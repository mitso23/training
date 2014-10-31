#include "PthreadUsage.h"
#include "SimpleThreading.h"
#include "ThreadingProblems.h"
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
	SyncPrimitive* semaphore= new PosixSemaphore(1);
	ThreadQueueSemaphoreMutex queue(1, 99, lock, semaphore );
	queue.startThreads();
	usleep(1000*100);
	queue.waitForCompletetion();
#endif

#if 0
	Lock* lock = new Mutex();
	SyncPrimitive* queueFullSemaphore = new PosixSemaphore(ProducerConsumerSemaphore::QUEUE_SIZE);
	SyncPrimitive* gueueEmptySemaphore = new PosixSemaphore(0);

	ProducerConsumerSemaphore queue(1, 2, lock, queueFullSemaphore,
	gueueEmptySemaphore);

	queue.startThreads();
	sleep(3);
	queue.waitForCompletetion();
#endif


#if 0
	Mutex* lock = new Mutex();
	SyncPrimitive* queueFullCondVariable = new CondVariable(lock);
	SyncPrimitive* gueueEmptyCondVariable = new CondVariable(lock);

	ProducerConsumerCondVariable queue(20, 10, lock, queueFullCondVariable,
			gueueEmptyCondVariable);

	queue.startThreads();
	sleep(5);
	queue.waitForCompletetion();
#endif

#if 0
	Lock* lock = new SpinLock;
	SyncPrimitive* semaphore = new PosixSemaphore(1);

	ReaderWriterProblem rd(semaphore, lock, 5, 2);
	rd.startThreads();
	sleep(3);
	rd.stopThreads();
#endif

	Lock* lock = new Mutex;
	const int numPhilosophers= 100;
	SyncPrimitive* semaphore[numPhilosophers];

	for (int i=0; i< numPhilosophers; ++i)
	{
		semaphore[i]= new PosixSemaphore(1);
	}

	SyncPrimitive* signal = new CondVariable((Mutex*)lock);
	DinningPhilosophers phil(semaphore, lock, signal, numPhilosophers);
	phil.startThreads();
	sleep(500);

	std::cout << "This is the end " << std::endl;
}

