#ifndef TRAINING_TESTAPPS_FINANCE_PRIMITIVES_H_
#define TRAINING_TESTAPPS_FINANCE_PRIMITIVES_H_

#include <memory>
#include <iostream>
#include <algorithm>
#include <functional>

#include "gmock/gmock.h"
#include "gtest/gtest.h"


using ::testing::AtLeast;
using ::testing::Return;
using ::testing::_;
using testing::MockFunction;


template<typename T>
struct Deleter
{
	void operator()(T* ptr)
	{
		std::cout << "deleting resource" << std::endl;
		delete ptr;
	}
};

class TestBind
{
 public:
	void foo(int x, int y)
	{
		std::cout << "x: " << x << " y: " << y << std::endl;
	}
};

template<typename T>
using SP = std::shared_ptr<T>;

template< std::size_t I, class T >
struct my_tuple_element;

// recursive case
template< std::size_t I, class Head, class... Tail >
struct my_tuple_element<I, std::tuple<Head, Tail...>>
	: my_tuple_element<I-1, std::tuple<Tail...>> { };

// base case
template< class Head, class... Tail >
struct my_tuple_element<0, std::tuple<Head, Tail...>>
{
	using type = Head;
};

template <typename Derived>
class PayOffStrategy
{
 public:
	double payoff(double S)
	{
		static_cast<Derived*>(this)->payoff(S);
	}
};

class CallStrategy : public PayOffStrategy<CallStrategy>
{
 public:
	explicit CallStrategy(double strike)
		: m_strikePrice(strike)
	{

	}

	double payoff(double S)
	{
		return std::max(S - m_strikePrice, 0.0);
	}

 private:
	double m_strikePrice;
};

class MockStrategy : public PayOffStrategy<MockStrategy>
{
 public:
	MOCK_METHOD1(payoff, double(double));
};

class SpreadStrategy : public PayOffStrategy<SpreadStrategy>
{
 public:
	SpreadStrategy(double k1, double k2)
		: m_k1(k1)
		, m_k2(k2)
	{

	}

	double payoff(double S)
	{
		if (S > m_k2)
		{
			return S - m_k2;
		}
		else if (S < m_k1)
		{
			return 0;
		}

		return m_k2 - m_k1;
	}

 private:
	double m_k1;
	double m_k2;
};

class PayOffStrategy2
{
 public:
	using Strategy = std::function<double (double S)>;

	PayOffStrategy2(Strategy&& strategy)
		: m_strategy(strategy)
	{

	}

	double payoff(double S)
	{
		return m_strategy(S);
	}

 private:
	Strategy m_strategy;
};

struct TestObject
{
 public:
	TestObject(int x, int y)
	{

	}
};

#endif
