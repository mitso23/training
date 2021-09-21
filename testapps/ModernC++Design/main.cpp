#include "PolicyBasedDesign.h"
#include "TypeTraits.h"

#include <iostream>
#include <memory>
#include <functional>
#include <string>
#include <array>
#include <type_traits>

struct IntDeleter
{
	void operator()(int* ptr) const
	{
		delete ptr;
	}

	int x;
};

template<typename T>
class Executor;

template<typename R, typename ...Args>
class Executor<R(Args...)>
{
public:
    //Check if we have a return type to pass to DBUS
    template<typename ReturnValue,
             typename F,
             typename std::enable_if<std::is_void<ReturnValue>::value, int>::type = 0
             >
             ReturnValue Dispatch(F& f, Args... args)
    {
       f(args..., 1, 2);
    }

    // This will be instantiated if we don't have  a return type specified
    template<typename ReturnValue,
             typename F,
             typename std::enable_if<!std::is_void<ReturnValue>::value, int>::type = 0
            >
    ReturnValue Dispatch(F& f, Args... args)
    {
        ReturnValue r;
        return f(args..., 1, 2, r);
    }

    template<typename F>
    R Call(F& f, Args... args)
    {
        return Dispatch<R>(f, args...);
    }
};

void testExecutor(int x, int y, int z)
{
    std::cout << "x: " << x << " y: " << y << " z: " << z << std::endl;
}

int testExecutor2(int x, int y, int& z)
{
    z = 5;
    std::cout << "retrun int, x: " << x << " y: " << y << " z: " << z << std::endl;
}

void testExecutor3(int x, int y)
{
    std::cout << "x: " << x << " y: " << y << std::endl;
}


int main(int argc, char* argv[])
{
    Executor<void (int)> e1;
    e1.Call(testExecutor, 10);

    Executor<int (void)> e2;
    e2.Call(testExecutor2);

    Executor<void ()> e3;
    e3.Call(testExecutor3);

#if 0
	WidgetManager<NewCreator<int>> x;
	std::cout << "sizeof(x): " << sizeof(x) << std::endl;

	std::unique_ptr<int> u_ptr;
	std::unique_ptr<int, IntDeleter> u_ptr1;
	std::unique_ptr<int, IntDeleter> u_ptr2{new int, IntDeleter()};

	std::unique_ptr<int, std::function<void(int*)>> u_ptr3(new int,  [](int*){});

	std::cout << "size of unique_ptr is " << sizeof(u_ptr) << " size of u_ptr1: " << sizeof(u_ptr1) << " u_ptr2:" << sizeof(u_ptr2) << std::endl;


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

#endif

	std::string x = "Hello";
	std::string y = "Dimitrios";

	std::array<std::string, 2> z = {x, y};
	for(const auto v : z)
	{
		std::cout << v << std::endl;
	}

	x = "Skata";


}

