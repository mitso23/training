#ifndef MIN_COST_IN_MATRIX_H_
#define MIN_COST_IN_MATRIX_H_

#define MAX_MATRIX_SIZE 3
#include <algorithm>

unsigned minCostMatrix(unsigned costMatrix[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE], int x, int y)
{
	std::cout << "X: " << x << " Y: " << y << std::endl;

	if (x == 0 && y == 0)
	{
		return costMatrix[0][0];
	}
	else if (x < 0 || x >= MAX_MATRIX_SIZE || y< 0 || y>= MAX_MATRIX_SIZE)
	{
		return 0xFFFFFFFF;
	}


	return costMatrix[x][y] + std::min(minCostMatrix(costMatrix, x - 1, y - 1) ,
			   	   	   std::min(minCostMatrix(costMatrix, x - 1, y),
					   minCostMatrix(costMatrix, x, y - 1)));

}

#endif /* MIN_COST_IN_MATRIX_H_ */
