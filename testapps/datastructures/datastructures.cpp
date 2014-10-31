//#include "testList.h"
#include "testQueue.h"

int main(int argc, char* argv[])
{
	//generic list tests
#if 0
	std::cout << "Adding elements to back " << std::endl;
	addElementsToListBack();
	displayIntList();

	std::cout << "delete elements test" << std::endl;
	removeNodeTest();
	displayIntList();

	std::cout << "clear list test " << std::endl;
	addElementsToListFront();
	clearList();

	displayIntList();
#endif

	//dynamic queue test
#if 1
	addElementsTest();
	displayElementsTest();
#endif
}
