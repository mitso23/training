#ifndef COMBINATION_K_OUT_OF_N_ITEMS_H_
#define COMBINATION_K_OUT_OF_N_ITEMS_H_

#include <vector>
#include <deque>

#include "../linklist/list.h"

std::deque<int> cont;

void print_deq()
{
	for(auto it=cont.begin(); it != cont.end(); ++it)
	{
		std::cout << *it;
	}
	std::cout << std::endl;

}

// 1		 						2
// 1 2   		 	 1 3            2 3
// 1 2 3 , 1 2 4 	 1 3 4			2 3 4 , 2 3 5
void printCombination_rec(const std::vector<int>& data, int index, int level)
{
	cont.push_back(data[index]);

	if (level == 1)
	{
		print_deq();
		return;
	}

	for(unsigned int i=index; i< data.size() - 1; ++i)
	{
		--level;
		printCombination_rec(data, i + 1, level);
		++level;
		cont.pop_back();
	}
}

// 1 2 3 4
void printCombination_rec_2(int* result, int* data, int index, int n, int k, int level)
{
	//std::cout << "index: " << index << " n: " << n << " k: " << k << " level: " << level << std::endl;
	result[level] = data[index];

	if (level == (k - 1))
	{
		for(unsigned int i=0; i<k; ++i)
		{
			std::cout << result[i];
		}

		std::cout << std::endl;
		return;
	}

	for(unsigned int i=index; i< n -1 ; ++i)
	{
		printCombination_rec_2(result, data, i + 1, n, k, level+1);
	}
}

void printAllCombinations(int* data, int size, int index, int level)
{
	//std::cout << data[index] << std::endl;
	push_back(data[index]);

	if (level == 1)
	{
		printList();
		return;
	}

	for(unsigned int i=index; i< size - 1; ++i)
	{
		--level;
		printAllCombinations(data, size, i + 1, level);
		++level;
		remove_back();
	}
}

//This prints all the possible combinations like using binary count
void printCombinations2(int* data, int size)
{
	for(unsigned level= 1; level<= size; ++level)
	{
		for(unsigned int j=0; j< size; ++j)
		{
			clearList();
			printAllCombinations(data + j, size - j, 0, level);
		}
	}
}

void printCombination(const std::vector<int>& data, int index, int level)
{
	for(unsigned int i=0; i< data.size(); ++i)
	{
		cont.clear();
		printCombination_rec(std::vector<int>(data.begin() + i, data.end()), 0, level);
	}
}

#endif /* COMBINATION_K_OUT_OF_N_ITEMS_H_ */
