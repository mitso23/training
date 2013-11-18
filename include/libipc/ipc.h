#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/mman.h>
#include <stdio.h>
#include <libbase/logger.h>

typedef enum
{
	SHARED_MEM_SEMAPHORE_KEY= 0xFF0000FF,
	SHARED_MEM_KEY= 0xDD0000DD,

}ipc_keys_t;

class SystemVSemaphore
{
public:

	static int waitForNonZeroValue(unsigned int key, int timedWait);

	static int waitIncrementSemaphore(unsigned int key, int count, int timedWait);

	static int incrementSemaphore(unsigned int key);

	static int destroySemaphore(unsigned int key);
};


class MemoryMap

{
	DECLARE_LOGGER(MemoryMap)

public:
	MemoryMap(void* addr, size_t length, int prot, int flags, char* fileName,int offset) :
			m_addr(addr), m_length(length), m_prot(prot), m_flags(flags), m_fileName(fileName), m_offset(offset),
			m_fd(-1),m_mappedAddress(NULL)
	{

	}

	void* map();

	void unmap();

	void flush() const
	{
		msync (m_addr, m_length, MS_SYNC | MS_INVALIDATE);
	}

private:
	void* m_addr;
	size_t m_length;
	int m_prot;
	int m_flags;
	char* m_fileName;
	int m_offset;
	int m_fd;
	void* m_mappedAddress;

};

class SharedMemory
{
	SharedMemory()
	{

	}

public:
	static char* getSharedMemory(bool owner, size_t size, unsigned int flags);
	static int destroySharedMemory();

private:
	static int m_segmentId;
	static char* m_sharedMemory;
};
