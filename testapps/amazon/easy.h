/*
 * easy.h
 *
 *  Created on: 12 Nov 2017
 *      Author: mitso23
 */

#ifndef EASY_H_
#define EASY_H_

/*Given a set of yesterday Amazon stock prices {2, -3, 5, 8, 1}
Write a code to buy and sell those stocks at maximum profit.
*/

#include "stdlib.h"
#include <iostream>
#include <algorithm>

struct MaxStock
{
	int max = 0;
	int pos = 0;
};

struct MinStock
{
	int min = 0;
	int pos = 0;
};

void findMaxStock(int* arr, unsigned int start, unsigned int size, struct MaxStock& maxStock)
{
	int max = arr[start];
	int pos = start;

	for(unsigned int i=pos + 1; i< size; ++i)
	{
		if (arr[i] > max)
		{
			max = arr[i];
			pos = i;
		}
	}

	maxStock.max = max;
	maxStock.pos = pos;
}

int calculate_max_profit_stock_sell(int* arr, unsigned int size)
{
	MaxStock maxStock;
	MinStock minStock;
	int maxProfit = 0;

	if (size == 1)
	{
		return arr[0];
	}
	else if (size == 2)
	{
		return abs(arr[1] - arr[0]);
	}
	else
	{
		minStock.min = arr[0];
		minStock.pos = 0;

		findMaxStock(arr, 0, size, maxStock);
		maxProfit = maxStock.max - minStock.min;

		std::cout << "min: " << minStock.min << " max: " << maxStock.max << " profit: " << maxProfit << std::endl;

		for(unsigned int i=2; i< size; ++i)
		{
			if (arr[i] < minStock.min)
			{
				minStock.min = arr[i];
				minStock.pos = i;

				if (i < (unsigned)maxStock.pos)
				{
					std::cout << "new min: " << minStock.min << " profit: " << maxProfit << std::endl;

					maxProfit = maxStock.max - minStock.min;
				}
				else
				{
					findMaxStock(arr, i, size, maxStock);

					std::cout << "new min and max: " << minStock.min << " max: " << maxStock.max << " profit: " << maxProfit << std::endl;

					if ((maxStock.max - minStock.min) > maxProfit)
					{
						maxProfit = maxStock.max - minStock.min;
					}
				}
			}
			else
			{
				continue;
			}
		}
	}

	return maxProfit;
}

void checkIfTwoElementsAddToSum(int* arr, unsigned int size, int sum)
{
	if (size <= 1)
	{
		return;
	}

	std::sort(arr, arr+size);

	for(unsigned int i=0, j=size - 1; i< size && j > i;)
	{
		if (arr[i] + arr[j] == sum)
		{
			std::cout << "found, i: " << i << " val: " << arr[i] << " j: " << j << " val: " << arr[j] << std::endl;
			++i;
			--j;
		}
		else if (arr[i] + arr[j] < sum)
		{
			++i;
		}
		else
		{
			--j;
		}
	}
}

#endif /* EASY_H_ */
