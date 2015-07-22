#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <vector>
#include <iterator>
#include <algorithm>
#include <boost/bind.hpp>


template <typename T>
class MemFun
{
public:
	MemFun(bool (T::*f)()) : m_funct(f)
	{

	}

	bool operator ()(T& obj)
	{
		return (obj.*m_funct)();
	}

private:
	bool (T::*m_funct)();
};

class TestClass
{
public:
	TestClass(int value) : m_value(value)
	{

	}

	bool isGreaterThanZero()
	{
		return m_value > 0;
	}

	friend ostream& operator << (std::ostream& stream, const TestClass& test)
	{
		return stream <<  test.m_value;
	}

private:
	int m_value;
};

void memFnTest()
{
	MemFun<TestClass> obj(&TestClass::isGreaterThanZero);
	std::vector<TestClass> vec= { TestClass(1), TestClass(0),  TestClass(0), TestClass(2) };
	print_cont(vec);
	//vec.erase(std::remove_if(vec.begin(), vec.end(), std::mem_fun_ref(&TestClass::isGreaterThanZero)), vec.end());
	vec.erase(std::remove_if(vec.begin(), vec.end(), obj), vec.end());
	print_cont(vec);
}

void transform()
{
	std::vector<int> input= { 1, 2 ,3 ,4 , 5 };
	std::vector<int> output;
	output.reserve(input.size());

	std::transform(input.begin(), input.end(), std::back_inserter(output), boost::bind(std::plus<int>(), _1, 2));
	//std::transform(input.begin(), input.end(), std::inserter(output, output.begin() + output.size()/2), boost::bind(std::plus<int>(), _1, 2));
	print_cont(output);
}

// 3 5 8 9 10 3 1
void partialSort()
{
	//Find the best two in order 10, 9 .....
	std::vector<int> vec= { 3 ,5 ,8 , 9, 10, 3, 1 };
	print_cont(vec);
	std::partial_sort(vec.begin(), vec.begin() + 2, vec.end(), std::greater<int>());
	print_cont(vec);
}

// 3 5 8 9 10 3 1
void nthElement()
{
	std::vector<int> vec= { 3 ,5 ,8 , 9, 10, 3, 1 };
	print_cont(vec);
	std::nth_element(vec.begin(), vec.begin() + 2, vec.end(), std::greater<int>());
	print_cont(vec);
}

// 1 5 2 3 4
void medianLevel()
{
	std::vector<int> vec= { 1, 5, 2 , 3 , 4, 8};
	print_cont(vec);
	auto mid= vec.begin() + vec.size() / 2;
	std::nth_element(vec.begin(), mid, vec.end(), std::less<int>());
	print_cont(vec);
}


// REMOVE doesn't remove anything from the container because it can't  as it doesn't know the container size
void removeExample()
{
	std::vector<int> vec= { 1, 5, 2 , 3 , 4, 8};
	print_cont(vec);
	auto newLogicalEnd= std::remove_if(vec.begin(), vec.end(), boost::bind(std::greater<int>(), _1, 3));
	print_cont(vec);
	vec.erase(newLogicalEnd, vec.end());
	print_cont(vec);
}


#endif
