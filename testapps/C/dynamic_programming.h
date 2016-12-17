#ifndef DYNAMIC_PROGRAMMING_H_
#define DYNAMIC_PROGRAMMING_H_

#include <stdio.h>

// [1 2 3 4 5 6]  --> The sum that gives us 7
// 1 < sum (7)
	// 1 2 < sum (6)
		// 1 2 3 < sum (4)
			/// 1 2 3 4 >  (1) sum (remove 4 and try again)
				/// 1 2 3 5 > sum (remove 5 and try again)
					/// 1 2 3 6 > sum (last element return)
	// 1, 3 < sum
		// 1, 3, 4 > sum
			// 1, 3 , 5 > sum

	//1, 4 < sum
		// 1, 4, 5 > sum
			// 1, 4, 6 > sum

	// 1, 5 < sum
		// 1, 5, 6 > sum

	// 1, 6 == sum (return)

// 2 < sum(7)
	// 2, 3 < sum(7)
		// 2, 3, 4 > sum(7)
			// 2, 3 , 5 > sum(7)



void knapsack_slow(int sum, int* arr, int position, int size)
{
	printf("arr: %d sum: %d \n", arr[position], sum);

	if (sum == arr[position])
	{
		printf("sum achieved: %d \n\n", arr[position]);

		if (position == size - 1)
		{
			printf("last element, returning\n");
			return;
		}

		knapsack_slow(sum, arr, position + 1, size);
		//printf("arr: %d \n", arr[position]);
	}
	else if (sum > arr[position])
	{
		if (position == size - 1)
		{
			printf("last element, returning \n");
			return;
		}

		knapsack_slow(sum - arr[position], arr, position + 1, size);
	}
	else
	{
		printf("overflow: %d \n", arr[position]);

		if (position == size - 1)
		{
			printf("last element, returning \n");
			return;
		}

		knapsack_slow(sum, arr, position + 1, size);
		//printf("arr: %d \n", arr[position]);
	}
}

void knapsack(int sum, int* arr, int size)
{
	for(int j=0; j< size; j++)
	{
		printf("--> Starting from: %d \n", arr[j]);

		for(int i=0; i< size - j; ++i)
		{
			knapsack_slow(sum - ((i == 0) ? 0 : arr[j]), arr, j + i, size);
		}
	}
}

#endif
