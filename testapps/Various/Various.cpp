#include <iostream>
#include <functional>

template <typename T>
void changeValue(T a)
{
	++a;
}

int main(int argc, char* argv[])
{

	int x= 1;
	changeValue(x);
	std::cout << "value of x is " << x << std::endl;
	changeValue(std::ref(x));
	std::cout << "value of x is " << x << std::endl;
}
