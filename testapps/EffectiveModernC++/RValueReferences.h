/*
 * RValueReferences.h
 *
 *  Created on: 23 Jun 2017
 *      Author: mitso23
 */

#ifndef RVALUEREFERENCES_H_
#define RVALUEREFERENCES_H_

#include <type_traits>

template <class T>
struct my_remove_reference
{
	typedef T type;
};

template <class T>
struct my_remove_reference<T&>
{
	typedef T type;
};

template <class T>
struct my_remove_reference<T&&>
{
	typedef T type;
};

template <class T, class U>
struct my_is_same
{
	bool operator()()
	{
		return false;
	}

};

template <class T>
struct my_is_same<T, T>
{
	bool operator()()
	{
		return true;
	}
};

void process(Noisy& n)
{
	std::cout << "lvalue version called " << std::endl;
}

void process(Noisy&& n)
{
	std::cout << "rvalue version called " << std::endl;
}

template<typename T>
void logAndProcess(T&& param)
{
	process(std::forward<T>(param));
}

void testRemoveReference()
{

#if 0
	Noisy n;
	//this will call the lvalue version
	process(n);
	//this will call the rvalue version
	process(std::forward<Noisy>(n));

	//this will do conditional cast
	logAndProcess(n);
#endif

	//int y = 1;
	//eventually what std::mvoe does is a simple cast
	//foo(reinterpret_cast<int&&>(y));


	//auto res = my_is_same<int, int&>()();
	//std::cout << res << std::endl;
	//std::cout << std::is_same<int, my_remove_reference<int&>::type>() << std::endl;
}

#endif /* RVALUEREFERENCES_H_ */
