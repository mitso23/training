#ifndef PTHREADUSAGE_H_
#define PTHREADUSAGE_H_
#include <libthread/Thread.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

static pthread_key_t thread_log_key;

class ThreadExitException : public std::exception
{

public:
	virtual const char* what() const throw()
	{
		return "Thread is exiting";
	}
	void exitThread(void* ptr)
	{
		return pthread_exit(ptr);
	}
};

void* testThreadFunction(void* args)
{
	Pthread* thread = (Pthread*) args;
	static Lock* lock= new SpinLock;
	lock->tryLock();
	if ( lock->tryLock() == EBUSY)
	{
		std::cout << "EBUSY" << std::endl;
	}

	std::cout << "Starting a Thread " << std::endl;
	lock->unLock();

	FILE* fp= NULL;
	try
	{

		fp = fopen("/home/dimitrios/training/resources/testFiless.txt",
				"w");
		if (!fp)
		{
			throw(new ThreadExitException());
			std::cerr << "error: " << strerror(errno) << std::endl;
		}

		thread->setThreadSpecificData((void*) fp);

		std::cout << "Thread data: " << thread->getThreadSpecificData()
				<< std::endl;
		sleep(1);

		int* ptr = new int;
		*ptr = 1000;
		return (void*) ptr;

	}
	catch (ThreadExitException& e)
	{
		std::cout << e.what() << std::endl;
		fclose(fp);
		e.exitThread(NULL);
		return 0;
	}
}


#endif /* PTHREADUSAGE_H_ */
