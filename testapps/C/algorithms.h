#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <signal.h>
int fibonacci(int x)
{
	int previous= 1;
	int current= 1;

	for(int i=0; i< x; ++i)
	{
		int newValue= current;
		printf("%d\n", newValue);

		newValue= previous + current;
		previous= current;
		current= newValue;
	}

	return 0;
}

int fibonacciRec(int x)
{
	int sum= 0;

	if (x == 0)
	{
		return 1;
	}
	else if (x == 1)
	{
		return 2;
	}
	else
	{
		sum= fibonacciRec(x-2) + fibonacciRec(x - 1);
	}

	return sum;
}

#endif /* ALGORITHMS_H_ */
