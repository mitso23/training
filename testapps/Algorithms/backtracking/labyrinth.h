#ifndef LABYRINTH_H_
#define LABYRINTH_H_

#include <unistd.h>

typedef struct
{
	int y;
	int x;
}Pos;

#define ROW_SIZE 10

static int visited[100][100] = { 0 };

void drawMap(const unsigned (*arr)[ROW_SIZE], unsigned size, Pos next)
{
	unsigned int* arrCopy[ROW_SIZE];

	for (unsigned int i=0; i< size; ++i)
	{
		arrCopy[i] = (unsigned*)malloc(sizeof(unsigned) * ROW_SIZE);
		memcpy(arrCopy[i], arr[i], ROW_SIZE*sizeof(unsigned));
	}

	arrCopy[next.y][next.x] = '*';

	for(unsigned int j=0; j< size; ++j)
	{
		for(unsigned int i=0; i< ROW_SIZE; ++i)
		{
			printf("%c ", arrCopy[j][i]);
		}

		printf("\n");
	}

	usleep(1000*200);
}

bool findExit(const unsigned (*arr)[ROW_SIZE], unsigned size, Pos current, Pos _exit)
{
	std::cout << "current x: " << current.x << " y: " << current.y << std::endl;

	Pos nextPos;
	visited[current.y][current.x] = 1;

	if (current.x == _exit.x && current.y == _exit.y)
	{
		std::cout << "FOUND" << std::endl;
		return true;
	}

	if(current.x - 1 >= 0 && !visited[current.y][current.x - 1] && arr[current.y][current.x - 1] == ' ')
	{
		nextPos.x = current.x - 1;
		nextPos.y = current.y;

		//std::cout << " going left: " << std::endl;
		drawMap(arr, size, nextPos);

		bool result = findExit(arr, size, nextPos, _exit);
		if (result)
		{
			return true;
		}
	}

	if (current.x + 1 < ROW_SIZE && !visited[current.y][current.x + 1] && arr[current.y][current.x + 1] == ' ')
	{
		nextPos.x = current.x + 1;
		nextPos.y = current.y;

		//std::cout << " going right: " << std::endl;
		drawMap(arr, size, nextPos);

		bool result = findExit(arr, size, nextPos, _exit);
		if (result)
		{
			return true;
		}
	}

	if (current.y - 1 >= 0 && !visited[current.y - 1][current.x] && arr[current.y-1][current.x] == ' ')
	{
		nextPos.x = current.x;
		nextPos.y = current.y - 1;

		//std::cout << " going down: " << std::endl;
		drawMap(arr, size, nextPos);

		bool result = findExit(arr, size, nextPos, _exit);
		if (result)
		{
			return true;
		}
	}

	if (current.y + 1 < ROW_SIZE && !visited[current.y + 1][current.x] && arr[current.y+1][current.x] == ' ')
	{
		nextPos.x = current.x;
		nextPos.y = current.y + 1;

		//std::cout << " going up: " << std::endl;
		drawMap(arr, size, nextPos);

		bool result = findExit(arr, size, nextPos, _exit);
		if (result)
		{
			return true;
		}
	}

	//std::cout << " returning: " << std::endl;
	return false;
}


const int MazeHeight = 9;
const int MazeWidth = 9;

char Maze[MazeHeight][MazeWidth + 1] =
{
    "# #######",
    "#   #   #",
    "# ### # #",
    "# #   # #",
    "# # # ###",
    "#   # # #",
    "# ### # #",
    "#   #   #",
    "####### #",
};

const char Wall = '#';
const char Free = ' ';
const char SomeDude = '*';

class COORD
{
public:
    int X;
    int Y;
    COORD(int x = 0, int y = 0) { X = x, Y = y; }
    COORD(const COORD &coord) { X = coord.X; Y = coord.Y; }
};

COORD StartingPoint(1, 0);
COORD EndingPoint(7, 8);

void PrintDaMaze()
{
    for (int Y = 0; Y < MazeHeight; Y++)
    {
        printf("%s\n", Maze[Y]);
    }
    printf("\n");
}

bool Solve(int X, int Y)
{
    // Make the move (if it's wrong, we will backtrack later.
    Maze[Y][X] = SomeDude;

    // If you want progressive update, uncomment these lines...
    PrintDaMaze();
    sleep(1);

    // Check if we have reached our goal.
    if (X == EndingPoint.X && Y == EndingPoint.Y)
    {
        return true;
    }

    // Recursively search for our goal.
    if (X > 0 && Maze[Y][X - 1] == Free && Solve(X - 1, Y))
    {
        return true;
    }
    if (X < MazeWidth && Maze[Y][X + 1] == Free && Solve(X + 1, Y))
    {
        return true;
    }
    if (Y > 0 && Maze[Y - 1][X] == Free && Solve(X, Y - 1))
    {
        return true;
    }
    if (Y < MazeHeight && Maze[Y + 1][X] == Free && Solve(X, Y + 1))
    {
        return true;
    }

    // Otherwise we need to backtrack and find another solution.
    //Maze[Y][X] = Free;

    // If you want progressive update, uncomment these lines...
    PrintDaMaze();
    sleep(1);
    return false;
}



#endif /* LABYRINTH_H_ */
