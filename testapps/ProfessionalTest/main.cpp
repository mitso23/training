/*
 * main.cpp
 *
 *  Created on: 29 Apr 2018
 *      Author: mitso23
 */

#include "CorruptedFile.h"
#include "WindowManager.h"

#include <vector>
#include <string.h>
#include <memory>
#include <unistd.h>

FILE* fp = nullptr;

int main(int argc, char* argv[])
{

	fp = fopen("/tmp/debug.txt", "w");
	if (!fp)
	{
		std::cout << "SHIT" << std::endl;
		return 0;
	}
#if 0
	CreateTestData();
	FindMissingFileContentsOptimized();
	//FindMissingFileContents();
	std::cout << "numberOfReadsFromFile: " << numberOfReadsFromFile
			<< " numberOfReadsFromCurruptedFile: "
			<< numberOfReadsFromCurruptedFile << std::endl;
#endif



	DrawCoordinateSystem(50, 50);

	Rectangle rec1(Coordinate(10, 20), 10, 5);
	DrawRectangle(rec1, 1);

	Rectangle rec2(Coordinate(30, 20), 5, 5);
	DrawRectangle(rec2, 2);


	Rectangle rec3(Coordinate(30, 40), 10, 8);
	DrawRectangle(rec3, 3);

	Rectangle rec4(Coordinate(2, 2), 50, 40);
	DrawRectangle(rec4, 4);

	Move(4, 2, 45);
	Move(3, 30, 30);
#if 0
	Front(3)

	for(unsigned int i=0; i< 10000; ++i)
		Move(3, 30, 70 + i%20);
#endif
}
