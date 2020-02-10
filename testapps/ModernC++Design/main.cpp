#include "PolicyBasedDesign.h"
#include "TypeTraits.h"

#include <iostream>
#include <memory>
#include <functional>

struct IntDeleter
{
	void operator()(int* ptr) const
	{
		delete ptr;
	}

	int x;
};

int main(int argc, char* argv[])
{

#if 0
	WidgetManager<NewCreator<int>> x;
	std::cout << "sizeof(x): " << sizeof(x) << std::endl;

	std::unique_ptr<int> u_ptr;
	std::unique_ptr<int, IntDeleter> u_ptr1;
	std::unique_ptr<int, IntDeleter> u_ptr2{new int, IntDeleter()};

	std::unique_ptr<int, std::function<void(int*)>> u_ptr3(new int,  [](int*){});

	std::cout << "size of unique_ptr is " << sizeof(u_ptr) << " size of u_ptr1: " << sizeof(u_ptr1) << " u_ptr2:" << sizeof(u_ptr2) << std::endl;
#endif

	std::cout << "is pointer: " << TypeTraits<int*>::isPointer << std::endl;
	has_type<float, std::tuple<int, int>> res;
	if (res)
	{
		std::cout <<" YUPII";
	}
	else
	{
		std::cout << "SHIT";
	}

	Factory<int, unsigned int, float, double> f;
	auto res2 = f.Get<char>();
}

