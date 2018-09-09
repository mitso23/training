/*
 * generate_combintaions_two_sorted_arrays.h
 *
 *  Created on: 15 May 2018
 *      Author: mitso23
 */

#ifndef GENERATE_COMBINTAIONS_TWO_SORTED_ARRAYS_H_
#define GENERATE_COMBINTAIONS_TWO_SORTED_ARRAYS_H_

#include <deque>

struct Pair
{
	Pair (int p, int v) : pos(p), val(v)
	{

	}

	int pos;
	int val;
};

void printCont(std::deque<Pair> q)
{
	for(auto it=q.begin(); it != q.end(); ++it)
	{
		std::cout << it->val << " ";
	}

	std::cout << std::endl;
}

void generatCombinationRec(unsigned int* arr1, unsigned int arr1Size, unsigned int arr1Index,
						   unsigned int* arr2, unsigned int arr2Size, unsigned int arr2Index,
						   bool& flag, std::deque<Pair>& q)
{
	std::cout << "arr1 index: " << arr1Index << " arr2 index: " << arr2Index << " flag: " << flag << " q.size() "  << q.size() << std::endl;

	if (flag)
	{
		if (arr1Index >= arr1Size)
		{
			std::cout << "max A index " << std::endl;
			return;
		}
	}
	else
	{
		if (arr2Index >= arr2Size)
		{
			std::cout << "max B index " << std::endl;
			return;
		}
	}

	if (flag)
	{
		//try A
		if (q.empty())
		{
			std::cout << "initial adding from A: " << arr1[arr1Index] << std::endl;
			q.push_back(Pair(arr1Index, arr1[arr1Index]));
			bool nextFlag = !flag;
			generatCombinationRec(arr1, arr1Size, arr1Index + 1, arr2, arr2Size, arr2Index, nextFlag, q);
		}
		else
		{
			Pair prevElement = q.back();
			std::cout << "Adding A, previous element " << prevElement.val << std::endl;

			unsigned int i= arr1Index;
			bool found = false;
			for (; i < arr1Size; ++i)
			{
				if (arr1[i] > prevElement.val)
				{
					found = true;
					break;
				}
			}

			if (found)
			{
				std::cout << "found element from A: " << arr1[i] << std::endl;
				q.push_back(Pair(i, arr1[i]));
				bool nextFlag = !flag;
				generatCombinationRec(arr1, arr1Size, i + 1, arr2, arr2Size, arr2Index, nextFlag, q);

				q.pop_back();
			}
			else
			{
				std::cout << "didn't find any element from A removing " << std::endl;
				q.pop_back();
			}
		}
	}
	else
	{
		//try to find the next largest element from B
		// if we don't find we simply return back
		Pair prevElement = q.back();

		std::cout << "B: q.size() " << q.size() << " prev element: " << prevElement.val << std::endl;

		unsigned int i= arr2Index;
		bool found = false;

		for(; i< arr2Size; ++i)
		{
			if (arr2[i] > prevElement.val)
			{
				found = true;
				break;
			}
		}

		if (found)
		{

			std::cout << "found next element from B: " << arr2[i] << std::endl;
			q.push_back(Pair(i, arr2[i]));
			printCont(q);
			bool nextFlag = !flag;
			generatCombinationRec(arr1, arr1Size, arr1Index, arr2, arr2Size, i + 1, nextFlag, q);

			q.pop_back();
		}
		else
		{
			std::cout << "didn't find next element from B, removing " << std::endl;
			q.pop_back();
		}
	}
}


void generatCombination(unsigned int* arr1, unsigned int arr1Size, unsigned int* arr2, unsigned int arr2Size)
{
	bool flag = true;
	std::deque<Pair> q;

	for(unsigned int i=0; i< arr1Size; ++i)
	{
		generatCombinationRec(arr1, arr1Size, i, arr2, arr2Size, 0, flag, q);
		q.clear();
	}
}



#endif /* GENERATE_COMBINTAIONS_TWO_SORTED_ARRAYS_H_ */
