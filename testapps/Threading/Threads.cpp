#include "PthreadUsage.h"
#include "ThreadQueue.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char* args[])
{

#if 0
	Pthread thread1(testThreadFunction, NULL);
	Pthread thread2(testThreadFunction, NULL);

	usleep(10000);
	thread1.join();
	thread2.join();
#endif

#if 0
	Lock* lock=new SpinLock();
	SemaphoreInterface* semaphore= new PosixSemaphore(1);
	ThreadQueueSemaphoreMutex queue(1, 99, lock, semaphore );
	queue.startThreads();
	usleep(1000*100);
	queue.waitForCompletetion();
#endif

	Lock* lock = new Mutex();
	SemaphoreInterface* dataReadySemaphore = new PosixSemaphore(0);
	SemaphoreInterface* spaceAvailableSemaphore = new PosixSemaphore(1);

	ThreadQueueSemaphoreMutex2 queue(1, 1, lock, dataReadySemaphore,
	spaceAvailableSemaphore);

	queue.startThreads();
	sleep(100);
	queue.waitForCompletetion();

	std::cout << "This is the end " << std::endl;
}

