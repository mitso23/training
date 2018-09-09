#include "Basics.h"
#include <iostream>
#include <algorithm>
#include <functional>
#include <list>

struct X
{
	int x;
	int y;
};

int main(int argc, char* argv[])
{

#if 0
	// They all generate the same code, so no code bloating
	Array<int, 3> arr;
	Array<int, 4> arr2;
	Array<char, 4> arr3;
	arr[0] = 1;
	arr[2] = 8;
	arr[3] = 5;

	std::cout << arr[0] << std::endl;
#endif

#if 0
	int* ptr1 = new int(2);
	int* ptr2 = new int(3);

	std::cout << ::max(ptr1, ptr2) << std::endl;
#endif

#if 0
	Stack<int> s1;
	s1.push(1);
	Stack<int> s2 = s1;
	std::cout << "s2: " << s2.GetSize() << "s1: " << s1.GetSize() << std::endl;
#endif

#if 0
	MyClass<int, int> m;
	MyClass<float> m2;
#endif

#if 0
	std::vector<int> src = { 1, 2, 3 };
	std::vector<int> dest;
	auto l = [](const int& val, const int adder)
	{
		return val + 5;
	};

	std::transform(src.begin(), src.end(), std::back_inserter(dest), std::bind(l, std::placeholders::_1, 5));
	//std::transform(src.begin(), src.end(), std::back_inserter(dest), addValue<int, 5>);
	for (auto& value : dest)
		std::cout << value << std::endl;
#endif

#if 0
	Stack<int> s1;
	Stack<int> f1;
	Stack<std::string, std::list<std::string>> str1;
	s1 = f1;
#endif

	X x;
	std::cout << x.x << std::endl;
}
