#ifndef DYNAMIC_PROGRAMMING_H_
#define DYNAMIC_PROGRAMMING_H_

#include <stdio.h>

// [1 2 3 4 5 ]  sum that gives you 7
void knapsack(const int* arr, int size, int sum)
{
	printf("array %d  sum %d size %d \n", arr[0], sum, size);

	if (arr[0] == sum)
	{
		printf("sum Achieved\n\n");

		if (size == 0)
		{
			return;
		}

		sum = sum + arr[-1];
		knapsack(arr + 1, --size, sum);
		printf("arr %d\n", arr[0]);
	}
	else if (arr[0] < sum)
	{
		if (size == 0)
		{
			return;
		}

		sum = sum - arr[0];
		knapsack(arr + 1, --size, sum);
		printf("arr %d\n", arr[0]);
	}
	else
	{
		printf("Overflow \n");
		sum = sum + arr[-1];

		if (size != 0)
		{
			--size;
		}

		knapsack(arr, size, sum);
		printf("arr %d\n", arr[0]);
	}
}

#endif
