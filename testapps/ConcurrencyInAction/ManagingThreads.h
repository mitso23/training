#ifndef MANAGINGTHREADS_H_
#define MANAGINGTHREADS_H_

#include <iostream>
#include <thread>
#include <utils/Noisy.h>
#include <vector>
#include <algorithm>
#include <future>

//NOTE: Make sure that when exception is thrown thread is joined, the only way to pass the thread is by reference as it is non copyable
// or by moving the object
class thread_guard
{
	std::thread& t;
public:
	explicit thread_guard(std::thread& t_) :
			t(t_)
	{

	}

	~thread_guard()
	{
		std::cout << "Joining the thread " << std::endl;
		if (t.joinable())
		{
			t.join();
		}
	}

	thread_guard(thread_guard const&) = delete;

	thread_guard& operator=(thread_guard const&) = delete;
};

class scoped_thread
{
	std::thread m_thread;

public:
	explicit scoped_thread(std::thread t) :
			m_thread(std::move(t))
	{

	}

	~scoped_thread()
	{
		if (m_thread.joinable())
		{
			//std::cout << "Joining for the thread" << std::endl;
			m_thread.join();
		}
	}
};

void testArgument(int i, const std::string& str)
{
	sleep(1);
}

void testArgumentByReference(int i, int& ref)
{
	sleep(1);
}

void scopeTest()
{
	Noisy ns;
	std::thread thread(ns);
	thread.detach();
}

class backGroundTask
{
public:
	void operator()()
	{
		std::cout << "Hello World Thread\n";
	}

	~backGroundTask()
	{
		std::cout << "Destroying background task " << std::endl;
	}
};

std::thread f()
{

	return std::thread
	{ backGroundTask() };
}

void f2(std::thread t)
{
	t.join();
}

void startManyThreads()
{
	std::vector<std::thread> threads;

	for (int i = 0; i < 10; i++)
	{
		threads.push_back(std::thread(Noisy()));
	}

	std::for_each(threads.begin(), threads.end(),
			std::mem_fn(&std::thread::join));
}

template<typename InputIterator, typename OutputIterator, typename T>
void accumulate(InputIterator begin, OutputIterator end, T& result)
{
	for (auto it = begin; it != end; ++it)
	{
		result += *it;
	}
}

template<typename Iterator,typename T>
struct accumulate_block
{
    void operator()(Iterator first,Iterator last,T& result)
    {
        result=accumulate(first,last,result);
    }
};



//NOTE: For some reason it doesn't compile
template<typename Iterator, typename T>
struct parallel_accumulate
{
	T operator()(Iterator first, Iterator last, T init)
	{
		unsigned long const length = std::distance(first, last);

		if (!length)
			return init;
		unsigned long const min_per_thread = 25;
		unsigned long const max_threads =

		(length + min_per_thread - 1) / min_per_thread;
		unsigned long const hardware_threads =
				std::thread::hardware_concurrency();

		unsigned long const num_threads = std::min(
				hardware_threads != 0 ? hardware_threads : 2, max_threads);

		unsigned long const block_size = length / num_threads;
		std::vector<T> results(num_threads);

		std::vector<std::thread> threads;
		Iterator block_start = first;
		for (unsigned long i = 0; i < (num_threads - 1); ++i)
		{
			Iterator block_end = block_start;
			std::advance(block_end, block_size);
			//std::thread(accumulate_block<Iterator, T>(),
				//	block_start, block_end, std::ref(results[i]));
			block_start = block_end;
		}
		//accumulate_block<Iterator, T>()(block_start, last,
			//	results[num_threads - 1]);

		//std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));

		//return accumulate(results.begin(), results.end(), init);

	}
};

#endif /* MANAGINGTHREADS_H_ */
