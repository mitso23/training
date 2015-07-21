#ifndef ITERATORS_H
#define ITERATORS_H

#include <string.h>
#include <fstream>
#include <istream_iterator>

//There is implicit convertion from iterator to const_iterator in most cases
//Do not use explicit casts to convert from const_iterator to iterator (it might work only for vector and string as they are plain pointers)
void constIterator()
{
	std::vector<int> vec;
	std::vector<int>::iterator iter;
	std::vector<int>::const_iterator constIter;
	iter= vec.begin();
	constIter= vec.end();

	if (iter == constIter)
	{
		std::cout << "yupii" << std::endl;
	}
}

void convertConstToNonConstIter()
{
	std::vector<int> vec= { 1, 2 };
	std::vector<int>::iterator iter;
	std::vector<int>::const_iterator constIter;
	iter= vec.begin();
	constIter= ++vec.begin();

	auto diff= std::distance<std::vector<int>::const_iterator>(iter, constIter);
	std::advance(iter, diff);
	std::cout << "iter: " << *iter << std::endl;
}

// 1 2 3 4 5
// begin is 1 end is after 5
// rbegin is 5 rend is before 1
// begin(1) 2 3 4 5 end
// rend 1 2 3 4 rbegin(5)

void reverseIterator()
{
	std::vector<int> vec= { 1, 2, 3, 4, 5  };

	auto it= ++vec.rbegin();
	std::cout << "rev: " << *it << std::endl;
	auto it2= it.base();
	std::cout << "it2: " << *it2 << std::endl;
	it2++;
	std::cout << "it2++: " << *it2 << std::endl;
}

void insertVector()
{
	std::vector<int> vec= { 1, 2, 3, 4, 5  };
	auto it= ++vec.rbegin();
	std::cout << "inserting at it " << *it << std::endl;
	auto it2= it.base();
	print_cont(vec);
	vec.insert(it2, 10 );
	print_cont(vec);
}

void readFromFile()
{
	std::ifstream f("/home/mitso/training/resources/test.txt");
	if (!f)
	{
		std::cerr << "Error opening file " << strerror(errno) << std::endl;
	}

	std::string str(istream_iterator<)
}

#endif
