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

Noisy process2()
{
	Noisy n;
	return n;
}

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

class Matrix
{

public:
	Matrix(int x, int y) : m_x(x), m_y(y)
	{
		std::cout << "constr" << std::endl;
	}

	Matrix(Matrix&& rhs) : m_x(std::move(rhs.m_x)), m_y(std::move(rhs.m_y))
	{
		std::cout << "move" << std::endl;
	}

	friend std::ostream& operator << (std::ostream& s, const Matrix& rhs)
	{
		s << "x: " << rhs.m_x << " y: " << rhs.m_y;
		return s;
	}

	Matrix& operator +=(Matrix& rhs)
	{
		std::cout << "+=" << std::endl;
		rhs.m_x = rhs.m_x + m_x;
		rhs.m_y = rhs.m_y + m_y;
		return rhs;
	}

	Matrix operator + (Matrix& rhs)
	{
		std::cout << "operator + " << std::endl;
		Matrix temp(rhs.m_x + m_x, rhs.m_y + m_y);
		return temp;
	}

	Matrix operator +=(Matrix&&rhs)
	{
		std::cout << "move: operator+=" << std::endl;
		rhs.m_x = rhs.m_x + m_x;
		rhs.m_y = rhs.m_y + m_y;
		return std::move(rhs);
	}

	Matrix operator + (Matrix&&rhs)
	{
		return std::move(rhs+=*this);
	}

private:
	int m_x;
	int m_y;
};

void testUniversalRefence()
{
	//this is universal reference
	auto&& var = process2();

	//This is rvalue reference
	Noisy&& var2 = process2();

	//This is lvalue reference
	const Noisy& var3 = process2();

	//Access the temporary
	process2().getData();
}


template<typename T>
void testTemplReference(T t)
{

}

void testRemoveReference()
{

	//This will call the lvalue reference
	Noisy n;
	process(std::forward<Noisy&>(n));

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
