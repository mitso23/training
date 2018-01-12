/*
 * boggle.h
 *
 *  Created on: 15 Nov 2017
 *      Author: mitso23
 */

#ifndef BOGGLE_H_
#define BOGGLE_H_

#include<string>
#include <deque>

struct BoggleTree
{
	BoggleTree()
	{
		for(unsigned int i=0; i< 24; ++i)
		{
			pNode[i] = nullptr;
		}
	}

	BoggleTree* pNode[127];

	bool isLastCharacter = false;
};

BoggleTree* boggleTreeRoot;

bool checkWordExists(const std::string& str, BoggleTree* boggleTreeRoot, bool& fullWorld)
{
	auto node = boggleTreeRoot->pNode[str[0]];

	if(node)
	{
		if (str.length() == 1)
		{
			if (node->isLastCharacter)
			{
				fullWorld = true;
			}

			return true;
		}

		return checkWordExists(str.substr(1, str.length()), node, fullWorld);
	}
	else
	{
		return false;
	}
}

BoggleTree* AddCharacter(char c, BoggleTree* boggleTreeRoot, bool lastCharacter)
{
	if (!boggleTreeRoot->pNode[c])
	{
		boggleTreeRoot->pNode[c] = new BoggleTree();
	}

	auto node =  boggleTreeRoot->pNode[c];
	if (lastCharacter)
	{
		node->isLastCharacter = true;
	}
}

void dictionaryToBoggleTree(char* dict[], unsigned dictSize)
{
	BoggleTree* root = boggleTreeRoot;
	BoggleTree* current = root;

	for(unsigned int j=0; j< dictSize; ++j)
	{
		for(unsigned int i=0; i< strlen(dict[j]); ++i)
		{
			current = AddCharacter(dict[j][i], current, i == (strlen(dict[j]) - 1));
		}

		current = root;
	}
}

void printDeq(std::deque<char>& deq)
{
	for(auto it= deq.begin(); it != deq.end(); ++it)
	{
		std::cout << *it;
	}

	if (!deq.empty())
		std::cout << std::endl;
}

void printBoggleDictionary(BoggleTree* current, std::deque<char>& deq)
{
	//std::cout << "current: " << current << std::endl;
	if (current == nullptr)
	{
		return;
	}

	for(unsigned int i=0; i< 127; ++i)
	{
		if (current->pNode[i] != NULL)
		{
			deq.push_back(i);
			//std::cout << "pushing character : " << (char)(i + 'A') << std::endl;
			printBoggleDictionary(current->pNode[i], deq);

			printDeq(deq);
			if (!deq.empty())
			{
				deq.pop_back();
			}
		}
		else
		{
			//std::cout << "empty " << std::endl;
			printDeq(deq);
			if (!deq.empty())
			{
				deq.pop_back();
			}
		}
	}
}

bool visitedArr[3][3];

bool isSafe(int i, int j)
{
	if (!visitedArr[j][i] && i>=0 && i<3 && j>=0 && j < 3)
	{
		return true;
	}

	return false;
}

bool isWorldInDict(const std::string& str, char* dict[], unsigned dictSize)
{
	for(unsigned int i=0; i< dictSize; ++i)
	{
		auto index = std::string(dict[i]).find(str);
		if (std::string(dict[i]) == str)
		{
			std::cout << "match: " << str << std::endl;
			return true;
		}
		else if (index == 0)
		{
			return true;
		}

	}

	return false;
}

bool my_binary_search(const std::string& str, char* dict[], unsigned dictSize, bool fullSearch = false)
{
	int start = 0;
	int end = dictSize - 1;
	int mid = start + (end - start)/2;

	while(start <= end)
	{

		auto comp = (fullSearch == true) ? std::string(dict[mid]) : std::string(dict[mid]).substr(0, str.length());
		//std::cout << "searching " << comp << std::endl;

		if (comp > str)
		{
			end = mid - 1;
		}
		else if (comp < str)
		{
			start = mid + 1;
		}
		else
		{
			//std::cout << "partial match : " << str << " full: " << std::string(dict[mid]) << " mode: " << std::boolalpha << fullSearch << std::endl ;
			return true;
		}

		mid = start + (end - start)/2;
	}

	return false;

}

int CheckWordInDictionary(const std::string& str, char* dict[], unsigned dictSize)
{
	bool res = my_binary_search(str, dict, dictSize, true);
	if (res == true)
	{
		std::cout << "match: " << str << std::endl;
		return true;
	}
	else
	{
		return my_binary_search(str, dict, dictSize);
	}

}

void find_all_possible_words_boggle_rec(char* dict[], unsigned dictSize, char arr[3][3], int i, int j, std::string& str, bool slow)
{
	if (!isSafe(i, j))
	{
		return;
	}

	str.push_back(arr[j][i]);

	if (slow == true)
	{
		if (!isWorldInDict(str, dict, dictSize))
		{
			str.pop_back();
			return;
		}
	}
	else
	{
		//if (!CheckWordInDictionary(str, dict, dictSize))
		bool fullWord = false;

		if (!checkWordExists(str, boggleTreeRoot, fullWord))
		{
			str.pop_back();
			return;
		}
		else
		{
			if (fullWord)
			{
				std::cout << "match: " << str << std::endl;
			}
			else
			{
				//std::cout << "partial match: " << str << std::endl;
			}
		}

	}

	visitedArr[j][i] = true;


	find_all_possible_words_boggle_rec(dict, dictSize, arr, i + 1, j, str, slow);
	find_all_possible_words_boggle_rec(dict, dictSize, arr, i - 1 , j, str, slow);
	find_all_possible_words_boggle_rec(dict, dictSize, arr, i, j + 1, str, slow);
	find_all_possible_words_boggle_rec(dict, dictSize, arr, i, j - 1, str, slow);

	find_all_possible_words_boggle_rec(dict, dictSize, arr, i+1, j+1, str, slow);
	find_all_possible_words_boggle_rec(dict, dictSize, arr, i-1, j+1, str, slow);
	find_all_possible_words_boggle_rec(dict, dictSize, arr, i-1, j-1, str, slow);
	find_all_possible_words_boggle_rec(dict, dictSize, arr, i+1, j-1, str, slow);

	visitedArr[j][i] = false;
	str.pop_back();
}

void find_all_possible_words_boggle(char* dict[], unsigned dictSize, char arr[3][3], int i, int j, std::string& str, bool slow)
{
	for(unsigned int j=0; j< 3; ++j)
	{
		for(unsigned int i=0; i< 3; ++i)
		{
			find_all_possible_words_boggle_rec(dict, dictSize, arr, i, j, str, slow);
		}
	}
}


#endif /* BOGGLE_H_ */
