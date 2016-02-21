#ifndef TESTAPPS_ALGORITHMS_BIT_MANIPULATION_H_
#define TESTAPPS_ALGORITHMS_BIT_MANIPULATION_H_

#include <utils/utils.h>

//101010
void reverseBits(unsigned int x)
{
	dumpValue(x);

	auto length= sizeof(x) * 8;

	for(auto i=0U; i< length / 2; ++i)
	{
		auto l= (x >> (length - i - 1)) & 1;
		auto r= (x >> i) & 1;

		if (l != r)
		{
			if (l)
			{
				x= x | (1 <<i );
				x= x & (~(1 <<  (length - i - 1)));
			}
			else
			{
				x= x & (~(1 <<  i));
				x= x | (1 << (length - i - 1));
			}
		}
	}

	dumpValue(x);
}

// This is equivalent of doing n % 7. will return 0,1,2,3,4,5,6,7
unsigned int fun0(unsigned int n)
{
	return n & 7;
}

// This is equivalent of doing n % 7. will return 7,6,5,4,3,2,1
unsigned int fun1(unsigned int n)
{
	return -n & 7;
}

// number * 2^l / 2^r= number * 2^(l-r)
unsigned int foo2(int number, int l, int r)
{
	return (number << l) >> r;
}

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

	//return (x > 0)
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


#endif /* TESTAPPS_ALGORITHMS_BIT_MANIPULATION_H_ */
