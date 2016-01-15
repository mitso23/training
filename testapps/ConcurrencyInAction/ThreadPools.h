#ifndef THREADPOOLS_H
#define THREADPOOLS_H

#include <containers/thread_safe_queue.h>
#include <utils/utils.h>
#include <mutex>
#include <vector>
#include <functional>

class thread_pool
{
public:
	thread_pool() : m_done(false)
	{
		for(unsigned int i=0; i< 4; ++i)
		{
			m_threads.push_back(scoped_thread(std::thread(&thread_pool::excecuteTask, this)));
		}
	}

	~thread_pool()
	{
		m_done= true;
		//We also need to interrupt the thread here
	}

	void postWork(std::function<void()>&& funct)
	{
		m_threadQueue.push(funct);
	}

private:
	std::atomic<bool> m_done;
	FineGrainLockQueue<std::function<void()>> m_threadQueue;
	std::vector<scoped_thread> m_threads;

	void excecuteTask()
	{
		while(!m_done)
		{
			//Get the next task and executed it
			std::function<void()> task;
			m_threadQueue.wait_pop(task);
			task();
		}
	}
};

#endif /* THREADPOOLS_H_ */
