#ifndef DYNAMIC_PROGRAMMING_H_
#define DYNAMIC_PROGRAMMING_H_

#include <stdio.h>
#include <stdlib.h>

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

void print(int num, int depth)
{
	depth = depth > 50 ? 50 : depth;

	for(unsigned int i=0; i< depth; ++i)
		printf(".");

	printf("%d\n", num);

}

int compInt (const void * elem1, const void * elem2)
{
    int f = *((int*)elem1);
    int s = *((int*)elem2);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}


// This is the version where the array is not sorted
void knapsack_slow(int sum, int* arr, int position, int size, int depth)
{
	print(arr[position], depth);

	if (sum == arr[position])
	{
		printf("sum achieved: %d\n", sum);

		if (position == size - 1)
		{
			return;
		}

		knapsack_slow(sum, arr, position + 1, size, ++depth);
	}
	else if (sum > arr[position])
	{
		if (position == size - 1)
		{
			return;
		}

		knapsack_slow(sum - arr[position], arr, position + 1, size, ++ depth);
	}
	else
	{
		if (position == size - 1)
		{
			return;
		}

		knapsack_slow(sum, arr, position + 1, size, ++depth);
	}
}

void knapsack_fast(int sum, int* arr, int position, int size, int depth)
{
	if (sum == arr[position])
	{
		print(arr[position], depth);
		printf("sum achieved\n");
		return;
	}
	else if (sum > arr[position])
	{
		print(arr[position], depth);

		if (position == size - 1)
		{
			return;
		}

		knapsack_fast(sum - arr[position], arr, position + 1, size, ++depth);
	}
	else
	{
		return;
	}
}

void knapsack(int sum, int* arr, int size)
{
	qsort (arr, size, sizeof(*arr), compInt);

	for(int j=0; j< size; j++)
	{
		//printf("--> Starting from: %d \n", arr[j]);

		for(int i=0; i< size - j; ++i)
		{
			if (i == 1)
				continue;

			knapsack_fast(sum - ((i == 0) ? 0 : arr[j]), arr, j + i, size, (i == 0) ? 0 : 1);
		}
	}
}

#endif
