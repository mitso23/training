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

}

void removeDuplicateFromSortedArray(std::vector<int>& v)
{

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
