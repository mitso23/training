#ifndef UTILS_H_
#define UTILS_H_

#ifdef __cplusplus
#include <iterator>
#include <iostream>
#include <algorithm>

// Template-template argument must
// be a class; cannot use typename:
template<typename C>
void print_cont(const C& c)
{
	for(auto item: c)
		std::cout << item << " ";

	std::cout << std::endl;
}
#endif

#include<stdio.h>
#include<stdlib.h>

static inline void hexdump(void* data, size_t sizeBytes)
{
	char* start= (char*)data;
	for(unsigned int i=0; i< sizeBytes; ++i)
	{
		printf("0x%02x ", *start++);
	}
	printf("\n");
}

#endif /* UTILS_H_ */
