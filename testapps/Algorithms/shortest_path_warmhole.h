#ifndef SHORTEST_PATH_WARMHOLE_H_
#define SHORTEST_PATH_WARMHOLE_H_

int wormHoldeMap[4][4];
bool wormHoleVisited[4];

struct Coordinate
{
	int x;
	int y;
};

Coordinate Coordinates[4];
int minPathDistance = 0xFFFFFFFF;

int calculateDistance(Coordinate a, Coordinate b)
{
	return (b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y);
}

int getNodeFromCoordinate(Coordinate coordinate)
{
	for(unsigned int i=0; i< 4; ++i)
	{
		if (Coordinates[i].x == coordinate.x && Coordinates[i].y == coordinate.y)
		{
			return i;
		}
	}

	return -1;
}

Coordinate getCoordinateFromNode(int i)
{
	return Coordinates[i];
}

void findMinDistance(int current, int dst, unsigned int count)
{
	if (current == dst)
	{
		if (count < minPathDistance)
		{
			minPathDistance = count;
		}

		return;
	}

	wormHoleVisited[current] = true;
	for(unsigned int i=0; i< 4; ++i)
	{
		if (wormHoldeMap[current][i] != 0 && !wormHoleVisited[i])
		{
			auto a = getCoordinateFromNode(current);
			auto b = getCoordinateFromNode(dst);

			auto distance = calculateDistance(a,b);

			if (count < minPathDistance)
				findMinDistance(i, dst, count + distance);
		}
	}

	wormHoleVisited[current] = false;
}

#endif /* SHORTEST_PATH_WARMHOLE_H_ */
