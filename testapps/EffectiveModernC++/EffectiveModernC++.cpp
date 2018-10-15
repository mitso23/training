#include "SmartPointers.h"
#include "TypeDeduction.h"
#include "ModernC++.h"
#include "RValueReferences.h"
#include "lambdas.h"
#include "Concurrency.h"

namespace CustomInteger
{

struct NumberTicks {};
struct NumberPulses {};

template <typename tag>
class Integer
{
public:
	constexpr explicit Integer(int _data ) : data(_data)
	{

	}

	constexpr int get() const
	{
		return data;
	}

private:
	int data;
};


typedef Integer<NumberTicks> NumberTicks_t;
typedef Integer<NumberPulses> NumberPulses_t;

int operator + (const NumberTicks_t& ticks, const NumberPulses_t& pulses)
{
	return ticks.get() + pulses.get();
}

void addTwoNumbers(const NumberTicks_t& a, const NumberPulses_t& b)
{
	auto c = a + b;
	std::cout << c << std::endl;
}

};

class FruitsEnum
{
public:
	enum Fruits
	{
		APPLE
	};
};

enum class Fruits : int
{
	APPLE
};

int gSem = 1;

void dummyThread()
{
	while(gSem)
	{
		std::cout << "running: " << std::endl;
		sleep(1);
	}

	std::cout << "finished: " << std::endl;
}

int foo(int x)
{

}

int main(int argc, char* argv[])
{
#if 0
	std::vector<int> x = { 1,2 };
	std::cout << getValue(x, 0) << std::endl;
#endif

#if 0
	auto investment = Stock::makeInvestment(1);
	std::shared_ptr<Investment> sharedInvestment = std::move(investment);
#endif

#if 0
	MoveSharedPtr();
#endif

#if 0
	testSharedFromThis();
#endif

#if 0
	auto listener = CListener::create();
	Observer observer;
	observer.AddListener(listener);
	listener = nullptr;
	observer.Notify();
#endif

	//testMakeUniquePtr();
	//testInitializerListMakeSharedPtr();
	//MoveAutoPtrInContainer();
	//iterateOverUnorderMap();
	//AutoToProxyClass();
	//differentTypeInitialization();
	//testRemoveReference();
	//testUniversalRefence();
	//test_my_move();
	//testScopedPtrMove();
	//std::cout << *testScopedPtrFromFunction() << std::endl;
	ScopedPtr<Noisy> res = testScopedPtrFromFunctionNoisy();

#if 0
	Matrix m1(1, 2);
	Matrix m2(3,4);

	auto m3 = m1 + std::move(m2);
	std::cout << m3 << std::endl;
#endif

#if 0
	Noisy n;
	testTemplReference<Noisy&&>(std::move(n));
#endif

#if 0
	using namespace CustomInteger;

	NumberTicks_t a(1);
	NumberPulses_t b(2);
	addTwoNumbers(a, b);
#endif

#if 0
	TestLambdas t;
	//t.test1();
	//test2();
	Noisy n;
	test3(std::move(n));
#endif

#if 0
	//scheduleTask();
	std::vector<unsigned> v(100000000, 1);
	std::cout << "sum: " << parallelAccumulate(v.begin(), v.end());
#endif

//NOTE: this will throw an exception
#if 0
	auto l= [](){ while(1);};

	std::thread t(l);
	sleep(1);
#endif

#if 0
	auto l =  [&gSem](){ gSem = 0;};
	ThreadRAII t(std::thread(&dummyThread), l, true);
#endif

	test_future();
}
