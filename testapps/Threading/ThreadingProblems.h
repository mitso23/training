#ifndef THREADINGPROBLEMS_H_
#define THREADINGPROBLEMS_H_

#include<libthread/Thread.h>


//Multiple Readers multiple writers implementation (NAIVE one without using RWMutex)
class ReaderWriterProblem
{

public:
	ReaderWriterProblem(SyncPrimitive* syncObject, Lock* lock, int numReaders,
			int numWritters) :
			m_syncObject(syncObject), m_lock(lock), m_numReadThreads(
					numReaders), m_numWriteThreads(numWritters), m_stopThread(
					false), m_database(0), m_readCounter(0)
	{

	}
	void startThreads()
	{
		for (int i = 0; i < m_numWriteThreads; ++i)
		{
			m_sendThread[i] = new Pthread(sendThreadWrapper,
					static_cast<void*>(this));
			m_sendThread[i]->runThread();
		}

		for (int i = 0; i < m_numReadThreads; i++)
		{
			m_readThread[i] = new Pthread(readThreadWrapper,
					static_cast<void*>(this));
			m_readThread[i]->runThread();
		}
	}

	static void* sendThreadWrapper(void* instanse)
	{
		Pthread::ThreadArguments* args =
				static_cast<Pthread::ThreadArguments*>(instanse);
		ReaderWriterProblem* ins =
				static_cast<ReaderWriterProblem*>(args->getArguments());

		ins->writeThread(args->getThread());

		return NULL;
	}

	static void* readThreadWrapper(void* instanse)
	{
		Pthread::ThreadArguments* args =
				static_cast<Pthread::ThreadArguments*>(instanse);

		ReaderWriterProblem* ins =
				static_cast<ReaderWriterProblem*>(args->getArguments());

		ins->readThread(args->getThread());

		return NULL;
	}

	void stopThreads()
	{
		m_stopThread = true;

		//wake up all the threads before doing join
		for (int i = 0; i < m_numWriteThreads + m_numReadThreads; ++i)
		{
			m_syncObject->post();
		}

		for (int i = 0; i < m_numWriteThreads; ++i)
		{
			m_sendThread[i]->join();
		}

		for (int i = 0; i < m_numReadThreads; i++)
		{
			m_readThread[i]->join();
		}
	}

	void inline incrementReadCounter()
	{
		ScopedLock lock(m_lock);
		++m_readCounter;
	}

	void inline decrementReadCounter()
	{
		ScopedLock lock(m_lock);
		if (--m_readCounter == 0)
		{
			lock.unlock();
			//wake up any potential writers
			m_syncObject->post();
		}

	}

	bool inline isReadCounterZero() const
	{
		ScopedLock lock(m_lock);

		if (m_readCounter == 0)
		{
			return true;
		}

		return false;
	}

	void readFromDatabase()
	{
		incrementReadCounter();

		std::cout << "Reading from the database " << m_database << std::endl;
		usleep(10);

		decrementReadCounter();
	}

	void writeToDatabase()
	{
		std::cout << "Writing the database " << ++m_database << std::endl;
		usleep(15);
	}

	void* readThread(Pthread* thread)
	{
		while (!m_stopThread)
		{
			if (isReadCounterZero())
			{
				//wait for resource to be available
				m_syncObject->wait();

				if (m_stopThread)
				{
					return NULL;
				}

				readFromDatabase();

				m_syncObject->post();

			}
			else
			{
				readFromDatabase();
			}

		}
		return NULL;
	}

	void* writeThread(Pthread* thread)
	{
		while (1)
		{

			m_syncObject->wait();

			if (m_stopThread)
			{
				return NULL;
			}

			writeToDatabase();

			m_syncObject->post();

		}

		return NULL;
	}

private:
	SyncPrimitive* m_syncObject;
	Lock* m_lock;
	Pthread* m_sendThread[100];
	Pthread* m_readThread[100];
	int m_numReadThreads;
	int m_numWriteThreads;
	bool m_stopThread;
	int m_database;
	int m_readCounter;
};


