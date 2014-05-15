#ifndef PTHREAD_H_
#define PTHREAD_H_

#include <stdio.h>
#include <libbase/logger.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <boost/bind.hpp>
#include <semaphore.h>

class Pthread
{
	typedef void *(*threadFuncPtr) (void *);

public:
	class ThreadArguments
	{
	public:
		ThreadArguments() : m_args(NULL), m_pthread(NULL)
		{

		}
		ThreadArguments(void* args, Pthread* thread) : m_args(args), m_pthread(thread)
		{

		}

		/*
		 * It is user responsibility to free the thread struct
		 */
		Pthread* getThread() const
		{
			return m_pthread;
		}

		/*
		 * It is user responsibility to free the arguments
		 */
		void* getArguments() const
		{
			return m_args;
		}

	private:
		void* m_args;
		Pthread* m_pthread;
	};

	Pthread(threadFuncPtr ptr, void* arg) :
		m_threadId(-1),
		m_threadDataKey(0),
		m_threadSpecificData(NULL),
		m_ptr(ptr),
		m_args(arg)
	{
		memset((void*)&m_threadAttr, 0, sizeof(m_threadAttr));
	}

	int runThread()
	{
		try
		{
			pthread_attr_init(&m_threadAttr);
			pthread_key_create(&m_threadDataKey, NULL);

			ThreadArguments arguments(m_args, this);
			m_threadArguments= arguments;

			return pthread_create(&m_threadId, &m_threadAttr, m_ptr,
					(void*)&m_threadArguments);
		}
		catch (...)
		{
			return -1;
		}
	}

	/**
	 * Thread can be set in an non joinable state, which means that the OS will clean up
	 * after a thread terminates otherwise the thread is in a zombie state like a process
	 */
	void setDetachState(int attr);

	/**
	 * Normally a thread can be canceled only if it reaches a certain cancellation point
	 * set PTHREAD_CANCEL_ASYNCHRONOUS in order to cancel at any point
	 * This must be called in a thread context
	 */
	void setCancelType(int attr);

	pthread_t getId() const;

	void* join();

	void cancel();

	void setCancelationPoint();

	void setThreadSpecificData(void* data);

	void* getThreadSpecificData();

private:
	pthread_t m_threadId;
	pthread_attr_t m_threadAttr;
	pthread_key_t m_threadDataKey;
	void* m_threadSpecificData;
	ThreadArguments m_threadArguments;
	threadFuncPtr m_ptr;
	void* m_args;
};

class Lock
{

public:
	virtual void setLockType(int)= 0;

	virtual int lock()= 0;

	virtual int unLock()= 0;

	virtual int tryLock()= 0;

	virtual ~Lock()
	{

	}

	virtual int readLock()
	{
		return -1;
	}

	virtual int writeLock()
	{
		return -1;
	}

};

class Mutex : public Lock
{
public:
	Mutex()
	{
		pthread_mutexattr_init (&m_attr);
		pthread_mutex_init (&m_mutex, NULL);
	}

	void setLockType(int attr)
	{
		pthread_mutexattr_settype(&m_attr, attr);
	}

	int lock()
	{
		int ret= pthread_mutex_lock(&m_mutex);
		return ret;
	}

	int tryLock()
	{
		return pthread_mutex_trylock(&m_mutex);
	}

	int unLock()

	{
		return pthread_mutex_unlock(&m_mutex);
	}

	~Mutex()
	{
		pthread_mutex_unlock(&m_mutex);
		pthread_mutexattr_destroy(&m_attr);
	}

private:
	pthread_mutex_t m_mutex;
	pthread_mutexattr_t m_attr;
};

class SpinLock : public Lock
{

public:

	SpinLock()
	{
		pthread_spin_init(&m_spinLock, 0);
	}

	void setLockType(int)
	{

	}

	int lock()
	{
		return pthread_spin_lock(&m_spinLock);
	}

	int unLock()
	{
		return pthread_spin_unlock(&m_spinLock);
	}

	int tryLock()
	{
		return pthread_spin_trylock(&m_spinLock);
	}

private:
	pthread_spinlock_t m_spinLock;
};

class RWMutex : public Lock
{

public:

	RWMutex()
	{
		pthread_rwlock_init(&rwLock, NULL);
	}

	void setLockType(int)
	{

	}

	int lock()
	{
		return -1;
	}

	int tryLock()
	{
		return -1;
	}

	int readLock()
	{
		return pthread_rwlock_rdlock(&rwLock);
	}

	int unLock()
	{
		return pthread_rwlock_unlock(&rwLock);
	}

	int writeLock()
	{
		return pthread_rwlock_wrlock(&rwLock);
	}

	~RWMutex()
	{

		pthread_rwlock_destroy(&rwLock);
		unLock();
	}

private:
	pthread_rwlock_t rwLock;
};

class SemaphoreInterface
{
public:

	virtual int wait()= 0;

	virtual int tryWait()= 0;

	virtual int post()= 0;

	virtual ~SemaphoreInterface()
	{

	}
};

class PosixSemaphore : public SemaphoreInterface
{

public:
	PosixSemaphore(int count) : m_count(count)
	{
		sem_init (&m_semaphore, 0, count);
	}

	int wait()
	{
		return sem_wait(&m_semaphore);
	}

	int tryWait()
	{
		return sem_trywait(&m_semaphore);
	}

	int post()
	{
		return sem_post(&m_semaphore);
	}

private:
	int m_count;
	sem_t m_semaphore;
};


class ScopedLock
{
public:
	ScopedLock(Lock* lock) : m_lock(lock)
	{
		m_lock->lock();
	}

	~ScopedLock()
	{
		m_lock->unLock();
	}

	int lock()
	{
		return m_lock->lock();
	}

	int unlock()
	{
		return m_lock->unLock();
	}

private:
	Lock* m_lock;
};

#endif
