#include "various.h"
#include "strings.h"

#include <vector>
#include <utils/utils.h>
#include "sorting.h"
#include "stl.h"
#include "coin_changing_problem.h"
#include "mergeSort.h"

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
	//checkIfRotated("abcde", "eabcd");
	//std::vector <int> x = { 1, 1, 2, 2 , 3};
	//removeDuplicateFromSortedArray(x);
	//print_cont(x);

#if 0
	std::vector<int> x1= { 1, 2 , 3 };
	std::vector<int> x2= { 4, 5, 6 };
	std::vector<int> result;

	mergeSortedArrays(x1, x2, result);
	print_cont(result);
#endif
#if 0
	std::vector<unsigned> x1= { 1, 3, 7, 2 , 1, 5 , 6, 2, 9 };
	pairOfNumbersSumToGivenN(x1, 10);
#endif

	//auto result= checkPattern("/home/mitso23/skatttas", "/home/mitso23/skat*a");
	//auto result= checkPattern2("abkkjkjcdefg", "ab*cdefg");
	//auto result= checkPattern2("ab", "ab*");
	//auto result= checkPattern2("abcccccc", "ab*c");
	//auto result= checkPattern2("abccccccccd", "ab*c");
	//auto result= checkPattern2("a", "*a");
	//auto result= checkPattern2("abc", "ab*c");
	//auto result= checkPattern2("a", "*a");
	//auto result= checkPattern2("a", "*");
	//auto result= checkPattern2("abcdefg", "a*cd*fg");
	//auto result= checkPattern2("abcdefg", "a*cd*fg*");
	//auto result= checkPattern2("abcdefg", "a*cd*fkg");
	//auto result= checkPattern2("abcdefg", "a*cd*fgl");

	//unsigned x[] = { 4, 3, 1};
	//std::cout << calculateMinNumberCoins(x, sizeof(x)/sizeof(x[0]), 10);
	//std::cout << count2({1,3,4}, 6) << std::endl;;

	unsigned x[] = { 2, 1, 4, 3, 9, 4 , 8 , 1, 11 , 12 , 15 };
	mergeSort(x, 0, sizeof(x)/sizeof(unsigned));

	for (unsigned int i=0; i<  sizeof(x)/sizeof(unsigned); ++i)
	{
		std::cout << x[i] << std::endl;
	}
}
