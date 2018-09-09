/*
 * main.cpp
 *
 *  Created on: 26 Aug 2018
 *      Author: mitso23
 */

#include "optional.h"

#include <iostream>
#include <ostream>
#include <vector>
#include <memory>

template<class T, class... U>
std::unique_ptr<T> make_unique(U&&... u)
{
    return std::unique_ptr<T>(new T(std::forward<U>(u)...));
}


class SimpleObject
{
public:
	SimpleObject(int x, int y)
		: m_x(x)
		, m_y(y)
	{

	}

	friend std::ostream& operator << (std::ostream& lhs, const SimpleObject& rhs)
	{
		return lhs << "x: " << rhs.m_x << " y: " << rhs.m_y << std::endl;
	}

private:
	int m_x;
	int m_y;
};

void testInt()
{
	optional<int> data;
	data = 1;
	if (!data)
	{
		std::cout << "data is not set: " << std::endl;
	}
	else
	{
		std::cout << "data is set: " << *data << std::endl;
	}
}

void testObject()
{
	optional<SimpleObject> obj(2, 1);
	optional<SimpleObject> obj2 = obj;
	optional<SimpleObject> obj3;
	obj3 = obj;
	obj3 = SimpleObject(5, 5);

	if (obj3)
	{
		std::cout << "object two is valid " << *obj3 << std::endl;
	}
	else
	{
		std::cout << "object is not valid " << std::endl;
	}
}

void testVector()
{
	std::vector<uint8_t> data;
	data.push_back(1);
	data.push_back(2);
	data.push_back(3);

	optional<std::vector<uint8_t>> optData;
	optData = data;

	for(unsigned int i=0; i< 3; ++i)
	{
		std::cout << (unsigned)(*optData)[i] << std::endl;
	}
}

void testNullOptAssignment()
{
	optional<int> data;
	data = 1.0f;

	data = nullopt;
	data = 1;
	if (data)
	{
		std::cout << "data is there " << std::endl;
	}
	else
	{
		std::cout << "data is not there " << std::endl;
	}

	if (data == nullopt)
	{
		std::cout << "data is nullptr" << std::endl;
	}
}

union skata
{
	uint8_t dummy;
	SimpleObject obj;

	skata(int x, int y)
		: obj(x, y)
	{

	}
};

int main(int argc, char*argv[])
{
	auto n = make_unique<int>(1);
	testNullOptAssignment();
	testInt();
	testObject();
	testVector();
}
