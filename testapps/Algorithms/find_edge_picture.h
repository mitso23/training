#ifndef FIND_EDGE_PICTURE_H_
#define FIND_EDGE_PICTURE_H_

#define MAX_PICTURE_SIZE 10

int Picture[MAX_PICTURE_SIZE][MAX_PICTURE_SIZE] = {
													{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
													{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
													{ 0, 1, 1, 1, 1, 1, 0, 0, 1, 0},
													{ 0, 1, 0, 0, 0, 1, 0, 0, 1, 0},
													{ 0, 1, 1, 1, 0, 0, 0, 0, 1, 0},
													{ 0, 1, 0, 0, 1, 1, 0, 0, 1, 0},
													{ 0, 1, 0, 0, 1, 1, 0, 0, 1, 0},
													{ 0, 1, 0, 0, 1, 1, 0, 0, 1, 0},
													{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
													{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

												  };
int maxCounter = 0;

void findFirstEdge(int&y, int&x, int size)
{
	for (unsigned int j = 0; j < size; ++j)
	{
		for (unsigned int i = 0; i < size; ++i)
		{
			if (Picture[j][i] == 1)
			{
				y = j;
				x = i;
				return;
			}
		}
	}

	y=-1;
	x=-1;
}

void printPicture(int size)
{
	for ( int j = 0; j < size; ++j)
	{
		for (int i = 0; i < size; ++i)
		{
			std::cout << Picture[j][i] << " ";
		}

		std::cout << std::endl;
	}

	std::cout << std::endl;

	sleep(1);
}

std::deque<std::pair<int, int>> data;

void printEdgePath(int size)
{
	int Picture2[MAX_PICTURE_SIZE][MAX_PICTURE_SIZE];
	memset(Picture2, 0, sizeof(Picture2));

	for(auto item: data)
	{
		Picture2[item.first][item.second] = 2;

		for ( int j = 0; j < size; ++j)
		{
			for (int i = 0; i < size; ++i)
			{
				std::cout << Picture2[j][i] << " ";
			}

			std::cout << std::endl;
		}

		std::cout << std::endl;
		sleep(1);
	}
}

void findEdge(int y, int x, int size, int& count, int dstY, int dstX)
{
	//std::cout << "y: " << y << " x: " << x << std::endl;

	if (Picture[y][x] == 2 && x == dstX && y == dstY)
	{
		if (count > maxCounter)
		{
			//printPicture(size);
			printEdgePath(size);
			maxCounter = count;
		}

		return;
	}

	Picture[y][x] = 2;
	++count;
	data.push_back(std::make_pair(y, x));
	//printPicture(size);

	if (x+1 < size && ((Picture[y][x+1] == 1) || (y == dstY && x+1 == dstX)))
	{
		findEdge(y, x+1, size, count, dstY, dstX);
	}

	if (x-1 >= 0 && ((Picture[y][x-1] == 1) || (y == dstY && x-1 == dstX)))
	{
		findEdge(y, x-1, size, count, dstY, dstX);
	}

	if (y+1 < size && ((Picture[y+1][x] == 1) || (y + 1 == dstY && x == dstX)))
	{
		findEdge(y+1, x, size, count, dstY, dstX);
	}

	if (y-1 >= 0 && ((Picture[y-1][x] == 1) || (y - 1 == dstY && x == dstX)))
	{
		findEdge(y-1, x, size, count, dstY, dstX);
	}


	Picture[y][x] = 1;
	--count;
	if (!data.empty())
		data.pop_back();

	//printPicture(size);
	//std::cout << "back y: " << y << " x: " << x << std::endl;

}

#endif /* FIND_EDGE_PICTURE_H_ */
