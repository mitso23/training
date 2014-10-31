#ifndef THREADQUEUE_H_
#define THREADQUEUE_H_

#include <libthread/Thread.h>
#include <queue>
#include <signal.h>

//THIS IS A NAIVE IMPLEMENTATION (NOT CORRECT, JUST FOR EXPERIMENTING)
class ThreadQueueSemaphoreMutex
{

public:
	ThreadQueueSemaphoreMutex(int numSendThreads, int numReadThreads, Lock* lock, SyncPrimitive* semaphore) :
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
	SyncPrimitive* m_semaphore;
	int m_numSendThreads;
	int m_numReadThreads;
	Pthread* m_sendThread[100];
	Pthread* m_readThread[100];
	bool m_stopThread;
};


class ProducerConsumerSemaphore
{

public:
	static const int QUEUE_SIZE= 10;

	ProducerConsumerSemaphore(int numSendThreads, int numReadThreads, Lock* lock, SyncPrimitive* queueFullSemaphore, SyncPrimitive* queueEmptySemaphore) :
		m_numSendThreads(numSendThreads),
		m_numReadThreads(numReadThreads),
		m_lock(lock),
		m_queueFullSemaphore(queueFullSemaphore),
		m_queueEmptySemaphore(queueEmptySemaphore),
		m_stopThread(false)
	{
		m_lock->lock();
		m_lock->unLock();

	}

	void static readThreadSignal(int number)
	{
		std::cout << "Read thread received signal " << std::endl;
	}

	void static sendThreadSignal(int number)
	{
		std::cout << "Write Thread received signal " << std::endl;
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
		ProducerConsumerSemaphore* ins= static_cast<ProducerConsumerSemaphore*>(args->getArguments());

		ins->sendThread(args->getThread());

		return NULL;
	}

	static void* readThreadWrapper(void* instanse)
	{
		Pthread::ThreadArguments* args =
				static_cast<Pthread::ThreadArguments*>(instanse);

		ProducerConsumerSemaphore* ins =
				static_cast<ProducerConsumerSemaphore*>(args->getArguments());

		ins->readThread(args->getThread());

		return NULL;
	}

	void* sendThread(Pthread* thread)
	{

		struct sigaction sa;
		memset(&sa, 0, sizeof(sa));
		sa.sa_handler = &sendThreadSignal;
		sigaction(15, &sa, NULL);

		static int data = 0;

		for (int i = 0; i < QUEUE_SIZE * 500; i++)
		{
			if (m_stopThread)
			{
				return NULL;
			}

			m_queueFullSemaphore->wait();

			//Lock the Queue
			{
				ScopedLock lock(m_lock);

				//add some data
				if (m_queue.size() == QUEUE_SIZE)
				{
					std::cout << "Trying to write to a full buffer, aborting"
							<< std::endl;
					return NULL;
				}

				m_queue.push(data++);
				std::cout << "Incrementing data: " << data << std::endl;

				//let the other thread know that data is available (if the queue was already empty)
				m_queueEmptySemaphore->post();

			}

		}

		return NULL;
	}

	void* readThread(Pthread* thread)
	{

		struct sigaction sa;
		memset(&sa, 0, sizeof(sa));
		sa.sa_handler = &readThreadSignal;
		sigaction(15, &sa, NULL);

		while(1)
		{

			m_queueEmptySemaphore->wait();

			if (m_stopThread)
			{
				return NULL;
			}

			ScopedLock lock(m_lock);

			if (m_queue.empty())
			{
				std::cout << "Trying to read from an empty queue, aborting "
						<< std::endl;
				return NULL;
			}

			std::cout << "Thread: " << thread->getId() << " Reading value: "
					<< m_queue.front() << std::endl;

			m_queue.pop();

			m_queueFullSemaphore->post();

		}

		return NULL;
	}

