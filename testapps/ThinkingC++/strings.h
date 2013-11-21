#ifndef STRINGS_H_
#define STRINGS_H_

#include<string>

#include<algorithm>
using namespace std;


struct my_char_traits : public char_traits<char>
{

	static bool eq(const char& __c1, const char& __c2)
	{

		return std::toupper(__c1) == std::toupper(__c2);
	}

	static bool ne(char c1st, char c2nd)
	{
		return std::toupper(c1st) != std::toupper(c2nd);
	}
	static bool lt(char c1st, char c2nd)
	{
		return std::toupper(c1st) < std::toupper(c2nd);
	}

	static int compare(const char* str1, const char* str2, size_t n)
	{
		for (int i = 0; i < n; i++)
		{
			if (std::tolower(*str1) > std::tolower(*str2))
				return 1;
			if (std::tolower(*str1) < std::tolower(*str2))
				return -1;
			if (*str1 == 0 || *str2 == 0)
				return 0;
			str1++;
			str2++; // Compare the other chars
		}
		return 0;
	}

};

typedef basic_string<char, my_char_traits , allocator<char> > mystring;

void stringRefCount()
{
	string temp;
	temp= "Hello World";

	string::iterator it= temp.begin();
	string temp2(temp.begin(), temp.end());

	//This will affect only the first string as it uses deep copy
	*it='M';

	cout << "string1: " << temp << endl;
	cout << "string2: " << temp2 << endl;
}

void stringInsert()
{
	std::string temp("Hello World");
	temp.insert(6, "There ");

	cout << temp << endl;
}

void stringReplace()
{
	std::string temp("Hello World");
	temp.replace(6, sizeof("Universe") - 1, "Universe");

	cout << temp << endl;
}

void stlReplace()
{
	std::string temp("Dimitrios Symonidis");

	std::replace(temp.begin(), temp.end(),'i', 'h');

	cout << temp << endl;
}

bool isWhiteSpace(char c)
{
	if (c == ' ')
	{
		return true;
	}
	else
	{
		return false;
	}

	return false;
}

void stripWhiteSpaces()
{

	std::string temp("11Hello1111111");
#if 0
	size_t pos1= temp.find_first_not_of(' ');
	size_t pos2= temp.find_last_not_of(' ');

	std::cout << std::string(temp, pos1, pos2 - pos1 + 1) << std::endl;;
#endif

	temp.erase(remove_if(temp.begin(), temp.end(), isWhiteSpace), temp.end());
	std::cout << temp << std::endl;

	for (std::string::iterator it= temp.begin(); it != temp.end(); ++it)
	{
		std::cout << *it << std::endl;
	}
}

void removeSubString()
{
	std::string temp("Hello World");

	temp.erase(temp.find("World"), sizeof("World") - 1);

	std::cout << temp << std::endl;
}

void compareString()
{
	std::string temp("Hello World");

	if (temp.compare(0, 5, "Hello", 0, 5) == 0)
	{
		cout << "Equal" << endl;
	}
	else
	{
		cout << "Not Equal \n";
	}

}

void reverseIterator()
{
	std::string temp("Hello World");
#if 0
	for(string::const_reverse_iterator it= temp.rbegin(); it != temp.rend(); ++it)
	{
		cout << *it << "\n";
	}
#endif

	char const * ptr= temp.c_str();

	ptr+=temp.length() - 1;

	while(*ptr)
	{
		std::cout << *ptr << std::endl;
		ptr--;
	}
}

void myStringEqualTest()
{
	if (mystring("Hello") == mystring("HELLO"))
	{
		cout << "Equal" << endl;
	}
	else
	{
		cout << "Non Equal" << endl;
	}
}

bool isPalindrome(const std::string& str)
{
	string::const_iterator fwdIter= str.begin();
	string::const_reverse_iterator backIter= str.rbegin();

	while (fwdIter != str.end())
	{
		if (*fwdIter != *backIter)
		{
			return false;
		}

		fwdIter++;
		backIter++;

	}

	return true;
}



#endif /* STRINGS_H_ */
