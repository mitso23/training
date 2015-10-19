#include "bithacks.h"

int isNegative(int x)
{
	//the naive implementation
#if 0
	int sign=0;

	if(x < 0)
	{
		sign= -1;
	}
	else if (x > 0)
	{
		sign=+1;
	}
	else
	{
		sign = 0;
	}
#endif

	//this will incur branch prediction;
	//return x < 0;

	//return -(int)((unsigned int)((int)x) >> (sizeof(int) * 8 - 1));

	//This might be architecture specific it relies on the fact that the left most bit is set to 1 for negative numbers
	//return (x >> (((sizeof(x) - 1) * 8 )));

	//A negative number shifted left will be sign extended
	//return ( +1 | (x >> (sizeof(int) * 8 - 1)));

	//return (x > 0) - ( x < 0);

	//return (x > 0) l
}

int calculateAbs(int number)
{
	//X^0 will give you X
	//X^1 will give you 0 (the negation of the number)

	int v= number;           					// we want to find the absolute value of v
	unsigned int r;  							// the result goes here
	int const mask = v >> sizeof(int) * 7;

	r = (v + mask) ^ mask;
	return r;
	//r = (v ^ mask) - mask;
}
