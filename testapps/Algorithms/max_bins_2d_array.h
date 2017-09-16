#ifndef MAX_BINS_2D_ARRAY_H_
#define MAX_BINS_2D_ARRAY_H_

#include <math.h>

#define MAX_BIN_ARRAY_SIZE 10

struct BinCoordinates
{
	unsigned int x;
	unsigned int y;
};

unsigned int BinArray[MAX_BIN_ARRAY_SIZE][MAX_BIN_ARRAY_SIZE];
unsigned int maxBinCount = 0;

BinCoordinates binCoordinates[MAX_BIN_ARRAY_SIZE * MAX_BIN_ARRAY_SIZE];

bool CheckIfAddingBinPossible(unsigned int currentX, unsigned int currentY, unsigned index)
{
	for(unsigned int i=0; i<index; ++i)
	{
		unsigned int x = binCoordinates[i].x;
		unsigned int y = binCoordinates[i].y;

		double distance = sqrt((y-currentY)*(y-currentY) + (x-currentX)*(x-currentX));
		//std::cout << "distance: " << distance << " x: " <<  binCoordinates[i].x << " y: " << binCoordinates[i].y << std::endl;
		if (distance == 2.0)
		{
			return false;
		}
	}

	return true;
}

void print(unsigned int currentX, unsigned int currentY, unsigned int level, unsigned int index)
{
	for(unsigned int i=0; i< level; ++i)
	{
		std::cout << " ";
	}
	std::cout << "X: " << currentX << " Y: " << currentY << " level: " << level << " index: " << index << std::endl;
}

void printBinArray(unsigned int maxY, unsigned int maxX)
{
	for(unsigned int j=0; j< maxY; ++j)
	{
		for(unsigned int i=0; i< maxX; ++i)
		{
			std::cout << BinArray[j][i]  << " ";
		}

		std::cout << std::endl;
	}

	std::cout << std::endl;
}

void maxBinsArray(unsigned int currentX, unsigned int currentY,
		unsigned int maxX, unsigned int maxY, unsigned int level, unsigned int index)
{
	if (currentX >= maxX || currentY >= maxY)
	{
		//std::cout << " returning " << std::endl;
		return;
	}

	for(unsigned int j=currentY; j< maxY; ++j)
	{
		for(unsigned int i=currentX; i< maxX; ++i)
		{
			unsigned int nextX = currentX;
			unsigned int nextY = currentY;
			unsigned int nextIndex = index;

			if (CheckIfAddingBinPossible(i, j, index))
			{
				BinCoordinates coord;
				coord.x = currentX;
				coord.y = currentY;

				binCoordinates[index] = coord;
				nextIndex = index + 1;

				BinArray[j][i] = 1;

				if (index > maxBinCount)
				{
					maxBinCount = index + 1;
					std::cout << "max: " << maxBinCount << std::endl;
					printBinArray(maxY, maxX);
				}
			}

			if (i + 1 < maxX)
			{
				nextX = i + 1;
			}
			else
			{
				nextX = 0;
				nextY = j + 1;
			}

			unsigned remaining = (maxY - j)*(maxX - i);
			if (maxBinCount >= index + remaining)
			{
				return;
			}

			maxBinsArray(nextX, nextY, maxX, maxY, level + 1, nextIndex);
			if (j == maxY - 1 && i == maxX - 1)
			{
				//printBinArray(maxY, maxX);
			}

			BinArray[j][i] = 0;
		}
}
}



#endif /* MAX_BINS_2D_ARRAY_H_ */
