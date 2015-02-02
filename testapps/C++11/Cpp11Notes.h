#ifndef CPP11NOTES_H_
#define CPP11NOTES_H_

#include <cstdio> // easier than iostream for formatted output
#include <iostream>
#include <iterator>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <map>

typedef std::map<std::string, size_t> word_count_type_t;
typedef std::unordered_map<std::string, size_t> word_count_type2_t;


inline bool compare(std::pair<std::string, size_t> firstItem, std::pair<std::string, size_t> secondItem)
{
	if(firstItem.second < secondItem.second)
	{
		return false;
	}
	else if (firstItem.second > secondItem.second)
	{
		return true;
	}
	else
	{
		return firstItem.first < secondItem.first;
	}
}

std::vector< std::pair<std::string, size_t>> getWords(const char* const fileName);

std::vector< std::pair<std::string, size_t>> getWords2(const char* const fileName);

inline std::ostream&  operator << (std::ostream& stream, const std::vector< std::pair<std::string, size_t>>& v)
{
	for(auto it=v.begin(); it != v.end(); ++it)
	{
		stream << "word: " << it->first << " count: " << it->second << std::endl;
	}

	return stream;


}


#endif /* CPP11NOTES_H_ */
