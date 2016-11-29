#include "SmartPointers.h"
#include "TypeDeduction.h"

int main(int argc, char* argv[])
{
#if 0
	std::vector<int> x = { 1, 2 };
	std::cout << getValue(x, 0) << std::endl;
#endif

	auto investment = Stock::makeInvestment(1);
}
