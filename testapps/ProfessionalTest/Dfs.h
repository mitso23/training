/*
 * dfs.h
 *
 *  Created on: Aug 8, 2019
 *      Author: mitso23
 */

#ifndef TESTAPPS_PROFESSIONALTEST_DFS_H_
#define TESTAPPS_PROFESSIONALTEST_DFS_H_

const int g_maxN = 100;

struct FamilyTree
{
	int parent = -1;
	int children[g_maxN];
	int numChilder = 0;
};

FamilyTree gFamilyTree[g_maxN];
int gN = 0;

struct Coordinates
{
	int y = -1;
	int x = -1;
	int count = 0;
};


class Queue
{

public:
	void Add(Coordinates& c)
	{
		if ((m_writePos + 1) % MAX_QUEUE_SIZE == m_readPos)
		{
			std::cerr << "queue is full" << std::endl;
			return;
		}
		q[m_writePos] = c;
		m_writePos = (m_writePos + 1) % MAX_QUEUE_SIZE;
	}

	Coordinates Pop()
	{
		if (m_readPos == m_writePos)
		{
			std::cerr << "queue is empty" << std::endl;
			return Coordinates();
		}

		auto readPos = m_readPos;
		m_readPos = (m_readPos + 1) % MAX_QUEUE_SIZE;

		return q[readPos];
	}

	int Size() const
	{
		if (m_writePos > m_readPos)
		{
			return m_writePos - m_readPos - 1;
		}
		else
		{
			return m_readPos - m_writePos - 1;
		}
	}

private:
	int m_writePos = 0;	///< The next position to be written
	int m_readPos = 0;	///< The next position to be read
	static constexpr unsigned MAX_QUEUE_SIZE = 100;
	Coordinates q[MAX_QUEUE_SIZE];
};

class Queue2
{

public:
	void Add(Coordinates& c)
	{
		if (m_size == MAX_QUEUE_SIZE)
		{
			std::cerr << "queue is full" << std::endl;
			return;
		}

		q[m_writePos] = c;
		m_writePos = (m_writePos + 1) % MAX_QUEUE_SIZE;
		++m_size;
	}

	Coordinates Pop()
	{
		if (m_size == 0)
		{
			std::cerr << "queue is empty" << std::endl;
			return Coordinates();
		}

		auto readPos = m_readPos;
		m_readPos = (m_readPos + 1) % MAX_QUEUE_SIZE;
		--m_size;

		return q[readPos];
	}

	int Size() const
	{
		return m_size;
	}

private:
	int m_writePos = 0;	///< The next position to be written
	int m_readPos = 0;	///< The next position to be read
	unsigned int m_size = 0;
	static constexpr unsigned MAX_QUEUE_SIZE = 10;
	Coordinates q[MAX_QUEUE_SIZE];
};

int minPathSize = 100;
#define MAP_SIZE 4

int Map[MAP_SIZE][MAP_SIZE] = { { 0, 0, 0, 0  },
				  				{ 0, 0, 0, 0, },
								{ 0, 0, 0, 0, },
								{ 0, 0, 0, 0, },
				  	  	  	  };

void PrintMap()
{
	for(unsigned int i=0; i< MAP_SIZE; ++i)
	{
		for(unsigned int j=0; j< MAP_SIZE; ++j)
		{
			std::cout << Map[i][j] << " ";
		}

		std::cout << std::endl;
	}
}

bool find_shortest_path(Coordinates src, Coordinates dst, Queue& q)
{
	std::cout << "y1: " << src.y << " x1: " << src.x << " count: " << src.count << " q size: " << q.Size() << std::endl;
	static int counter = 1;
	Map[src.y][src.x] = counter++;

	PrintMap();

	//Check if you can go right
	if (src.x + 1 < MAP_SIZE && Map[src.y][src.x+1] == 0)
	{
		Coordinates c;
		c.y = src.y;
		c.x = src.x + 1;
		c.count = src.count + 1;
		q.Add(c);
		std::cout << " can go right" << std::endl;
	}

	//Check if you can go left
	if (src.x - 1 >= 0 && Map[src.y][src.x-1] == 0)
	{
		Coordinates c;
		c.y = src.y;
		c.x = src.x - 1;
		c.count = src.count + 1;
		q.Add(c);

		std::cout << " can go left" << std::endl;
	}

	//Check if we can go down
	if (src.y + 1 < MAP_SIZE && Map[src.y + 1][src.x] == 0)
	{
		Coordinates c;
		c.y = src.y + 1;
		c.x = src.x;
		c.count = src.count + 1;
		q.Add(c);

		std::cout << " can go down" << std::endl;
	}

	//Check if we can go up
	if (src.y - 1 >=0 && Map[src.y - 1][src.x] == 0)
	{
		Coordinates c;
		c.y = src.y - 1;
		c.x = src.x;
		c.count = src.count + 1;
		q.Add(c);

		std::cout << " can go up" << std::endl;
	}

	if (src.y == dst.y && src.x == dst.x)
	{
		std::cout << "found path: " << src.count << " max: " << minPathSize << std::endl;

		if (src.count < minPathSize)
		{
			minPathSize = src.count;
		}
	}

	Coordinates next = q.Pop();
	while (next.x != -1 && next.y != -1 && Map[next.y][next.x] == 0)
	{
		find_shortest_path(next, dst, q);
		next = q.Pop();
		std::cout << "going back to y: " << next.y << " x: " << next.x << std::endl;
	}
}

void dfs_init(int N, int path[100][2])
{
	gN = N;

	for(int i=0; i< N; ++i)
	{
		int parent = path[i][0];
		int child = path[i][1];

		std::cout << "Adding child: " << child << " to parent: " << parent << std::endl;

		gFamilyTree[parent].parent = parent;
		gFamilyTree[parent].children[gFamilyTree[parent].numChilder++] = child;
	}
}

int dfs_rec(int current, int max)
{
	auto parent = gFamilyTree[current].parent;
	auto numChilder = gFamilyTree[current].numChilder;

	for(int i = 0; i < numChilder; ++i)
	{
		auto child = gFamilyTree[current].children[i];
		if (child >= max)
		{
			std::cout << "found child " << child << " larger than: " << max << std::endl;
			return 1;
		}
		else
		{
			if (dfs_rec(child, max) == 1)
			{
				return 1;
			}
		}
	}

	return -1;
}

int dfs(int n)
{
	auto parent = gFamilyTree[n].parent;
	if (parent == -1)
	{
		std::cerr << "no such parent exist: " << n << std::endl;
		return -1;
	}

	return dfs_rec(n, n);
}



#endif /* TESTAPPS_PROFESSIONALTEST_DFS_H_ */
