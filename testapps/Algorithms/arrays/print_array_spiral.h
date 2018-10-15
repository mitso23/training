/*
 * print_array_spiral.h
 *
 *  Created on: 1 Aug 2018
 *      Author: mitso23
 */

#ifndef PRINT_ARRAY_SPIRAL_H_
#define PRINT_ARRAY_SPIRAL_H_


//this is incorrect
#include <stdio.h>
#define R 3
#define C 6

void spiralPrint(int a[R][C])
{
	int startX = 0;
	int startY = 0;

	int width = C;
	int height = R;

	while(startX <= width && startY <= height)
	{
		std::cout << "startX: " << startX << " startY: " << startY << " width: " << width << " height: " << height << std::endl;

		//print first row
		for(int x=startX; x< width + startX; ++x)
		{
			std::cout << a[startY][x] << " ";
		}

		//print last column
		for(int y=startY + 1; y< height + startY; ++y)
		{
			std::cout << a[y][startX + width - 1] << " ";
		}

		//print last row
		for (int x = startX + width - 2; x >= startX; --x)
		{
			std::cout << a[startY + height - 1][x] << " ";
		}

		//print first row
		for(int y= startY + height - 2; y> startY; --y)
		{
			std::cout << a[y][startX] << " ";
		}

		startX+=1;
		startY+=1;
		width-=2;
		height-=2;
	}
}


#endif /* PRINT_ARRAY_SPIRAL_H_ */
