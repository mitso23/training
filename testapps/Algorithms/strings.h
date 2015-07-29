#ifndef STRINGS_H_
#define STRINGS_H_

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>


void my_strcpy(const char* src, char* dst)
{
	while(*src)
	{
		*dst++= *src++;
	}
}


#endif /* STRINGS_H_ */
