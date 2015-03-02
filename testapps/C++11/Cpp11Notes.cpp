#include "Cpp11Notes.h"

// using C++98 notation
std::vector< std::pair<std::string, size_t>> getWords(const char* const fileName)
{
	std::ifstream f(fileName);

	if(!f)
	{
		std::cerr << "Failed to open file: " << std::endl;
		return std::vector< std::pair<std::string, size_t> >();
	}

	word_count_type_t wordCount;
	for(std::string word; f >> word; ++wordCount[word]);

	std::vector< std::pair<std::string, size_t> > v;
	v.reserve(std::distance(wordCount.begin(), wordCount.end()));
	std::copy(wordCount.begin(), wordCount.end(), back_inserter(v));
	std::sort(v.begin(), v.end(), compare);

	return v;
}

// Do the same thing using C++11 notation
std::vector< std::pair<std::string, size_t>> getWords2(const char* const fileName)
{
	std::ifstream f(fileName);

	if(!f)
	{
		std::cerr << "Failed to open file: " << std::endl;
		return std::vector< std::pair<std::string, size_t> >();
	}

	word_count_type2_t wordCount;
	for(std::string word; f >> word; ++wordCount[word]);

	std::vector< std::pair<std::string, size_t> > v;
	v.reserve(std::distance(wordCount.begin(), wordCount.end()));
	std::copy(wordCount.begin(), wordCount.end(), back_inserter(v));
	std::sort(v.begin(), v.end(), [](std::pair<std::string, size_t> firstItem, std::pair<std::string, size_t> secondItem) { return firstItem.second > secondItem.second; } );

	return v;
}
