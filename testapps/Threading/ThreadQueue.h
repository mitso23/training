#ifndef THREADQUEUE_H_
#define THREADQUEUE_H_

#include <libthread/Thread.h>
#include <queue>


//THIS IS A NAIVE IMPLEMENTATION
class ThreadQueueSemaphoreMutex
{

public:
	ThreadQueueSemaphoreMutex(int numSendThreads, int numReadThreads, Lock* lock, SemaphoreInterface* semaphore) :
		m_numSendThreads(numSendThreads),
		m_numReadThreads(numReadThreads),
		m_lock(lock),
		m_semaphore(semaphore),
		m_stopThread(false)
	{
		m_lock->lock();
		m_lock->unLock();

	}

	void startThreads()
	{
		for (int i = 0; i < m_numSendThreads; ++i)
		{
			m_sendThread[i]= new Pthread(sendThreadWrapper, static_cast<void*>(this));
			m_sendThread[i]->runThread();
		}

		for (int i = 0; i < m_numReadThreads; i++)
		{
			m_readThread[i]= new Pthread(readThreadWrapper, static_cast<void*>(this));
			m_readThread[i]->runThread();
		}
	}

	static void* sendThreadWrapper(void* instanse)
	{
		Pthread::ThreadArguments* args=  static_cast<Pthread::ThreadArguments*>(instanse);
		ThreadQueueSemaphoreMutex* ins= static_cast<ThreadQueueSemaphoreMutex*>(args->getArguments());

		ins->sendThread(args->getThread());

		return NULL;
	}

	static void* readThreadWrapper(void* instanse)
	{
		Pthread::ThreadArguments* args =
				static_cast<Pthread::ThreadArguments*>(instanse);

		ThreadQueueSemaphoreMutex* ins =
				static_cast<ThreadQueueSemaphoreMutex*>(args->getArguments());

		ins->readThread(args->getThread());

		return NULL;
	}

	void* sendThread(Pthread* thread)
	{
		static int data= 0;

		for (int i=0; i< 1000; i++)
		{
			if (m_stopThread)
			{
				return NULL;
			}

			//Lock the Queue
			{
				ScopedLock lock(m_lock);

				//add some data
				m_queue.push(data++);
				std::cout << "Incrementing data: " << data << std::endl;
			}

			//let the other thread know that data is available
			m_semaphore->post();

		}

		return NULL;
	}

	void* readThread(Pthread* thread)
	{
		while(1)
		{

			{
				ScopedLock lock(m_lock);

				while (m_queue.empty())
				{
					m_lock->unLock();
					//The semaphore has memory so if somebody does post after the unlock it will work
					m_semaphore->wait();

					m_lock->lock();

					if (m_stopThread)
					{
						return NULL;
					}
				}

				//We can read here as match as we like as we hold the mutex

				std::cout << "Thread: " << thread->getId() << " Reading value: " << m_queue.front() << std::endl;
				m_queue.pop();

			}

		}

		return NULL;
	}

	void waitForCompletetion()
	{
		m_stopThread= true;

		for(int i=0; i< m_numReadThreads; ++i)
		{
			m_semaphore->post();
		}

		for (int i = 0; i < m_numSendThreads; ++i)
		{
			m_sendThread[i]->join();
		}

		for (int i = 0; i < m_numReadThreads; i++)
		{
			m_readThread[i]->join();
		}
	}

private:
	std::queue<int> m_queue;
	Lock* m_lock;
	SemaphoreInterface* m_semaphore;
	int m_numSendThreads;
	int m_numReadThreads;
	Pthread* m_sendThread[100];
	Pthread* m_readThread[100];
	bool m_stopThread;
};


