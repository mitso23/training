#include <iostream>
#include <functional>
#include <iterator>
#include <string>
#include <utils/Noisy.h>
#include <sstream>

void reverseSentence(const std::string& str)
{
	std::stringstream data(str);
	std::string word;

	while(data >> word)
	{
		std::string reversedWord;
		std::copy(word.rbegin(), word.rend(), std::back_inserter(reversedWord));
		std::cout << reversedWord << " ";
	}

	std::cout << std::endl;
}

int main(int argc, char* argv[])
{
	std::string temp("Hello world");

	reverseSentence(temp);
}
