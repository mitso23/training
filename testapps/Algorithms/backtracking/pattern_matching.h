/*
 * pattern_matching.h
 *
 *  Created on: 5 Aug 2017
 *      Author: mitso23
 */

#ifndef PATTERN_MATCHING_H_
#define PATTERN_MATCHING_H_

char* patternMap[(unsigned int) 'z' - (unsigned int)'a'];

char* getNewString(char* str, unsigned int start, unsigned int end)
{
	unsigned int size = end - start + 1;
	char* newChar = new char[size + 1]();

	for(unsigned int i=0; i< size; ++i)
	{
		newChar[i] = str[start + i];
	}
	newChar[size] = '\0';

	return newChar;
}

bool pattern_match(char* str, unsigned int strIndex, char* pattern, unsigned int patternIndex)
{
	std::cout << "strIndex: " << strIndex << " patternIndex: " << patternIndex << std::endl;

	if (strIndex >= strlen(str) || patternIndex >= strlen(pattern))
	{
		std::cout << "index out of bounds: " << std::endl;
		return false;
	}

	char patternChar = pattern[patternIndex];

	if (patternMap[patternChar] == NULL)
	{
		std::cout << "first pattern: " << patternChar << std::endl;

		for(unsigned int i=0; i + strIndex < strlen(str); ++i)
		{
			patternMap[patternChar] = getNewString(str, strIndex, strIndex + i);
			std::cout << "adding new string: " <<  patternMap[patternChar] << std::endl;

			if (pattern_match(str, strIndex + i + 1, pattern, patternIndex + 1))
			{
				return true;
			}
		}

		delete patternMap[patternChar];
		patternMap[patternChar] = NULL;

		if (patternIndex + 1 == strlen(pattern))
		{
			std::cout << "success: " << std::endl;
			return true;
		}
	}
	else
	{
		std::cout << "existing pattern: " << patternChar << std::endl;
		char* expectedStr = patternMap[patternChar];

		for (unsigned int i = 0; i + strIndex < strlen(str); ++i)
		{
			char* current = getNewString(str, strIndex, strIndex + i);
			std::cout << "compare: " << current << std::endl;
			if (strcmp(expectedStr, current) == 0)
			{
				std::cout << "Pattern match " << std::endl;

				if (patternIndex + 1 == strlen(pattern))
				{
					if (strIndex + i + 1== strlen(str))
					{
						std::cout << "success: " << std::endl;
						return true;
					}
					else
					{
						//this is the last pattern but there are more letters so return false
						// ef  MO T MO K
						// pat a  b a
						std::cout << " More letters after final match, strIndex: " << strIndex + i << " len: " << strlen(str) << std::endl;
						return false;
					}
				}
				else
				{
					// this is not the last pattern so move on
					// str: MO T MO K
					// pat: a  b a  c
					if (pattern_match(str, strIndex + i + 1, pattern, patternIndex + 1))
					{
						return true;
					}
				}
			}
		}
	}

	std::cout << "the end: " << std::endl;
	return false;

}

#endif /* PATTERN_MATCHING_H_ */
