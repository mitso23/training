#ifndef PERMUTATION_H_
#define PERMUTATION_H_

#include <string.h>

/// abcd pos = 1
///
void rotate(char* str,int size)
{
	int pos = strlen(str) - size;

	//printf("rotating pos: %d \n", pos);
	unsigned temp = str[strlen(str) - 1];

	for(int i=strlen(str) - 1; i >= pos; --i)
	{
		str[i] = str[i - 1];
	}

	str[pos] = temp;

	//printf("result: %s\n", str);
}

//->cat
//-->at print (cat),rotate(ta) print(cta)
//--->t (return)
void permutate(char* str, int size)
{
	if (size == 1)
	{
		return;
	}

	for(unsigned int i=0; i< size; ++i)
	{
		permutate(str, size - 1);

		if (size == 2)
		{
			printf("%s\n", str);
		}

		rotate(str, size);
	}
}

#endif /* PERMUTATION_H_ */
