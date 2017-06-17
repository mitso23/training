/*
 * ModernC++.h
 *
 *  Created on: 4 Jun 2017
 *      Author: mitso23
 */

#ifndef MODERNC___H_
#define MODERNC___H_

#include <vector>

class TestWidget
{
public:
	TestWidget(int x, bool y) : m_x(x), m_y(y)
	{
		std::cout << "constructor called: " << std::endl;
	}

	TestWidget(std::initializer_list<Noisy> l)
	{
		std::cout << "initialiser list is called: " << std::endl;
		v = l;
	}

	TestWidget(std::vector<Noisy>& n)
	{
		v = std::move(n);
	}

private:
	int m_x  {0};
	bool m_y {0};
	std::vector<Noisy> v;
};

void differentTypeInitialization()
{
#if 0
	int x(0);
	int xx = 0;
	int xxx = { 0 };

	//This will call the constructor
	Noisy n = { 0 };

	// This will call the copy constructor (compiler optimises and calls the constructor)
	Noisy nn = 0;
#endif
	//NOTE: This will not compile as the brace initialise code doesn't do narrow conversions
	//std::vector<int8_t> x = { 1.0, 2.0 };
	//std::vector<uint8_t> y = { 1, 2 };

	//TestWidget { 1, 2 };

	//This will create two Noisy and copy construct the vector. It is more efficient to use emplace_back
	std::vector<Noisy> k= { Noisy(), Noisy() };

	//TestWidget v(k);
}

#endif /* MODERNC___H_ */
