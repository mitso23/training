#ifndef COMBINATION_H_
#define COMBINATION_H_

#include <vector>

void combination(int* arr, unsigned int size)
{
	for(unsigned int i=0; i< (1 << size); ++i)
	{
		//std::cout << "i:" << i << std::endl;
		for (unsigned int j=0; j< size; ++j)
		{
			//std::cout << "j: " << j << std::endl;
			if ((i >> j) & 1 == 1)
			{
				std::cout << arr[j];
			}
		}

		std::cout << std::endl;
	}
}

void combination_sum(int* arr, unsigned int size, unsigned int expectedSum)
{
	unsigned int sum = 0;
	std::vector<int> v;

	for(unsigned int i=0; i< (1 << size); ++i)
	{
		for (unsigned int j=0; j< size; ++j)
		{
			if ((i >> j) & 1 == 1)
			{
				sum+= arr[j];
				v.push_back(arr[j]);
			}
		}

		if (sum == expectedSum)
		{
			for(auto item: v)
			{
				std::cout << item;
			}
			std::cout << std::endl;
		}

		sum = 0;
		v.clear();
	}
}

#endif
