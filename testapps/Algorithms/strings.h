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

//abc -> bc , cb : abc, bac, bca | acb, cab, cba
void print_mutation(std::string str)
{
	if (str.size() == 1)
	{
		std::cout << str << std::endl;
		return;
	}
	else if (str.size() == 0)
	{
		return;
	}

	std::string begin;
	auto back_it = std::back_inserter(begin);
	*back_it = str[0];

	std::vector<std::string> l;
	l.reserve(1024*1024*100);
	l.push_back(std::move(begin));

	auto it = ++str.begin();

	for (; it != str.end(); ++it)
	{
		permutate(*it, l);
	}

	print_cont(l);
}

bool checkAllCharactersUnique(std::string str)
{
	std::unordered_set<char> s;
	for(auto it=str.begin(); it!= str.end(); ++it)
	{
		if (s.find(*it) != s.end())
		{
			return false;
		}
		else
		{
			s.insert(*it);
		}
	}

	return true;
}

//Dimitrios
void removeAllDuplicates(std::string str)
{
	std::string::iterator new_end= str.end();
	for(auto it=str.begin(); it< new_end; ++it)
	{
		auto l= [it](char c) { if (c == *it) return true; return false; };
		new_end= std::remove_if(it + 1, new_end, l);
	}

	str.erase(new_end, str.end());
	std::copy(str.begin(), str.end(), std::ostream_iterator<char>(std::cout, "")); std::cout << "\n";
}

unsigned level= -1;


//THIS NEEDS MORE WORK
void combinationStrings(const std::string& str, unsigned lvl=0)
{
	++level;

	if (str.empty())
	{
		return;
	}

	if (str.size() == 1)
	{
		//std::cout << "returning: " << str << " : from level " << lvl << std::endl;
		return;
	}
	else
	{
		std::cout << "parent :" << str[0] << " has the following children: " << str << std::endl;
	}

	for(auto it=str.begin(); it != str.end() && it + 1 != str.end(); ++it)
	{
		combinationStrings(std::string(it + 1, str.end()), lvl +1);
		--level;
		//std::cout << "returning: " << *it << " : from level " << lvl << std::endl;
	}
}

// H e l l o
// 0 1 2 3 4
void shiftString(std::string& str, int num)
{
	if (num == 0) return;

	auto temp= str.substr(str.size() - num);

	for(int i=str.size() - 1; i>= 0; --i)
	{
		int index = ((i - num) >= 0) ? (i - num) : (str.size() - (num - i));
		str[i]= str[index];
	}

	std::copy(temp.begin(), temp.end(), str.begin());
}

// Dimitrios --> iosDimitr
bool checkIfRotated(const std::string& str1, const std::string& ref2)
{
	auto cref2= ref2;

	for(auto i= 0U; i< str1.size(); ++i)
	{

		if (str1 == cref2)
		{
			std::cout << "String is rotated " << std::endl;
			return true;
		}
		else
		{
			shiftString(cref2, 1);
			std::cout << cref2 << std::endl;
		}
	}

	return false;
}

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
