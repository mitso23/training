/*
 * ipc.cpp
 *
 *  Created on: Aug 2, 2013
 *      Author: dimitrios
 */

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include<string.h>
#include <sys/mman.h>
#include <time.h>
#include <unistd.h>


#include<libipc/ipc.h>


int SystemVSemaphore::waitForNonZeroValue(unsigned int key, int timedWait= -1)
{
	int semid= semget (key, 1, IPC_CREAT | 0666);

	if (semid < 0)
	{
		std::cout << "failed to get semaphore: " << strerror(errno) << std::endl;
	}

	struct sembuf operations[1];

	operations[0].sem_num = 0;
	operations[0].sem_op = -1;
	operations[0].sem_flg = SEM_UNDO;

	if ( semop (semid, operations, 1) < 0)
	{
		std::cout << "semops failed: " << strerror(errno) << std::endl;
		return -1;
	}

	return 0;

}

int SystemVSemaphore::waitIncrementSemaphore(unsigned int key, int count, int timedWait= -1)
{
	int semid = semget(key, 1, IPC_CREAT | 0666);

	if (semid < 0) {
		std::cout << "failed to get semaphore: " << strerror(errno)
				<< std::endl;
	}

	struct sembuf operations[1];

	operations[0].sem_num = 0;
	operations[0].sem_op = +1;
	operations[0].sem_flg = SEM_UNDO;

	if (semop(semid, operations, 1) < 0) {
		std::cout << "semops failed: " << strerror(errno) << std::endl;
		return -1;
	}

	operations[0].sem_num = 0;
	operations[0].sem_op = -count;
	operations[0].sem_flg = SEM_UNDO;

	if (semop(semid, operations, 1) < 0) {
		std::cout << "semops failed: " << strerror(errno) << std::endl;
		return -1;
	}

	return 0;

}

int SystemVSemaphore::incrementSemaphore(unsigned int key)
{
	int semid = semget(key, 1, IPC_CREAT | 0666);

	if (semid < 0)
	{
		std::cout << "failed to get semaphore: " << strerror(errno)
				<< std::endl;
	}

	struct sembuf operations[1];

	operations[0].sem_num = 0;
	operations[0].sem_op = +1;
	operations[0].sem_flg = SEM_UNDO;

	if (semop(semid, operations, 1) < 0)
	{
		std::cout << "semops failed: " << strerror(errno) << std::endl;
		return -1;
	}

	return 0;
}

int SystemVSemaphore::destroySemaphore(unsigned int key)
{
	int semid = semget(key, 1, IPC_CREAT | 0666);

	if (semid < 0)
	{
		std::cout << "failed to get semaphore: " << strerror(errno)
				<< std::endl;
	}

	return semctl(semid, 1, IPC_RMID, 0);
}

 char* SharedMemory::m_sharedMemory= NULL;
 int SharedMemory::m_segmentId= -1;

char* SharedMemory::getSharedMemory(bool owner, size_t size, unsigned int flags)
{
	int segment_id= 0;

	if (m_sharedMemory)
	{
		return m_sharedMemory;
	}

	if (owner)
	{
		segment_id = shmget (SHARED_MEM_KEY, size,
	                     IPC_CREAT | flags);

		if (segment_id < 0)
		{
			std::cerr << "Failed to create shared memory segment as owner" << strerror(errno) << std::endl;
			return NULL;
		}

		SystemVSemaphore::incrementSemaphore(SHARED_MEM_SEMAPHORE_KEY);
	}
	else
	{
		SystemVSemaphore::waitForNonZeroValue(SHARED_MEM_SEMAPHORE_KEY);

		segment_id = shmget (SHARED_MEM_KEY, size,
							flags);
		if (segment_id < 0)
		{
			std::cerr << "Failed to create shared memory segment as client"
					<< strerror(errno) << std::endl;
			return NULL;
		}
	}

	m_sharedMemory= (char*) shmat (segment_id, 0, 0);
	m_segmentId= segment_id;

	if(!m_sharedMemory)
	{
		std::cerr << "Failed to attach to shared memory " << strerror(errno) <<  std::endl;
		return NULL;
	}

	return m_sharedMemory;

}

int SharedMemory::destroySharedMemory()
{
	int result= 0;

	if (m_segmentId != -1 && m_sharedMemory)
	{
		/* Detach the shared memory segment. */
		result= shmdt (m_sharedMemory);

		/* Deallocate the shared memory segment. */
		result= shmctl (m_segmentId, IPC_RMID, 0);

		SystemVSemaphore::destroySemaphore(SHARED_MEM_SEMAPHORE_KEY);
	}

	m_segmentId= -1;
	m_sharedMemory= NULL;

	return result;
}

void* MemoryMap::map()
{
	m_fd= open(m_fileName, O_RDWR, S_IRUSR | S_IWUSR | O_CREAT);

	if (m_fd >=0)
	{
		return (m_mappedAddress= mmap(m_addr, m_length, m_prot, m_flags, m_fd, m_offset));
	}
	else
	{
		std::cerr << "failed to open file " << m_fileName << ": " << strerror(errno) << std::endl;
		return NULL;
	}
}

void MemoryMap::unmap()
{
	if (m_mappedAddress)
	{
		munmap(m_mappedAddress, m_length);
	}
}
