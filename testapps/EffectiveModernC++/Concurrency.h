/*
 * Concurrency.h
 *
 *  Created on: 4 Dec 2017
 *      Author: mitso23
 */

#ifndef CONCURRENCY_H_
#define CONCURRENCY_H_

#include <thread>
#include <future>
#include <chrono>

template<typename F, typename ... Ts>
inline std::future<typename std::result_of<F(Ts...)>::type>
reallyAsync(F&& f, Ts&&... params)
{
	// for asynchronous
	return std::async(std::launch::async, // call to f(params...)
			std::forward<F>(f),
			std::forward<Ts>(params)...);
}

void asyncTask()
{
	std::this_thread::sleep_for(std::chrono::seconds(1));
}

std::promise<int> getDelayedResult()
{
	std::promise<int> p;
}

template<typename RandomIt>
unsigned parallelAccumulate(RandomIt begin, RandomIt end)
{
	auto length = std::distance(begin, end);

	if (length < 100000000/4)
	{
		return std::accumulate(begin, end, 0);
	}

	auto mid = begin + length/2;
	auto fut = reallyAsync(parallelAccumulate<RandomIt>, begin, mid);

	return fut.get() + parallelAccumulate(mid, end);

}

void scheduleTask()
{
	auto fut = reallyAsync(asyncTask);

	while (fut.wait_for(std::chrono::milliseconds(100)) !=
	std::future_status::ready)
	{
		std::cout << " still running" << std::endl;
	}

	std::cout << "finished running: " << std::endl;
}

template<typename InputIterator>
void accumulate(InputIterator begin, InputIterator end, std::promise<int> p)
{
	auto sum = std::accumulate(begin, end, 0);
	p.set_value(sum);
	std::cout << "accumulate result is: " << sum << std::endl;
}

#if 0
template<class T, template <typename> class C>
void accumulate2(typename C<T>::iterator begin, typename C<T>::iterator end, std::promise<int> p)
{
	auto sum = std::accumulate(begin, end, 0);
	p.set_value(sum);
	std::cout << "accumulate result is: " << sum << std::endl;
}
#endif

void test_future()
{
	std::promise<int> p;
	std::future<int> f = p.get_future();

	std::vector<int> v = {1, 2, 3 , 4 };
	std::thread t(accumulate2<int, std::vector<int> >, v.begin(), v.end(), std::move(p));

	std::cout << "future result is: " << f.get() << std::endl;
	t.join();
}

class ThreadRAII
{

public:
	ThreadRAII(std::thread&& thread, std::function<void(void)> terminateThread = nullptr, bool join = true)
	: m_join(join),
	  m_terminateThread(terminateThread),
	  m_thread(std::move(thread))
	{

	}

	~ThreadRAII()
	{
		if (m_thread.joinable())
		{
			if (m_join)
			{
					if (m_terminateThread)
						m_terminateThread();

					std::cout << "joining thread" << std::endl;
					m_thread.join();
					std::cout << "thread was joined" << std::endl;

			}
			else
			{
				m_thread.detach();
			}
		}
	}

private:
	bool m_join;
	//MAKE SURE that the thread object is declared last so all the variables are initialised before the thread
	// start running
	std::function<void(void)> m_terminateThread;
	std::thread m_thread;


};

#endif /* CONCURRENCY_H_ */
