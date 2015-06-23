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
	explicit scoped_thread(std::thread&& t) :
			m_thread(std::move(t))
	{

	}

	scoped_thread(scoped_thread&& rhs)
	{
		m_thread= std::move(rhs.m_thread);
	}

	~scoped_thread()
	{
		if (m_thread.joinable())
		{
			std::cout << "waiting for thread to exit " << std::endl;
			m_thread.join();
			std::cout << "thread exited" << std::endl;
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

template<typename Iterator,typename T>
struct accumulate_block
{
	void operator()(Iterator first, Iterator last, T& result)
	{
		result = accumulate(first, last, 0);
		std::cout << "result is " << result << std::endl;
	}
};

template<typename Iterator, typename T>
struct parallel_accumulate
{
	T operator()(Iterator first, Iterator last)
	{
		unsigned distance= std::abs(std::distance(first, last)) ;

		const unsigned minNumberItemsPerThread= 3;
		const unsigned maxNumberThreads= 2;

		unsigned int numItemsPerThread= 0;
		unsigned int numThreads= 0;

		if (distance <= minNumberItemsPerThread)
		{
			numThreads= 1;
			numItemsPerThread= distance;
		}
		else if (distance < (minNumberItemsPerThread * maxNumberThreads))
		{
			numItemsPerThread= minNumberItemsPerThread;
			numThreads= distance / numItemsPerThread;
		}
		else
		{
			numThreads= maxNumberThreads;
			numItemsPerThread= distance / numThreads;
		}

		std::cout << "num items: " << numItemsPerThread << " numThreads: " << numThreads << std::endl;


		int results[maxNumberThreads] = { 0 };

		{
			Iterator block_start= first;
			std::vector<scoped_thread> threads;

			for (auto i = 0U; i < numThreads; ++i)
			{
				Iterator block_end= block_start;

				if (i == numThreads - 1)
					std::advance(block_end, numItemsPerThread + (distance % numItemsPerThread));
				else
					std::advance(block_end, numItemsPerThread);

				std::cout << "start  is " << *block_start <<  " end is " << *(block_end - 1) << std::endl ;

				scoped_thread sk(std::thread(accumulate_block<Iterator, T> (),
						block_start, block_end, std::ref(results[i])));
				block_start= block_end;

				threads.push_back(std::move(sk));
			}
		}

		return std::accumulate(results, results + numThreads, 0);
	}
};

#endif /* MANAGINGTHREADS_H_ */
