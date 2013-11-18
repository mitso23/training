/*
 * ipctest.cpp
 *
 *  Created on: Aug 4, 2013
 *      Author: dimitrios
 */

#include<libipc/ipc.h>
#include<libbase/logger.h>

#include<iostream>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/time.h>

int  sendFile()
{
	int read_fd;
	int write_fd;
	struct stat stat_buf;
	off_t offset = 0;

	read_fd = open("/dev/zero", O_RDONLY);

	if (read_fd < 0)
	{
		std::cout << "Failed to open /dev/zero" << strerror(errno) << std::endl;
		return -1;
	}

	fstat(read_fd, &stat_buf);

	write_fd = open("/dev/null", O_WRONLY | O_CREAT, stat_buf.st_mode);

	if (write_fd < 0)
	{
		std::cout << "Failed to open /dev/null" << strerror(errno) << std::endl;
		return -1;
	}

	int result = sendfile(write_fd, read_fd, &offset, stat_buf.st_size);

	if (result < 0)
	{
		std::cout << "Failed send " << strerror(errno) << std::endl;
		return -1;
	}

	close(read_fd);
	close(write_fd);
}

bool finished= false;
void timer_handler (int signum)
{
	static int count = 0;
	printf ("timer expired %d times\n", ++count);

	if (count == 2)
		finished= true;
}

void sigChild(int number)
{
	int status;
	std::cout << "child died" << std::endl;
	wait(&status);
}

int main(int argc, char* argv[])
{

	struct sigaction sa;
	struct sigaction sa2;
	struct itimerval timer;
	/* Install timer_handler as the signal handler for SIGVTALRM. */
	memset (&sa, 0, sizeof (sa));
	memset (&sa2, 0, sizeof (sa2));
	sa.sa_handler = &timer_handler;
	sa2.sa_handler = &sigChild;
	sigaction (SIGVTALRM, &sa, NULL);
	sigaction(SIGCHLD, &sa2, NULL);
	timer.it_value.tv_sec = 0;
	timer.it_value.tv_usec = 250000;
	/* ... and every 250 msec after that. */
	timer.it_interval.tv_sec = 0;
	timer.it_interval.tv_usec = 250000;

	/* Start a virtual timer. It counts down whenever this process is
	   executing. */
	setitimer (ITIMER_VIRTUAL, &timer, NULL);

	while(1)
	{
		int x;

		std::cin >> x;

		std::cout << "value read was" << x << std::endl;

		int id= fork();

		if (id == 0)
		{
			char* argv[] = { (char*)"/bin/df", (char*)"-h", NULL };
			std::cout << "created a child" << getpid() << std::endl;
			execv(argv[0],argv);

			std::cout << "never should reach here" << std::endl;
		}

		sleep(1);

	}

	std::cout << "Finished " << std::endl;


}
