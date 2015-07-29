#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <vector>
#include <iterator>
#include <algorithm>
#include <boost/bind.hpp>

//NOTE most algorithms that expect a container to be sorted expect ascending order like binary_search

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

class Accumulator
{

public:
	Accumulator() : m_sum(0)
	{

	}

	void operator()(int data)
	{
		m_sum+= data;
	}

	int getSum() const
	{
		return m_sum;
	}

private:
	int m_sum;
};

void accumulate()
{
	std::vector<int> vec= { 1, 2 ,3 ,4 };
	std::cout << std::accumulate(vec.begin(), vec.end(), 1, std::multiplies<int>()) << std::endl;
	std::cout << std::for_each(vec.begin(), vec.end(), Accumulator()).getSum() << std::endl;
}

int ciCharCompare(char c1, char c2)
{
	int upper1= std::tolower(c1);
	int upper2= std::tolower(c2);

	if (upper1 == upper2)
	{
		return 0;
	}
	else if (upper1 < upper2)
	{
		return -1;
	}
	else
	{
		return 1;
	}
}

int ciStringCompareImpl(const string& s1, const string& s2);

//see below for
// implementation
int ciStringCompare(const string& s1, const string& s2)
{
	if (s1.size() <= s2.size())
		return ciStringCompareImpl(s1, s2);
	else
		return -ciStringCompareImpl(s2, s1);
}

int ciStringCompareImpl(const string& s1, const string& s2)
{
	//we could use the mismatch STL algorithm in this case
	auto it1= s1.begin();
	for (auto it2= s2.begin(); it2 != s2.end(); ++it2)
	{
		auto ret= ciCharCompare(*it1, *it2);
		++it1;
		if (ret == 0)
		{
			continue;
		}
		else
		{
			return ret;
		}
	}

	if (s1.size() < s2.size())
	{
		return -1;
	}
	else if (s1.size() > s2.size())
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

#endif
