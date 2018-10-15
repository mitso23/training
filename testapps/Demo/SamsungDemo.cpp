/*
 * SamsungDemo.h
 *
 *  Created on: 5 Aug 2018
 *      Author: mitso23
 */

#ifndef SAMSUNGDEMO_H
#define SAMSUNGDEMO_H

#include "ResourceManagementBad.h"
#include "ResourceManagementGood.h"
#include "ResourceManagementGreat.h"
#include "ResourceManagementModern.h"

#include <fcntl.h>
#include <unistd.h>


int main(int argc, char* argv[])
{
	//ResourceManagementGood resource1(20);
	//ResourceManagementGood resource2 = resource1;
	//ResourceManagementGood resource2(10);
	//resource2 = resource1;

	//ResourceManagementGreat resource1(10);
	//ResourceManagementGreat resource2 = resource1;


#if 0
	//valgrind can't detect buffer overflow
	// we need to manually place guards after each array
	int x[3] = { 0 };
	int index = 0;

	std::cin >> index;
	x[index] = 1;

	std::cout << x[index] << std::endl;
#endif

#if 0
	//conditional jump on uninitialized variable
	int* ptr = new int[10];
	if (ptr[0])
	{
		std::cout << "ptr[0] is not zero" << std::endl;
	}

	delete[] ptr;

#endif

#if 0
	//leaking a file descriptor
	int fd = open("/tmp/test.txt", O_CREAT | O_WRONLY,  S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	write(fd, "Hello", sizeof("Hello"));
#endif

	return 0;
}

#endif /* SAMSUNGDEMO_H_ */
