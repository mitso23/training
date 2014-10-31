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
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>



void pipeTesting()
{
	int fds[2];
	pid_t pid;
	/* Create a pipe. File descriptors for the two ends of the pipe are
	 placed in fds. */
	pipe(fds);
	/* Fork a child process. */
	pid = fork();
	if (pid == (pid_t) 0)
	{
		/* This is the child process. Close our copy of the write end of
		 the file descriptor. */
		close(fds[1]);
		/* Connect the read end of the pipe to standard input. */
		dup2(fds[0], STDIN_FILENO);
		/* Replace the child process with the “sort” program. */
		execlp("sort", "sort", NULL);
	}
	else
	{
		/* This is the parent process. */
		FILE* stream;
		/* Close our copy of the read end of the file descriptor. */
		close(fds[0]);
		/* Convert the write file descriptor to a FILE object, and write
		 to it. */
		stream = fdopen(fds[1], "w");
		fprintf (stream, "C\n");
		fprintf (stream, "D\n");
		fprintf (stream, "A\n");
		fprintf (stream, "E\n");
		fflush(stream);
		close(fds[1]);
		/* Wait for the child process to finish. */

		waitpid(pid, NULL, 0);
	}
	return;
}

void pipeTesting2()
{
	FILE* stream = popen ("sort", "w");
	fprintf (stream, "C\n");
			fprintf (stream, "D\n");
			fprintf (stream, "A\n");
			fprintf (stream, "E\n");
			fflush(stream);

	pclose (stream);

}

int main(int argc, char* argv[])
{

	int pid= fork();

	if(pid < 0)
	{
		std::cerr << "fork failed" << strerror(errno) << std::endl;
		return -1;
	}

	int fd;

	if (pid == 0)
	{
		char* mem= SharedMemory::getSharedMemory(true, 1024, 0666);
		sprintf(mem, "Hello World");
		std::cout << "created shared memory as owner" << std::endl;
		sleep(1);
		SharedMemory::destroySharedMemory();
		std::cout << "destroyed shared memory as owner" << std::endl;

		MemoryMap memoryMap(0,1024,PROT_WRITE , MAP_SHARED, (char*)"/dev/zero", 0);

		char* ptr= (char*)memoryMap.map();
		strcpy(ptr, "Parent");
		memoryMap.flush();

		pipeTesting2();

	}
	else
	{
		char* mem= SharedMemory::getSharedMemory(false, 1024, 0666);
		sleep(2);
		std::cout << "got shared memory as client: " << mem << std::endl;

		MemoryMap memoryMap(0,1024*1024, PROT_READ, MAP_SHARED, (char*)"/dev/zero", 0);
		char* ptr= (char*)memoryMap.map();
		std::cout << "child received " << ptr << std::endl;

		pipeTesting();

		*ptr= 1;
	}


	std::cout << "Child exiting: " << pid << std::endl;

}
