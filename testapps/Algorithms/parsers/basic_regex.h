#ifndef STRINGS_H_
#define STRINGS_H_

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <list>
#include <utils/utils.h>
#include <unordered_set>
#include <iterator>

#include <string.h>

//"/home/mitso23/skatttas", "/home/mitso23/skat*a*"
// abcdefsdef", "abc*def"
bool checkPattern(const char* str, const char* pattern)
{
	printf("str[0] pattern[0] %c : %c\n", str[0], pattern[0]);

	if (str[0] == '\0')
	{
		return true;
	}
	else if (pattern[0] == '*' && pattern[1] == '\0')
	{
		return true;
	}
	else if(str[0] == pattern[0])
	{
		return checkPattern(str+1, pattern + 1);
	}
	else if (pattern[0] == '*')
	{
		return checkPattern(str + 1, pattern);
	}
	else if (pattern[0] == '*' && str[0] == pattern[1])
	{
		return checkPattern(str+1, pattern + 1);
	}
	else if (str[0] != pattern[0])
	{
		return false;
	}
	else
	{
		return false;
	}
}

typedef enum
{
	PARSING_CHARACTER,
	STAR_FOUND,
	MATCHING_CHARACTER_AFTER_STAR,
	NOT_MATCHING_CHARACTER_AFTER_STAR

}parsing_state_t;

std::ostream& operator << (std::ostream& str, parsing_state_t state)
{
	switch(state)
	{
		case PARSING_CHARACTER : return str << "PARSING_CHARACTER";
		case STAR_FOUND : return str << "STAR FOUND";
		case MATCHING_CHARACTER_AFTER_STAR : return str << "MATCHING_CHARACTER_AFTER_STAR";
		case NOT_MATCHING_CHARACTER_AFTER_STAR : return str << "NOT_MATCHING_CHARACTER_AFTER_STAR";
		//NOTE: DO NOT PUT DEFAULT CASE
	}

	return str << "UNKNOWN";
}

void debugStateMachine(const char* str, const char* pattern, unsigned str_index, unsigned pattern_index, parsing_state_t state)
{
	std::cout << "state: " << state << " str [" << str_index
			<< "] = " << str[str_index] << " pattern [" << pattern_index << "] ="
			<< pattern[pattern_index] << std::endl;
}

// abcdefsdef", "abc*def"
bool checkPattern2(const char* str, const char* pattern)
{
	parsing_state_t state= PARSING_CHARACTER;
	unsigned lastStarPosPattern= 0;
	unsigned int len= strlen(str);
	unsigned int patlen= strlen(pattern);
	unsigned str_index= 0, pattern_index= 0;

	for(; str_index< len;)
	{
		if (pattern_index == patlen && (state == MATCHING_CHARACTER_AFTER_STAR || state == STAR_FOUND))
		{
			pattern_index= lastStarPosPattern;
			if (lastStarPosPattern < patlen - 1)
				++pattern_index;
		}

		debugStateMachine(str, pattern, str_index, pattern_index, state);

		if (state == PARSING_CHARACTER)
		{
			if (str[str_index] == pattern[pattern_index])
			{
				++str_index;
				++pattern_index;
			}
			else if (pattern[pattern_index] == '*')
			{
				state= STAR_FOUND;
				lastStarPosPattern= pattern_index;
				++pattern_index;
			}
			else
			{
				return false;
			}
		}
		else if (state == STAR_FOUND)
		{
			if (pattern[pattern_index] == '*')
			{
				lastStarPosPattern = pattern_index;
				++pattern_index;
			}
			else if (str[str_index] == pattern[pattern_index])
			{
				state= MATCHING_CHARACTER_AFTER_STAR;
				++str_index;
				++pattern_index;
			}
			else if (str[str_index] != pattern[pattern_index])
			{
				state= NOT_MATCHING_CHARACTER_AFTER_STAR;
				++str_index;
			}
		}
		else if (state == NOT_MATCHING_CHARACTER_AFTER_STAR)
		{
			if (pattern[pattern_index] == '*')
			{
				state= STAR_FOUND;
				lastStarPosPattern = pattern_index;
				++pattern_index;
			}
			else if (str[str_index] == pattern[pattern_index])
			{
				++str_index;
				++pattern_index;
				state= MATCHING_CHARACTER_AFTER_STAR;
			}
			else
			{
				pattern_index= lastStarPosPattern;
				++pattern_index;
				++str_index;
			}
		}
		else if (state == MATCHING_CHARACTER_AFTER_STAR)
		{
			if (pattern[pattern_index] == '*')
			{
				state = STAR_FOUND;
				lastStarPosPattern = pattern_index;
				++pattern_index;
			}
			else if (str[str_index] == pattern[pattern_index])
			{
				++str_index;
				++pattern_index;
			}
			else
			{
				pattern_index = lastStarPosPattern;
				++pattern_index;
				state= NOT_MATCHING_CHARACTER_AFTER_STAR;
			}
		}
	}

	if (str_index == len  && pattern_index == patlen)
	{
		return true;
	}
	else if (str_index == len && pattern[pattern_index] == '*')
	{
		return true;
	}
	else
	{
		return false;
	}
}

#endif /* STRINGS_H_ */
