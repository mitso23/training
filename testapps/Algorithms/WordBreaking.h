/*
 * WordBreaking.h
 *
 *  Created on: 5 Jul 2017
 *      Author: mitso23
 */

#ifndef WORDBREAKING_H_
#define WORDBREAKING_H_

#include "string.h"
#include <deque>
#include <string>

std::deque<std::string> words;

void printLevel2(unsigned int level)
{
	std::cout << "-";
	for(unsigned int i=0; i< level; ++i)
	{
		std::cout << "-";
	}
	std::cout << ">";
}

bool wordInDictionary(const char* word, const char** dict, unsigned int sizeDict)
{
	for(unsigned int i=0; i< sizeDict; ++i)
	{
		//std::cout << "dict[" <<i << "]" << dict[i] << " word: " << word << std::endl;
		bool result = strcmp(dict[i], word);
		if (result == 0)
		{
			return true;
		}
	}

	return false;
}

void printAllWords_rec(const char* sentence, const char** dict,
		unsigned int sizeDict, unsigned int level, unsigned int startPos,
		unsigned int stopPos)
{
	//printLevel2(level);
	//std::cout << "startPos: " << startPos << " endPos: " << stopPos << " words.size: " << words.size() << " str(len): " << strlen(sentence) << std::endl;

	if (startPos == strlen(sentence))
	{
		for(const auto& item: words)
		{
			std::cout << item << " ";
		}

		std::cout << std::endl;

		return;
	}

	char word[strlen(sentence) + 1];

	unsigned int length = 1;
	memcpy(word, sentence + startPos, length);
	word[length] = '\0';

	while(startPos + length <= strlen(sentence))
	{
		if(wordInDictionary(word, dict, sizeDict))
		{
			//std::cout << "word in dictionary: " << word << std::endl;

			stopPos = startPos + length - 1;
			words.push_back(std::string(word));
			printAllWords_rec(sentence, dict, sizeDict, level + 1, stopPos + 1, stopPos);
			words.pop_back();
		}
		else
		{
			//std::cout << "word not in dictionary: " << word << std::endl;
		}

		word[length] = *(sentence + startPos + length);
		++length;
		word[length] = '\0';

	}

	//std::cout << "returning" << std::endl;
}


#endif /* WORDBREAKING_H_ */
