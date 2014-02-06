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
#endif

	//mapOperations();
	Noisy n3= testFunc(Noisy());

	std::cout << "n3 id " << n3 << std::endl;
	NoisyReport* nr = NoisyReport::getInstance();
	delete nr;
}

