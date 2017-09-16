#ifndef MIN_COST_IN_MATRIX_H_
#define MIN_COST_IN_MATRIX_H_

#define MAX_MATRIX_SIZE 2
#include <algorithm>

unsigned minCostMatrix(unsigned costMatrix[MAX_MATRIX_SIZE][MAX_MATRIX_SIZE], int x, int y, int level)
{
	std::cout << "X: " << x << " Y: " << y << " level: " << level << std::endl;

	if (x == 0 && y == 0)
	{
		return costMatrix[0][0];
	}
	else if (x < 0 || x >= MAX_MATRIX_SIZE || y< 0 || y>= MAX_MATRIX_SIZE)
	{
		return 0xFFFFFFFF;
	}

	auto result = costMatrix[y][x] + std::min(minCostMatrix(costMatrix, x - 1, y - 1, level + 1) ,
			   	   	   std::min(minCostMatrix(costMatrix, x - 1, y, level + 1),
					   minCostMatrix(costMatrix, x, y - 1, level + 1)));

	std::cout << "min cost x: " << x << " y: " << y << " = " <<  result << " level: " << level << std::endl;

	return result;

}

#endif /* MIN_COST_IN_MATRIX_H_ */
