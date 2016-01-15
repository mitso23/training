#include "Basic.h"
#include "Medium.h"


int main(int argc, char* argv[])
{
	//testConstructionDestructionOrder();
	//testCopyAssignementOperators();
	//testPolymorphism();

	//misUseOfDelete();
	//throwException();

#if 0
	try
	{
		f();
	}
	catch(const char* str)
	{
		std::cout << "string exception caught" << std::endl;
	}
	catch(int)
	{
		std::cout << "Int exception caught" << std::endl;
	}
	catch(std::exception& e)
	{
		std::cout << "Exception caught" << e.what() << std::endl;
	}
	catch(...)
	{
		std::cout << "Exception caught"<< std::endl;
	}
#endif

#if 0
	std::list<Bank> banks;
	banks.push_back(Bank("Royal Bank of Scotland", 9, 16)); // 09:00 - 16:00
	banks.push_back(Bank("Morgan Stanley", 11, 17)); // 11:00 - 17:00
	banks.push_back(Bank("JP Morgan", 14, 20)); // 14:00 - 20:00
	banks.push_back(Bank("National Australia Bank", 2, 7)); // 02:00 - 07:00

	std::vector<Order> testOrders { { 10, 17 }, // 10:00 - 17:00   // canTrade returns true
			{ 15, 21 }, // 15:00 - 21:00    //         returns false
			{ 4, 10 }, // 04:00 - 10:00    //         returns false
			};

	for (auto&& order : testOrders) {
	        if (canTrade(order, banks)) {
	            std::cout << "TRADE VALID" << std::endl;
	        } else {
	            std::cout << "TRADE FAILED" << std::endl;
	        }
	    }
#endif

	//functorExample();
	downCastringTest();
}
