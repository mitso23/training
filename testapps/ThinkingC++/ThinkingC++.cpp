/*
 * ipctest.cpp
 *
 *  Created on: Aug 4, 2013
 *      Author: dimitrios
 */

#include "strings.h"
#include "iostreams.h"
#include "Templates.h"
#include "Stl.h"
#include "Functors.h"
#include "Algorithms.h"
#include "MultipleInheritance.h"
#include "Exceptions.h"
#include "DesignPatterns.h"

#include <vector>
#include <queue>
#include <deque>
#include <set>


Noisy testFunc(const Noisy& noisy)
{
	Noisy n2= noisy;

	return n2;
}

int main(int argc, char* argv[])
{
	//string operations
#if 0
	stringRefCount();

	stringInsert();

	stringReplace();

	stlReplace();

	stripWhiteSpaces();

	removeSubString();

	compareString();

	reverseIterator();

	myStringEqualTest();

	std::cout << isPacopylindrome("m") << endl;

	Coordinates coord;
	coord.x=1;
	coord.y=2;

	std::cout << coord << std::endl;
#endif

	//iostream operations
#if 0
	openReadFile();
	openReadFile();
	seekFile();
	stringStream();
	formatString();
	std::cout << myatoi(1);
	openReadFile();

	memPtr ptr[2]=
	{	&Print::copy, &Print::execute};

	Print printer;
	(printer.*(ptr[0]))(1,2);
	(printer.*(ptr[1]))(1,2);

#endif

	//template operations
#if 0

	Mysequence<Print, std::vector> printer;

	Print print;
	printer.push_back(&print);
	//printer.push_back(new Print());
	printer.apply(&Print::print);

	DECLARE_LIST(int)
	ADD_LIST(1)
	ADD_LIST(2)

#endif

	//STL operations
#if 0
	IOStreamIterators();
	vectorReallocation();
	dequeuReallocation();
	convertContainers();
	listReallocation();
	listOperations();
	testSwap< std::deque<Noisy> >();
	MyList<int> list;
	list.push_back(1);
	list.push_back(2);
	auto iter= list.begin();
	MyList<int>::MyListIterator iter2= list.end();

	std::cout << "value is " << *iter << std::endl;
	++iter;
	std::cout << "value is " << *iter << std::endl;

	std::set<Noisy> myset;
	assoc_generate_n(myset, 10, NoisyGen());
	copy(myset.begin(), myset.end(), ostream_iterator < Noisy > (cout, " "));

	//mapOperations();
	Noisy n3= testFunc(Noisy());

	std::cout << "n3 id " << n3 << std::endl;
	NoisyReport* nr = NoisyReport::getInstance();
	delete nr;
#endif

	//FUNCTION POINTERS
#if 0
	callFunct(1, foo);
	Functor f;
	callFunct(1, f);
	tryRead(f, 1);
	less<int> f2;
	sort(f2);
	testBind2Arg();
	callFunct(1, 1.0f, 2.0, goo);
	bindExample();
	Test test;
	memberFunctionTest(test, &Test::foo1, 2);
	memberFunctionTest(test, &Test::foo2, 2);
#endif

	//ALGORITHMS
#if 0
	countExample();
#endif

	//MULTIPLE INHERITANCE
	MI* b= new MI();
	b->who();

#if 1
	MI2 mi;

	out << "sizeof(mi) = "
	<< hex << sizeof(mi) << " hex" << endl;
	mi.printthis();

#endif
#if 0
	// A second demonstration: AMBIGIUS WILL NOT WORK
	Base1* b1 = &mi;// Upcast
	Base2* b2 = &mi;// Upcast
	out << "Base 1 pointer = " << b1 << endl;
	out << "Base 2 pointer = " << b2 << endl;

	{
		IOFile iofile;
		std::cout << sizeof(iofile) << std::endl;
	}

	Paste1* mypaste1= new Paste1();
	MyBase& myBase= *mypaste1;
#endif


#if 0
	//Exceptions (if exeption during array creation destructors will be called to clean up
	try
	{
		//testException();
		ArrayTest a[3];
	}
	catch(...)
	{
		std::cout << "caught exception" << std::endl;
	}

	//If throw a derived type you can catch it by the base type
	try
	{
		X x;
		x.f();
	}
	catch(X::Trouble& trouble)
	{
		std::cout << "caught exception" << std::endl;
	}
#endif

#if 0
	//Design patterns
	HAL& hal= HAL::getInstanse();

	const char* names[]=
	{	"Square", "Circle", "\0"};

	std::cout << "Running" << sizeof(names) << std::endl;
	for(const char** ptr= names; **ptr; ptr++)
	{
		std::cout << *ptr << std::endl;
		if (ShapeCreator::createShape(*ptr) != NULL)
		{
			std::cout << "Created a shape" << std::endl;
		}
	}

#endif

}

