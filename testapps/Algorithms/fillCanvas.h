/*
 * fillCanvas.h
 *
 *  Created on: 7 Jul 2017
 *      Author: mitso23
 */

#ifndef FILLCANVAS_H_
#define FILLCANVAS_H_

//  0 0 0 0
//  0 0 1 1
//  1 1 0 0

void printCanvas(int data[][4], unsigned int size)
{
	for(unsigned int j=0; j< size; ++j)
	{
		for(unsigned int i=0; i< 4; ++i)
		{
			std::cout << data[j][i] << ' ';
		}
		std::cout << std::endl;
	}
}

void fillCanvas(int (*data)[4], unsigned int size, int number, int X, int Y)
{
	std::cout << "Y: " << Y  << " X: " << " data: " << data[Y][X] << std::endl;

	data[Y][X] = number;

	if (X + 1 < 4 && data[Y][X+1] != number)
	{
		fillCanvas(data, size, number, X + 1, Y);
	}

	if (X - 1 > 0 && data[Y][X-1] != number)
	{
		fillCanvas(data, size, number, X - 1 , Y);
	}

	if (Y + 1 < size && data[Y+1][X] != number)
	{
		fillCanvas(data, size, number, X , Y+1);
	}

	if (Y - 1 > 0 && data[Y-1][X] != number)
	{
		fillCanvas(data, size, number, X, Y - 1);
	}
}


#endif /* FILLCANVAS_H_ */
