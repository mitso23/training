#ifndef RWLOCK_H_
#define RWLOCK_H_
#include <libthread/Thread.h>
#include <mutex>
#include <condition_variable>

///READER->READER->WRITTER->READER->READER
class RWLock
{
public:
	RWLock() :
			m_numReaders(0), m_pendingWrite(false)
	{

	}

	void lockReader()
	{
		std::unique_lock < std::mutex > lock(m_lock);
		m_writeCondVar.wait(lock, [this]{ return !m_pendingWrite; });
		++m_numReaders;
	}

	void unlockReader()
	{
		std::unique_lock < std::mutex > lock(m_lock);
		if (--m_numReaders == 0)
		{
			m_readCondVar.notify_one();
		}
	}

	void lockWriter()
	{
		std::unique_lock < std::mutex > lock(m_lock);
		m_pendingWrite = true;
		m_readCondVar.wait(lock, [this]	{ return (m_numReaders == 0) ? (true) : (false);});
	}

	void unlockWriter()
	{
		m_pendingWrite = false;
		m_writeCondVar.notify_all();
		m_lock.unlock();
	}

private:
	unsigned int m_numReaders;
	bool m_pendingWrite;
	std::condition_variable m_readCondVar;
	std::condition_variable m_writeCondVar;
	std::mutex m_lock;
};

#endif /* RWLOCK_H_ */