//THIS IS A NAIVE IMPLEMENTATION
class ThreadQueueSemaphoreMutex2
{

public:
	ThreadQueueSemaphoreMutex2(int numSendThreads, int numReadThreads, Lock* lock, SemaphoreInterface* dataReadySemaphore, SemaphoreInterface* spaceAvailable) :
		m_numSendThreads(numSendThreads),
		m_numReadThreads(numReadThreads),
		m_lock(lock),
		m_dataReadySemaphore(dataReadySemaphore),
		m_spaceAvailableSemaphore(spaceAvailable),
		m_stopThread(false)
	{
		m_lock->lock();
		m_lock->unLock();

	}

	void startThreads()
	{
		for (int i = 0; i < m_numSendThreads; ++i)
		{
			m_sendThread[i]= new Pthread(sendThreadWrapper, static_cast<void*>(this));
			m_sendThread[i]->runThread();
		}

		for (int i = 0; i < m_numReadThreads; i++)
		{
			m_readThread[i]= new Pthread(readThreadWrapper, static_cast<void*>(this));
			m_readThread[i]->runThread();
		}
	}

	static void* sendThreadWrapper(void* instanse)
	{
		Pthread::ThreadArguments* args=  static_cast<Pthread::ThreadArguments*>(instanse);
		ThreadQueueSemaphoreMutex2* ins= static_cast<ThreadQueueSemaphoreMutex2*>(args->getArguments());

		ins->sendThread(args->getThread());

		return NULL;
	}

	static void* readThreadWrapper(void* instanse)
	{
		Pthread::ThreadArguments* args =
				static_cast<Pthread::ThreadArguments*>(instanse);

		ThreadQueueSemaphoreMutex2* ins =
				static_cast<ThreadQueueSemaphoreMutex2*>(args->getArguments());

		ins->readThread(args->getThread());

		return NULL;
	}

	void* sendThread(Pthread* thread)
	{
		static int data= 0;

		for (int i=0; i< 1000; i++)
		{
			if (m_stopThread)
			{
				return NULL;
			}

			//Lock the Queue
			{
				ScopedLock lock(m_lock);

				while(m_queue.size() == 10)
				{
					std::cout << "Queue is full going to sleep " << std::endl;
					m_spaceAvailableSemaphore->wait();
				}

				//add some data
				m_queue.push(data++);
				std::cout << "Incrementing data: " << data << std::endl;
			}

			//let the other thread know that data is available
			m_dataReadySemaphore->post();

		}

		return NULL;
	}

	void* readThread(Pthread* thread)
	{
		while(1)
		{

			{
				ScopedLock lock(m_lock);

				std::cout << "read Thread \n";

				while (m_queue.empty())
				{
					m_lock->unLock();
					//The semaphore has memory so if somebody does post after the unlock it will work
					std::cout << "Read thread queue empty waiting for data " << std::endl;
					m_dataReadySemaphore->wait();

					m_lock->lock();

					if (m_stopThread)
					{
						return NULL;
					}
				}

				//We can read here as match as we like as we hold the mutex

				std::cout << "Thread: " << thread->getId() << " Reading value: " << m_queue.front() << std::endl;
				m_queue.pop();
				m_spaceAvailableSemaphore->post();

			}

		}

		return NULL;
	}

	void waitForCompletetion()
	{
		m_stopThread= true;

		for(int i=0; i< m_numReadThreads; ++i)
		{
			m_dataReadySemaphore->post();
		}

		for(int i=0; i< m_numSendThreads; ++i)
		{
			m_spaceAvailableSemaphore->post();
		}

		for (int i = 0; i < m_numSendThreads; ++i)
		{
			m_sendThread[i]->join();
		}

		for (int i = 0; i < m_numReadThreads; i++)
		{
			m_readThread[i]->join();
		}
	}

private:
	std::queue<int> m_queue;
	Lock* m_lock;
	SemaphoreInterface* m_dataReadySemaphore;
	SemaphoreInterface* m_spaceAvailableSemaphore;
	int m_numSendThreads;
	int m_numReadThreads;
	Pthread* m_sendThread[100];
	Pthread* m_readThread[100];
	bool m_stopThread;
};




#endif /* THREADQUEUE_H_ */
