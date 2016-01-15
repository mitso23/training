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
}




#endif /* STRINGS_H_ */
