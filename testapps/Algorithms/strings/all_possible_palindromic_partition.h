/*
 * all_possible_palindromic_partition.h
 *
 *  Created on: 21 Jul 2018
 *      Author: mitso23
 */

#ifndef ALL_POSSIBLE_PALINDROMIC_PARTITION_H_
#define ALL_POSSIBLE_PALINDROMIC_PARTITION_H_

#include <vector>
#include <string>

void printPallindrome(const std::vector<std::string> data)
{
	for(auto& item : data)
	{
		std::cout << item << " ";
	}

	std::cout << std::endl;
}

//DFS algorithm to solve this problem
void allPossiblePallindromicPartitions(char* str, unsigned int currentIndex, std::vector<std::string>& data)
{
	//std::cout << "index: " << currentIndex << " strlen: " << strlen(str)  << " data size: " << data.size() << std::endl;

	if (currentIndex >= strlen(str))
	{
		printPallindrome(data);
		return;
	}

	std::string newStr;
	for(unsigned int i=currentIndex; i < strlen(str); ++i)
	{
		//std::cout << "i: " << i << std::endl;
		newStr+= std::string(1, str[i]);
		data.push_back(newStr);
		//std::cout << "adding new str: " << newStr << std::endl;

		allPossiblePallindromicPartitions(str, i + 1, data);
	//	std::cout << "backtracking" << std::endl;

		if (!data.empty())
		{
			auto oldStr = data.back();
//			std::cout << "removing oldStr: " << oldStr << std::endl;
			data.pop_back();
		}
	}
}


#endif /* ALL_POSSIBLE_PALINDROMIC_PARTITION_H_ */
