#include <iostream>

auto foo(auto x, auto y)
{
	std::cout << "auto version of x and y called " << std::endl;
	auto result = x + y;

	if (result > 0)
	{
		return result;
	}
	else
	{
		return 1.0;
	}
}

auto foo(int x, int y)
{
	std::cout << "int version of x and y called " << std::endl;
	return x + y;
}