	void waitForCompletetion()
	{
		m_stopThread= true;

		for(int i=0; i< m_numSendThreads; ++i)
		{
			m_queueFullSemaphore->post();
			//m_sendThread[i]->stopThread();
		}

		for(int i=0; i< m_numReadThreads; ++i)
		{
			m_queueEmptySemaphore->post();
			//m_readThread[i]->stopThread();
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
	SyncPrimitive* m_queueFullSemaphore;
	SyncPrimitive* m_queueEmptySemaphore;
	int m_numSendThreads;
	int m_numReadThreads;
	Pthread* m_sendThread[100];
	Pthread* m_readThread[100];
	bool m_stopThread;
};


class ProducerConsumerCondVariable
{

public:
	static const int QUEUE_SIZE= 10;

	ProducerConsumerCondVariable(int numSendThreads, int numReadThreads, Lock* lock, SyncPrimitive* queueFullCondVariable, SyncPrimitive* queueEmptyCondVariable) :
		m_numSendThreads(numSendThreads),
		m_numReadThreads(numReadThreads),
		m_lock(lock),
		m_queueFullCondVariable(queueFullCondVariable),
		m_queueEmptyCondVariable(queueEmptyCondVariable),
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
		ProducerConsumerCondVariable* ins= static_cast<ProducerConsumerCondVariable*>(args->getArguments());

		ins->sendThread(args->getThread());

		return NULL;
	}

	static void* readThreadWrapper(void* instanse)
	{
		Pthread::ThreadArguments* args =
				static_cast<Pthread::ThreadArguments*>(instanse);

		ProducerConsumerCondVariable* ins =
				static_cast<ProducerConsumerCondVariable*>(args->getArguments());

		ins->readThread(args->getThread());

		return NULL;
	}

	void* sendThread(Pthread* thread)
	{
		static int data= 0;

		for (int i=0; i< QUEUE_SIZE * 500; i++)
		{
			if (m_stopThread)
			{
				return NULL;
			}

			ScopedLock lock(m_lock);

			while(m_queue.size() >=QUEUE_SIZE)
			{
				//The mutex will automatically unlock in wait
				std::cout << "Queue is Full going to sleep" << std::endl;
				m_queueFullCondVariable->wait();

				if (m_stopThread)
				{
					return NULL;
				}

			}

			//At this point the mutex is locked again
			{
				//add some data
				if (m_queue.size() == QUEUE_SIZE)
				{
					std::cout << "Trying to write to a full buffer, aborting" << std::endl;
					return NULL;
				}

				m_queue.push(data++);
				std::cout << "Incrementing data: " << data << std::endl;

				//let the other thread know that data is available
				m_queueEmptyCondVariable->broadcast();

			}

		}

		return NULL;
	}

	void* readThread(Pthread* thread)
	{
		while(1)
		{

			ScopedLock lock(m_lock);

			while(m_queue.empty())
			{

				std::cout << "Queue is empty going to sleep " << std::endl;
				m_queueEmptyCondVariable->wait();

				if (m_stopThread)
				{
					return NULL;
				}
			}

			//At this point the mutex is locked again

			if (m_stopThread)
			{
				return NULL;
			}

			std::cout << "Thread: " << thread->getId() << " Reading value: "
					<< m_queue.front() << std::endl;

			m_queue.pop();

			m_queueFullCondVariable->post();


		}

		return NULL;
	}

	void waitForCompletetion()
	{
		m_stopThread= true;

		for(int i=0; i< m_numSendThreads; ++i)
		{
			m_queueFullCondVariable->post();
		}

		for(int i=0; i< m_numReadThreads; ++i)
		{
			m_queueEmptyCondVariable->post();
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
	SyncPrimitive* m_queueFullCondVariable;
	SyncPrimitive* m_queueEmptyCondVariable;
	int m_numSendThreads;
	int m_numReadThreads;
	Pthread* m_sendThread[100];
	Pthread* m_readThread[100];
	bool m_stopThread;
};




#endif /* THREADQUEUE_H_ */
