/*
 * Knapsack.h
 *
 *  Created on: 5 Jul 2017
 *      Author: mitso23
 */

#ifndef KNAPSACK_H_
#define KNAPSACK_H_

#include <deque>
std::deque<int> q;
unsigned int minNumCoins = 0xFFFFFFFF;

void knapsack(unsigned* data, unsigned int index, unsigned int size, unsigned int& sum, unsigned int target, unsigned int level, bool useSameCoin)
{
	++level;

	for(unsigned int i= useSameCoin ? 0 : index; i< size; ++i)
	{
		sum = sum + data[i];
		q.push_back(data[i]);

		if (sum == target)
		{
			if (q.size() < minNumCoins)
			{
				minNumCoins = q.size();
#if 1
			for(auto item: q)
			{
				std::cout << item << " ";
			}
			std::cout << std::endl;
#endif
			}

			if (useSameCoin)
			{
				knapsack(data, i, size, sum, target, level, useSameCoin);
			}
			else if(!useSameCoin && i < size - 1)
			{
				knapsack(data, i + 1, size, sum, target, level, useSameCoin);
			}
		}
		else if (sum < target)
		{
			if (useSameCoin)
			{
				knapsack(data, i, size, sum, target, level, useSameCoin);
			}
			else if (!useSameCoin && i < size - 1)
			{
				knapsack(data, i + 1, size, sum, target, level, useSameCoin);
			}
		}
		else
		{

		}

		//backtrack
		sum = sum - data[i];
		q.pop_back();
	}

	--level;
}



#endif /* KNAPSACK_H_ */
