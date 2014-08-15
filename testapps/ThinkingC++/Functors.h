#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <vector>
#include <functional>

class Test
{
public:
	int z;

	int foo1(int x)
	{
		std::cout << "X= " << x << "Z= " << z << std::endl;
		return x;
	}

	int foo2(int x)
	{
		std::cout << "X= " << x << "Z= " << z << std::endl;
		return x;
	}
};

template<class T, class UnarayFunc>
void callFunct(T arg, UnarayFunc f)
{
	int result= 0;

	result= f(arg);
}

template<class T, class W, class BinaryFunct>
void callFunct(T arg, W arg2, BinaryFunct f)
{
	int result= 0;

	result= f(arg, arg2);
}

template<class T, class W, class K, class Funct>
void callFunct(T arg, W arg2, K arg3, Funct f)
{
	int result= 0;

	result= f(arg, arg2, arg3);
}

void generateExample()
{
	std::vector<int> vec;
	generate_n(back_inserter(vec), 10, rand);
}

template<class InputIter, class Predicate>
void copy_if(InputIter begin, InputIter end, InputIter dest, Predicate f)
{
	InputIter it;
	for (it= begin; it != end; it++ )
	{
		if (f(*it))
		{
			*dest++= *it;
		}
	}
}



template<class BinaryFunction>
void sort(BinaryFunction compare)
{
	int x= 1;
	int y= 2;

	if (compare(1,2))
	{
		std::cout << "1 is less than 2" << std::endl;
	}
}

void tryRead(boost::function<int (int)> f, int arg1)
{
	int result= f(arg1);
}

void testBind2Arg()
{
	int a[]= { 1, 2, 3, 50, 80, 90 };
	std::vector<int> input;
	std::vector<int> output;

	std::copy(a, a + sizeof(a), back_inserter(input));
	std::cout << *std::find_if(input.begin(), input.end(), bind2nd(std::less<int>(), 30)) << std::endl;
}


int foo(int x)
{
	std::cout << x << std::endl;
	return x;
}

int goo(int x, float t, double z)
{
	std::cout << x << std::endl;
	return x;
}

struct Functor
{
	int operator()(int x)
	{
		return x;
	}
};

//In order to call a member function we need an instance of the object
void memberFunctionTest(Test test, int (Test::*ptr)(int), int argument)
{
	(test.*ptr)(argument);
}

//Bind of a member function always requires instance of the class
void bindExample()
{
	boost::function<void (int)> f= boost::bind(&foo, _1);
	Test test;
	boost::function<void (int)> f2= boost::bind(&Test::foo1, &test, _1);
	f2(1);
}

void memFunExample()
{
	std::vector<string> x;
	int result[5]= { 0 };

	x.push_back("Hello");
	x.push_back("World");

	//mem_fun_ref creates a functor object from a function pointer
	//THIS WILL BE CALLED IN TRANSFORM LIKE THIS length(*it)
	std::transform(x.begin(), x.end(), result, std::mem_fun_ref(&string::length));

}


