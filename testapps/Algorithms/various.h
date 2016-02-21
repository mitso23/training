#ifndef VARIOUS_H_
#define VARIOUS_H_

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <list>
#include <utils/utils.h>

void missingNumber(const std::vector<int>& v)
{
	//XOR all the elements in the array
	//Sort and find the non contiguous block
	//Sum all the number using arithmetic progression and then sum it again and find the missing number
}

void pairOfNumbersSumToGivenN(std::vector<unsigned>& v, unsigned int sum)
{
	std::sort(v.begin(), v.end());

	for(auto start= v.begin(), end=v.end(); start < end;)
	{
		if (*start + *end == sum)
		{
			std::cout << *start << " : " << *end << std::endl;
			++start;
			--end;
		}
		else if (*start + *end > sum)
		{
			--end;
		}
		else
		{
			++start;
		}
	}
}

bool isDuplicate(const std::vector<int>& v, int pos)
{
	if (pos == 0)
	{
		return false;
	}
	else if (pos == v.size() - 1)
	{
		return v[pos] == v[pos - 1];
	}
	else
	{
		return (v[pos] == v[pos - 1]);
	}

}

void mergeSortedArrays(const std::vector<int>& v1, const std::vector<int>& v2, std::vector<int>& result)
{
	auto it1= v1.begin();
	auto it2= v2.begin();
	auto it3= std::back_inserter(result);

	while(it1 != v1.end() && it2 != v2.end())
	{
		if (*it1 < *it2)
		{
			*it3= *it1;
			++it1;
		}
		else if (*it1 > *it2)
		{
			*it3 = *it2;
			++it2;
		}
	}

	if (it1 == v1.end())
	{
		std::copy(it2, v2.end(), it3);
	}
	else if (it2 == v2.end())
	{
		std::copy(it1, v1.end(), it3);
	}

}

// std::vector <int> x = { 1, 1, 2, 2 , 3};
void removeDuplicateFromSortedArray(std::vector<int>& v)
{
	if (v.size() == 1)
	{
		return ;
	}

	auto start= v.begin() + 1;

	for(auto i= 1U; i< v.size(); ++i)
	{
		if (isDuplicate(v, i))
		{
			std::cout << "duplicate at " << i << " value: " << v[i] << std::endl;
		}
		else
		{
			std::cout << "not duplicate at " << i << " value: " << v[i] << std::endl;
			*start++= v[i];

		}
	}

	v.erase(start, v.end());
}

void findBestMatch(std::vector<unsigned>& arr, unsigned position, unsigned target)
{
	if(arr[position] == target)
	{
		std::cout << "target achieved " << std::endl;
		std::cout << "  adding " << arr[position] << std::endl;
		return;
	}
	else if (arr[position] > target)
	{
		std::cout << "target not achieved " << std::endl;
		std::cout << "  adding " << arr[position] << std::endl;
		return;
	}
	else
	{
		findBestMatch(arr, position + 1, target - arr[position]);
		std::cout << "  adding " << arr[position] << std::endl;
	}
}

void knapsack(std::vector<unsigned>& arr, unsigned target)
{
	for(auto i=0U; i< arr.size(); ++i)
	{
		findBestMatch(arr, i, target);
	}
}

unsigned pow(unsigned number)
{
	unsigned result= 1;
	for(unsigned int i=0; i< number; ++i)
	{
		result*= 2;
	}

	return result;
}

unsigned power(unsigned x, unsigned y)
{
	return (y == 1) ?  x : power(x*x, y>>1);
}

void printSpace(unsigned num)
{
	for (auto j = 0U; j < num; ++j)
	{
		std::cout << " ";
	}
}

void printStars(unsigned num)
{
	for (auto j = 0U; j < num; ++j)
	{
		std::cout << "*";
	}
}

void printNewLine()
{
	std::cout << std::endl;
}


//     **
//    ****
//  ********
void print_pyramid(unsigned height)
{
	unsigned maxNumDots= pow(height);

	for(unsigned int i=1; i<= height; ++i)
	{
		unsigned numDots= pow(i);
		unsigned numSpaces= maxNumDots - numDots;

		printSpace(numSpaces/ 2);
		printStars(numDots);
		printSpace(numSpaces/ 2);
		printNewLine();

	}
}

void findMaxSum(std::vector<int> arr)
{
	unsigned sum= 0;
	unsigned max_sum= 0;

	for(int i=0; i< arr.size(); ++i)
	{
		for(int j=0; j< arr.size(); ++j)
		{
			sum+= arr[j];
			if(sum > max_sum)
			{
				max_sum= sum;
			}
			else
			{
				break;
			}
		}
	}
}

void permutate(char c, std::vector<std::string>& l)
{
	std::vector<std::string> result;

	for(auto it=l.begin(); it!= l.end(); ++it)
	{
		for(unsigned int i=0; i< (*it).size() + 1; ++i)
		{
			auto temp= *it;
			temp.insert(i, 1, c);

			result.push_back(std::move(temp));
		}
	}

	l= result;
}





#endif /* VARIOUS_H_ */
