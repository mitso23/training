/*
 * ipctest.cpp
 *
 *  Created on: Aug 4, 2013
 *      Author: dimitrios
 */

#include "strings.h"
#include "iostreams.h"
#include "Templates.h"

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
	seekFile();
	stringStream();
	formatString();
	std::cout << myatoi(1);

	memPtr ptr[2]= { &Print::copy, &Print::execute };

	Print printer;
	(printer.*(ptr[0]))(1,2);
	(printer.*(ptr[1]))(1,2);
#endif



}


