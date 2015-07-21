#include "Containers.h"
#include "Iterators.h"

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
	//setComparatorTest();
	//setOfPointers();
	//manual_remove_example();
	//modifyElementAssociativeContainer();
	//sortedVector();
	//mapOperators();
	//mapUpperLowerBounds();
	//convertConstToNonConstIter();
	//reverseIterator();
	insertVector();

}
