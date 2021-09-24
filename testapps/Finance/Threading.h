#pragma once

#include <thread>
#include <list>
#include <random>
#include <array>
#include <algorithm>
#include <future>
#include <execution>
#include <queue>
#include <functional>

int compute1(int a)
{
	return a + 2;
}

int compute2(int c)
{
	return c - 2;
}

int compute3(int a)
{
	return a*2;
}

int compute4(int a)
{
	return a / 2;
}

int final(int r1, int r2)
{
	return r1 + r2;
}

class ThreadPool
{
 public:
	ThreadPool(unsigned numThreads)
		: m_numThreads(numThreads)
	{
		for(int i=0; i< m_numThreads; ++i)
		{
			m_threads.push_back(std::thread(&ThreadPool::ExecuteTasks, this));
		}
	}

	~ThreadPool()
	{
		//std::cout << "terminating: " << std::endl;

		m_terminate.store(true);

		{
			//std::cout << "notifying threads" << std::endl;
			std::unique_lock<std::mutex> lock(m_mutex);
			m_condVar.notify_all();
			//std::cout << "finished notifying threads" << std::endl;
		}

		for(auto& t : m_threads)
		{
			//std::cout << "waiting to join: " << std::endl;
			t.join();
			//std::cout << "joined" << std::endl;
		}
	}

	template<typename F, typename ...Args, typename R = std::invoke_result_t<std::decay_t<F>, std::decay_t<Args>...>, std::enable_if_t<!std::is_void<R>::value>>
	std::future<R> PushTask(F&& f, const Args&... args)
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		std::shared_ptr<std::promise<R>> promise(new std::promise<R>);
		auto fut = promise->get_future();

		auto l = [f, promise, args...] () mutable
		{
			try
			{
				promise->set_value(f(args...));
			}
			catch(...)
			{
				promise->set_exception(std::current_exception());
			}
		};

		m_tasks.push(std::move(l));
		m_condVar.notify_all();

		return fut;
	}

 private:
	void ExecuteTasks()
	{
		while(!m_terminate.load())
		{
			{
				std::unique_lock<std::mutex> lock(m_mutex);
				auto l = [&]()
				{
					if (m_terminate.load())
					{
						return true;
					}
					else if (m_tasks.empty())
					{
						return false;
					}
					else
					{
						return true;
					}
				};

				m_condVar.wait(lock, l);

				if (m_terminate.load())
				{
					break;
				}
#if 0
				int s;
				cpu_set_t cpuset;
				pthread_t thread;

				thread = pthread_self();
				CPU_ZERO(&cpuset);
				CPU_SET(m_threadAffinity.load(), &cpuset);
				m_threadAffinity.fetch_add(1);

				s = pthread_setaffinity_np(thread, sizeof(cpuset), &cpuset);

				s = pthread_getaffinity_np(thread, sizeof(cpuset), &cpuset);
				if (s < 0)
				{
					std::cout << "failed to get affinity" << std::endl;
					exit(0);
				}

				for (int j = 0; j < CPU_SETSIZE; j++)
				{
					if (CPU_ISSET(j, &cpuset))
					{
						std::cout << "got a task running in CPU: " << j << std::endl;
					}
				}
#endif
				m_tasks.front()();
				m_tasks.pop();

			}
		}
	}

 private:
	std::queue<std::function<void(void)>> m_tasks;
	std::mutex m_mutex;
	std::condition_variable m_condVar;
	std::atomic<bool> m_terminate{false};
	unsigned m_numThreads;
	std::vector<std::thread> m_threads;
	std::atomic<int> m_threadAffinity {0};
};

template <typename Fut, typename Work>
auto then(Fut&& f, Work w)
{
	return std::async(std::launch::async, [w, f = std::move(f)]() mutable { return w(f.get()); });
}

int parallelCompute()
{
	auto f1 = std::async(compute1, 1);
	auto f2 = std::async(compute2, 2);

	auto f3 = then(std::move(f1), compute3);
	auto f4 = then(std::move(f2), compute4);

	return final(f3.get(), f4.get());
}

//Naive implementation
template<typename ForwadIt>
auto parallelAccumulate(ForwadIt begin, ForwadIt end)
{
	//std::cout << " thread id: " << std::this_thread::get_id() << std::endl;

	auto d = std::distance(begin, end);
	if (d <= 1000)
	{
		return std::accumulate(begin, end, 0);
	}

	auto nextIt = begin;
	std::advance(nextIt, d / 2);

	auto result = std::async(std::launch::async, parallelAccumulate<ForwadIt>, begin, nextIt);
	return std::accumulate(nextIt, end, 0) + result.get();
}

std::array<std::list<double>, 3> ll;

void generateData()
{
	std::default_random_engine generator;
	std::normal_distribution<double> distribution(5.0,2.0);

	for(auto& elem : ll)
	{
		for (int i = 0; i < 1000000; ++i)
		{
			elem.push_back(distribution(generator));
		}
	}
}

#define HAS_MEM_FUNC(func, name)                                        \
    template<typename T, typename Sign>                                 \
    struct name {                                                       \
        typedef char yes[1];                                            \
        typedef char no [2];                                            \
        template <typename U, U> struct type_check;                     \
        template <typename _1> static yes &chk(type_check<Sign, &_1::func > *); \
        template <typename   > static no  &chk(...);                    \
        static bool const value = sizeof(chk<T>(0)) == sizeof(yes);     \
    };

HAS_MEM_FUNC(sort, has_sort)
HAS_MEM_FUNC(merge, has_merge)

template <typename T>
class Wrapper
{

};

template<typename Args...>
class Wrapper<Args...>
{

};

template<typename T>
class Monitor
{
 public:
	Monitor()
	{
		static_assert(std::is_default_constructible_v<T>, "type needs to be default constructible");
	}

	Monitor(T t)
		: m_t(t)
	{

	}

	template<typename ...Args>
	Monitor(Args&&...args)
		: m_t(T{std::forward<Args>(args)...})
	{

	}

	template<typename F>
	auto operator ()(F&& f)
	{
		std::lock_guard<std::mutex> l{m_mutex};
		return f(m_t);
	}

 private:
	T m_t;
	mutable std::mutex m_mutex;
};

template<typename T>
int SortElementsHelper(T& l)
{
	using Container = std::remove_reference<decltype(ll[0])>::type;
	using FunctPtr = void(Container::*)();

	if constexpr (has_sort<Container, FunctPtr>::value)
	{
		l.sort();
	}
	else
	{
		std::sort(l.begin(), l.end());
	}

	return 1;
}

int SortElements(decltype(ll[0])& l)
{
	return SortElementsHelper(l);
}

template<typename T>
auto MergeElements(T elements)
{
	using Container = std::remove_reference<decltype(ll[0])>::type;
	using FunctPtr = void(Container::*)(Container&);

	if constexpr (has_merge<Container, FunctPtr>::value)
	{
		for (int i = 1; i < elements.size(); ++i)
		{
			elements[0].merge(ll[i]);
		}

		return std::move(elements[0]);
	}
	else
	{
		std::remove_reference<decltype(ll[0])>::type first = std::move(elements[0]);

		for (int i = 1; i < ll.size(); ++i)
		{
			typename std::remove_reference<decltype(elements[0])>::type result;
			result.reserve(first.size() + ll[i].size());

			std::merge(elements[i].begin(), elements[i].end(), first.begin(), first.end(), std::back_inserter(result));
			first = std::move(result);
		}

		return first;
	}
}



auto MergeElements()
{
	return MergeElements(ll);
}
