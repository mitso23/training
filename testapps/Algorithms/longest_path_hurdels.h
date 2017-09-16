/*
 * longest_path_hurdels.h
 *
 *  Created on: 15 Jul 2017
 *      Author: mitso23
 */

#ifndef LONGEST_PATH_HURDELS_H_
#define LONGEST_PATH_HURDELS_H_

#include <queue>
#include <algorithm>

#define X_MAX 3
#define Y_MAX 3

bool visitedPath[Y_MAX][X_MAX];
int maxLength = 0;
std::deque<std::pair<int, int>> pathsFollowed;
static unsigned numberRecursionCalled = 0;

void drawPath(int path[Y_MAX][X_MAX])
{
	return;

	for(int j=0; j< Y_MAX; ++j)
	{
		for (int i=0; i< X_MAX; ++i)
		{
			std::cout << path[j][i] << " ";
		}

		std::cout << std::endl;
	}

	std::cout << std::endl;

	usleep(1000*50);
}

void findLongestPath(int path[Y_MAX][X_MAX], int X, int Y, int level, int& currentLength, int dstX, int dstY)
{
	//std::cout << "X: " << X << " Y: " << Y << " level: " << level << " len: "
		//<< currentLength << " path: " << path[Y][X] <<  std::endl;

	++numberRecursionCalled;
	path[Y][X] = 2;
	pathsFollowed.push_back(std::pair<int,int>(Y,X));

	drawPath(path);

	if (dstX == X && dstY == Y)
	{
		std::cout << "found with length: " << currentLength << std::endl;
		for(const auto& item: pathsFollowed)
		{
			std::cout << "Y: " << item.first << " X: " << item.second << std::endl;
		}

		path[Y][X] = 1;

		if(pathsFollowed.size())
			pathsFollowed.pop_back();

		if (currentLength > maxLength)
		{
			maxLength = currentLength;
		}

		if (currentLength)
			--currentLength;

		return;
	}

	if (X - 1 >= 0  && path[Y][X-1] == 1)
	{
		++currentLength;
		findLongestPath(path, X-1, Y, level + 1, currentLength, dstX, dstY);
	}

	if (X + 1 < X_MAX && path[Y][X+1] == 1)
	{
		++currentLength;
		findLongestPath(path, X+1, Y, level + 1, currentLength, dstX, dstY);
	}

	if (Y - 1 >= 0 && path[Y-1][X] == 1)
	{
		++currentLength;
		findLongestPath(path, X, Y - 1, level + 1, currentLength, dstX, dstY);
	}

	if (Y + 1 < Y_MAX  && path[Y+1][X] == 1)
	{
		++currentLength;
		findLongestPath(path, X, Y + 1, level + 1, currentLength, dstX, dstY);
	}

	path[Y][X] = 1;

	if(pathsFollowed.size())
		pathsFollowed.pop_back();

	if (currentLength)
		--currentLength;

	drawPath(path);
}


#endif /* LONGEST_PATH_HURDELS_H_ */
