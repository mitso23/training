/*
 * find_all_possible_islands.h
 *
 *  Created on: 22 Jul 2018
 *      Author: mitso23
 */

#ifndef FIND_ALL_POSSIBLE_ISLANDS_H_
#define FIND_ALL_POSSIBLE_ISLANDS_H_

bool gvisited[5][5];

void find_all_possible_islands_rec(unsigned int mat[5][5], int x, int y, unsigned int visited[5][5])
{
	visited[y][x] = true;
	gvisited[y][x] = true;

	std::cout << "y: " << y << " x: " << x << std::endl;

	if (x + 1< 5 && !visited[y][x+1] && mat[y][x+1] == 1)
	{
		find_all_possible_islands_rec(mat, x+1, y, visited);
	}

	if (x - 1 >= 0 && !visited[y][x-1] && mat[y][x-1] == 1)
	{
		find_all_possible_islands_rec(mat, x-1, y, visited);
	}

	if (y + 1 < 5 && !visited[y+1][x] && mat[y+1][x] == 1)
	{
		find_all_possible_islands_rec(mat, x, y+1, visited);
	}

	if (y - 1 >= 0 && !visited[y-1][x] && mat[y-1][x] == 1)
	{
		find_all_possible_islands_rec(mat, x, y - 1, visited);
	}

	//The 4 diagonal
	if (y - 1 >= 0 && x - 1 >=0 && !visited[y-1][x-1] && mat[y-1][x-1] == 1)
	{
		find_all_possible_islands_rec(mat, x-1, y - 1, visited);
	}

	if (x+1 < 5 && y + 1 < 5 && !visited[y+1][x+1] && mat[y+1][x+1] == 1)
	{
		find_all_possible_islands_rec(mat, x+1, y+1, visited);
	}

	if (x+1 < 5 && y - 1 >=0 && !visited[y-1][x+1] && mat[y-1][x+1] == 1)
	{
		find_all_possible_islands_rec(mat, x+1, y-1, visited);
	}

	if (x-1 >=0 && y + 1 < 5 && !visited[y+1][x - 1] && mat[y+1][x-1] == 1)
	{
		find_all_possible_islands_rec(mat, x-1, y+1, visited);
	}

	std::cout << "backtracking" << std::endl;
	visited[y][x] = false;
}

int find_all_possible_islands(unsigned int mat[5][5])
{
	int count = 0;

	for(unsigned int j=0; j<5; ++j)
	{
		for(unsigned int i=0; i< 5; ++i)
		{
			std::cout << "j: " << j << " i: " << i << " val: " << mat[j][i] << std::endl;

			if (mat[j][i] == 1 && gvisited[j][i] != 1)
			{
				unsigned int visited[5][5];
				memset(&visited[0][0], 0, sizeof(visited));

				find_all_possible_islands_rec(mat, i, j, visited);
				++count;
			}
		}
	}

	return count;
}




#endif /* FIND_ALL_POSSIBLE_ISLANDS_H_ */
