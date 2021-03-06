#include "Containers.h"
#include "Iterators.h"
#include "Algorithms.h"
#include "Functors.h"
#include "ProgrammingStl.h"

#include <string>
#include <vector>


int main(int argc, char* argv[])
{
#if 0
	int* t= (int*)operator new(sizeof(int) * 100);
	int* arrInts= new(t)int(1);

	std::vector<int, CustomAllocator<int>> vect;
	vect.push_back(1);
	std::cout << *vect.begin() << std::endl;
#endif

#if 0
	std::cout << "size of string is " << sizeof(std::string) << std::endl;
	std::cout << "size of vector is " << sizeof(std::vector<int>) << std::endl;
	vectorOfBools();
#endif

	//Algorithms and Iterators
#if 0
	//setComparatorTest();
	//setOfPointers();
	//manual_remove_example();
	//modifyElementAssociativeContainer();
	//sortedVector();
	//mapOperators();
	//mapUpperLowerBounds();
	//convertConstToNonConstIter();
	//reverseIterator();

	//insertVector();
	//readFromFile();
	//transform();
	//partialSort();
	//nthElement();
	//medianLevel();
	//removeExample();
	//memFnTest();
	//std::cout << ciStringCompare("Hello", "Hellz") << std::endl;
	//accumulate();
#endif

#if 0
	int x=0;
	auto y= RefWrapper<int>(x);
	proxy(y);
	std::cout << "X is " << x << std::endl;
	std::cout << "Y is " << y << std::endl;
	std::cout << "bool is " << bool(true) << std::endl;
#endif

	//efficientStringAddition();
	//readArrayAddsDequeue();
	//assignTest();
	//findSet();
	keepListSorted();

}
