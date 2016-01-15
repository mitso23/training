#include "Sorting.h"
#include "various.h"
#include "strings.h"
#include "containers.h"
#include "FinanceStuff.h"

#include <vector>
#include <utils/utils.h>

int main(int argc, char* argv[])
{
	//print_pyramid(7);
	//print_mutation("Dimitrios Symonidis");
	//std::cout << checkAllCharactersUnique("abcd") << std::endl;
	//std::cout << checkAllCharactersUnique("Dimitrios") << std::endl;
	//removeAllDuplicates(std::string("Dimitrios"));

#if 0
	BigInt b1("26");
	BigInt b2("995");

	std::cout << b1 + b2 << std::endl;
#endif

	//std::cout << power(2, 8) << std::endl;

	//std::vector<unsigned> x= { 1, 2 ,3 ,4 ,5, 1 ,1 ,1 ,1 ,1 ,1 , 1, 1 , 2, 2, 2, 3, 4, 5, 5};
	//knapsack(x, 9);
	//combinationStrings("abcde");
	checkIfRotated("abcde", "eabcd");
}
