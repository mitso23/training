#include "SmartPointers.h"
#include "TypeDeduction.h"

int main(int argc, char* argv[])
{
#if 0
	std::vector<int> x = { 1, 2 };
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
	MoveAutoPtrInContainer();
}
