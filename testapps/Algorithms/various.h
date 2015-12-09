#ifndef VARIOUS_H_
#define VARIOUS_H_

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>


unsigned pow(unsigned number)
{
	unsigned result= 1;
	for(unsigned int i=0; i< number; ++i)
	{
		result*= 2;
	}

	return result;
}

void printSpace(unsigned num)
{
	for (auto j = 0U; j < num; ++j)
	{
		std::cout << " ";
	}
}

void printStars(unsigned num)
{
	for (auto j = 0U; j < num; ++j)
	{
		std::cout << "*";
	}
}

void printNewLine()
{
	std::cout << std::endl;
}


//     **
//    ****
//  ********
void print_pyramid(unsigned height)
{
	unsigned maxNumDots= pow(height);

	for(unsigned int i=1; i<= height; ++i)
	{
		unsigned numDots= pow(i);
		unsigned numSpaces= maxNumDots - numDots;

		printSpace(numSpaces/ 2);
		printStars(numDots);
		printSpace(numSpaces/ 2);
		printNewLine();

	}
}

#endif /* VARIOUS_H_ */