class DinningPhilosophers
{

	typedef enum
	{
		THINKING,
		HUNGRY,
		EATING
	}philosopher_state_t;

//0  1  2

#define LEFT ((philosopher + 1) % m_numPhilosophers)
#define RIGHT ((philosopher - 1) < 0) ? (m_numPhilosophers - 1) : (philosopher - 1)

public:
	DinningPhilosophers(SyncPrimitive* syncObject[], Lock* lock, SyncPrimitive* signal,
			int numPhilosophers
			) :
			 m_lock(lock), m_signal(signal), m_numPhilosophers(
					numPhilosophers), m_stopThread(false)
	{
		m_philosophersState= new int[m_numPhilosophers];

		for (int i = 0; i < m_numPhilosophers; ++i)
		{
			m_philosophersState[i] = THINKING;
		}

		m_syncObject= syncObject;
	}

	~DinningPhilosophers()
	{
		delete[] m_philosophersState;
		m_philosophersState= NULL;

		if (!m_stopThread)
		{
			stopThreads();
		}


	}

	void startThreads()
	{

		for (int i = 0; i < m_numPhilosophers; ++i)
		{
			m_philosophersThreads[i] = new Pthread(philosopherWrapper,
					static_cast<void*>(this));

			m_philosophersThreads[i]->runThread();

		}

	}

	void stopThreads()
	{
		m_stopThread = true;

		//wake up all the threads before doing join
		for (int i = 0; i < m_numPhilosophers; ++i)
		{
			m_syncObject[i]->post();
		}

		for (int i = 0; i < m_numPhilosophers; ++i)
		{
			m_philosophersThreads[i]->join();
			delete m_philosophersThreads[i];
		}

	}

	void eat(int philosopher)
	{
		m_lock->lock();
		m_philosophersState[philosopher]= HUNGRY;

		if (m_philosophersState[LEFT] == EATING || m_philosophersState[RIGHT] == EATING)
		{
			m_lock->unLock();

			std::cout << "HUNGRY " << philosopher << std::endl;
			m_syncObject[philosopher]->wait();

			m_lock->lock();
		}

		m_philosophersState[philosopher]= EATING;

		std::cout << "Eating: " << philosopher << std::endl;
		m_lock->unLock();

		usleep(200*1000);
	}

	void signalPhilosopher(int philosopher)
	{
		m_lock->lock();

		if (m_philosophersState[philosopher] == HUNGRY && m_philosophersState[LEFT] != EATING && m_philosophersState[RIGHT] != EATING)
		{
			std::cout << "signaling " << philosopher << std::endl;
			m_syncObject[philosopher]->post();
		}

		m_lock->unLock();
	}

	void think(int philosopher)
	{
		//ScopedLock lock(m_lock);
		m_lock->lock();

		m_philosophersState[philosopher] = THINKING;
		std::cout << "Thinking " << philosopher <<  std::endl;
		m_lock->unLock();

		//Think
		usleep(100*1000);
	}

	static void* philosopherWrapper(void* instanse)
	{
		Pthread::ThreadArguments* args =
				static_cast<Pthread::ThreadArguments*>(instanse);
		DinningPhilosophers* ins =
				static_cast<DinningPhilosophers*>(args->getArguments());

		ins->philosopher(args->getThread());

		return NULL;
	}

	void* philosopher(Pthread* thread)
	{
		static int g_philosopher= -1;
		int philosopher= ++g_philosopher;

		while (1)
		{
			think(philosopher);
			eat(philosopher);
			signalPhilosopher(LEFT);
			signalPhilosopher(RIGHT);
		}

		return NULL;
	}

private:
	SyncPrimitive** m_syncObject;
	Lock* m_lock;
	Pthread* m_philosophersThreads[100];
	SyncPrimitive* m_signal;
	int m_numPhilosophers;
	bool m_stopThread;
	int* m_philosophersState;


};


#endif /* THREADINGPROBLEMS_H_ */
