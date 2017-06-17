#ifndef N_QUEEN_PROBLEM_H_
#define N_QUEEN_PROBLEM_H_

#define MAX_BOARD_SIZE 8

/// 1 0 0
/// 0 0 1
/// 0 0 0

static int numberSolutions = 0;

void printBoard(unsigned int arr[MAX_BOARD_SIZE][MAX_BOARD_SIZE], unsigned expected)
{
	unsigned count = 0;

	for(unsigned int j= 0; j< MAX_BOARD_SIZE; ++j)
	{
			for(unsigned int i=0; i < MAX_BOARD_SIZE; ++i)
			{
				if (arr[j][i] == 1)
				{
					++count;
				}
			}
	}

	if (count == expected)
	{
		for(unsigned int j= 0; j< MAX_BOARD_SIZE; ++j)
		{
			for(unsigned int i=0; i < MAX_BOARD_SIZE; ++i)
			{
				std::cout << arr[j][i];

			}

			std::cout << std::endl;
		}
		std::cout << std::endl;

		++numberSolutions;
	}
}

bool checkIfVerticalPossible(int X, int Y, unsigned int arr[MAX_BOARD_SIZE][MAX_BOARD_SIZE])
{
	int startX = X;

	while(startX < MAX_BOARD_SIZE)
	{
		if (arr[Y][startX] != 0)
		{
			return false;
		}

		++startX;
	}

	startX = X;

	while(--startX >=0)
	{
		if (arr[Y][startX] != 0)
		{
			return false;
		}
	}

	return true;
}

bool checkIfHorizontalPossible(int X, int Y, unsigned int arr[MAX_BOARD_SIZE][MAX_BOARD_SIZE])
{
	int startY = Y;

	while(startY < MAX_BOARD_SIZE)
	{
		if (arr[startY][X] != 0)
		{
			return false;
		}

		++startY;
	}

	startY = Y;

	while(--startY >=0)
	{
		if (arr[startY][X] != 0)
		{
			return false;
		}
	}

	return true;
}

bool checkIfLeftDiagonalPossible(int X, int Y, unsigned int arr[MAX_BOARD_SIZE][MAX_BOARD_SIZE])
{
	int startX = X;
	int startY = Y;

	while(startX >= 0 && startY < MAX_BOARD_SIZE)
	{
		if (arr[startY][startX] != 0)
		{
			return false;
		}

		--startX;
		++startY;
	}

	startX = X;
	startY = Y;

	while(--startY >= 0 && ++startX < MAX_BOARD_SIZE)
	{
		if (arr[startY][startX] != 0)
		{
			return false;
		}
	}

	return true;
}

bool checkIfRightDiagonalPossible(int X, int Y, unsigned int arr[MAX_BOARD_SIZE][MAX_BOARD_SIZE])
{
	int startX = X;
	int startY = Y;

	while(startX < MAX_BOARD_SIZE && startY < MAX_BOARD_SIZE)
	{
		if (arr[startY][startX] != 0)
		{
			return false;
		}

		++startX;
		++startY;
	}

	startX = X;
	startY =Y;

	while(--startX >= 0 && --startY >= 0)
	{
		if (arr[startY][startX] != 0)
		{
			return false;
		}
	}

	return true;
}

void positionNQueens(int startX, int startY, unsigned int arr[MAX_BOARD_SIZE][MAX_BOARD_SIZE], unsigned int level)
{
	for(unsigned int j= startY; j< MAX_BOARD_SIZE; ++j)
	{
		for(unsigned int i=startX; i < MAX_BOARD_SIZE; ++i)
		{
			//std::cout << "x: " << i << " y: " << j << " level: " << level << std::endl;

			if (checkIfVerticalPossible(i, j, arr) && checkIfHorizontalPossible(i, j, arr)
				&& checkIfLeftDiagonalPossible(i, j, arr) && checkIfRightDiagonalPossible(i, j, arr))
			{
				arr[j][i] = 1;
				++level;
				//std::cout << "Going: startX: " << i << " startY: " << j << " level: " << level << std::endl;

				positionNQueens(0, j, arr, level);
				arr[j][i] = 0;
				--level;
				//std::cout << "Returned: startX: " << i << " startY: " << j << " level: " << level << std::endl;
			}

			if (j == MAX_BOARD_SIZE - 1 && i == MAX_BOARD_SIZE - 1)
			{
				printBoard(arr, 8);
			}
		}
	}

	std::cout << " number solutions: " << numberSolutions << std::endl;

	//std::cout << "Returning: startX: " << startX << " startY: " << startY << " level: " << level << std::endl;

}


#endif /* N_QUEEN_PROBLEM_H_ */
