/*
 * labyrinth_wall.h
 *
 *  Created on: 14 Jun 2017
 *      Author: mitso23
 */

#ifndef LABYRINTH_WALL_H_
#define LABYRINTH_WALL_H_

#include <unistd.h>

const int MazeHeight = 3;
const int MazeWidth = 3;

#if 0
char Maze[MazeHeight][MazeWidth + 1] =
{
//   012345678
    "# #######", //0
    "#x #   # ", //1
    "# ###x# #", //2
    "# #   # #", //3
    "# # #x###", //4
    "#x  # #  ", //5
    "#x ##x x#", //6
    "#    x  #", //7
    "#########", //8
};
#endif

char Maze[MazeHeight][MazeWidth + 1] =
{
//   012
    "   ", //0
    " xx", //1
    "# #", //2
};

const char Wall = '#';
const char Free = ' ';
const char SomeDude = '*';
const char MoveWall = 'x';

class COORD
{
public:
    int X;
    int Y;
    COORD(int x = 0, int y = 0) { X = x, Y = y; }
    COORD(const COORD &coord) { X = coord.X; Y = coord.Y; }
};

COORD StartingPoint(1, 0);
COORD EndingPoint(2, 1);

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
	//std::cout << "Y: " << Y << " X: " << X << std::endl;

    // Make the move (if it's wrong, we will backtrack later.
    Maze[Y][X] = SomeDude;

    // If you want progressive update, uncomment these lines...
    PrintDaMaze();
    usleep(1000 * 1000);

    // Check if we have reached our goal.
    if (X == EndingPoint.X && Y == EndingPoint.Y)
    {
    	std::cout << "SUCCESS" << std::endl;
        return true;
    }

    // Recursively search for our goal.
    if (Y < MazeHeight && Maze[Y + 1][X] == Free && Solve(X, Y + 1))
    {
	  return true;
    }
    if (X > 0 && Maze[Y][X - 1] == Free && Solve(X - 1, Y))
    {
	   return true;
    }
    if (Y > 0 && Maze[Y - 1][X] == Free && Solve(X, Y - 1))
    {
	   return true;
   	}


    if (X < MazeWidth && Maze[Y][X + 1] == Free && Solve(X + 1, Y))
    {
        return true;
    }


    if (X > 0 && Maze[Y][X - 1] == MoveWall)
    {
    	//std::cout << "Move wall at Y: " << Y << " X: " << X - 1 << std::endl;

		int MoveWallY = Y;
		int MoveWallX = X - 1;

		if (MoveWallX > 0 && Maze[MoveWallY][MoveWallX -1] == Free)
		{
			Maze[MoveWallY][MoveWallX -1] = MoveWall;
			Maze[MoveWallY][MoveWallX] = Free;

			if (Solve(X-1, Y))
			{
				return true;
			}

			Maze[MoveWallY][MoveWallX -1] = Free;
			Maze[MoveWallY][MoveWallX] = MoveWall;
		}

		if (MoveWallX < MazeHeight && Maze[MoveWallY][MoveWallX+1] == Free)
		{
			Maze[MoveWallY][MoveWallX+1] = MoveWall;
			Maze[MoveWallY][MoveWallX] = Free;


			if (Solve(X-1, Y))
			{
				return true;
			}

			Maze[MoveWallY][MoveWallX+1] = Free;
			Maze[MoveWallY][MoveWallX] = MoveWall;
		}

		if (MoveWallY > 0 && Maze[MoveWallY - 1][MoveWallX] == Free)
		{
			Maze[MoveWallY - 1][MoveWallX] = MoveWall;
			Maze[MoveWallY][MoveWallX] = Free;


			if (Solve(X-1, Y))
			{
				return true;
			}

			Maze[MoveWallY - 1][MoveWallX] = Free;
			Maze[MoveWallY][MoveWallX] = MoveWall;
		}

		if (MoveWallY < MazeHeight && Maze[MoveWallY + 1][MoveWallX] == Free)
		{
			Maze[MoveWallY + 1][MoveWallX] = MoveWall;
			Maze[MoveWallY][MoveWallX] = Free;

			if (Solve(X-1, Y))
			{
				return true;
			}

			Maze[MoveWallY + 1][MoveWallX] = Free;
			Maze[MoveWallY][MoveWallX] = MoveWall;
		}


	}

	if (X < MazeWidth && Maze[Y][X + 1] == MoveWall)
	{
		//std::cout << "Move wall at Y: " << Y << " X: " << X + 1 << std::endl;

		int MoveWallY = Y;
		int MoveWallX = X + 1;

		if (MoveWallX > 0 && Maze[MoveWallY][MoveWallX - 1] == Free)
		{
			Maze[MoveWallY][MoveWallX - 1] = MoveWall;
			Maze[MoveWallY][MoveWallX] = Free;

			if (Solve(X+1, Y))
			{
				return true;
			}

			Maze[MoveWallY][MoveWallX - 1 ] = Free;
			Maze[MoveWallY][MoveWallX] = MoveWall;
		}

		if (MoveWallX < MazeHeight && Maze[MoveWallY][MoveWallX+1] == Free)
		{
			Maze[MoveWallY][MoveWallX+1] = MoveWall;
			Maze[MoveWallY][MoveWallX] = Free;

			if (Solve(X+1, Y))
			{
				return true;
			}

			Maze[MoveWallY][MoveWallX+1] = Free;
			Maze[MoveWallY][MoveWallX] = MoveWall;
		}

		if (MoveWallY > 0 && Maze[MoveWallY - 1][MoveWallX] == Free)
		{
			Maze[MoveWallY - 1][MoveWallX] = MoveWall;
			Maze[MoveWallY][MoveWallX] = Free;

			if (Solve(X+1, Y))
			{
				return true;
			}

			Maze[MoveWallY - 1][MoveWallX] = Free;
			Maze[MoveWallY][MoveWallX] = MoveWall;
		}

		if (MoveWallY < MazeHeight && Maze[MoveWallY + 1][MoveWallX] == Free)
		{
			Maze[MoveWallY + 1][MoveWallX] = MoveWall;
			Maze[MoveWallY][MoveWallX] = Free;

			if (Solve(X+1, Y))
			{
				return true;
			}

			Maze[MoveWallY + 1][MoveWallX] = Free;
			Maze[MoveWallY][MoveWallX] = MoveWall;
		}

	}

	if (Y > 0 && Maze[Y - 1][X] == MoveWall)
	{
		int MoveWallY = Y - 1;
		int MoveWallX = X;

		if (MoveWallX > 0 && Maze[MoveWallY][MoveWallX -1] == Free)
		{
			Maze[MoveWallY][MoveWallX -1] = MoveWall;
			Maze[MoveWallY][MoveWallX] = Free;

			if (Solve(X, Y - 1))
			{
				return true;
			}

			Maze[MoveWallY][MoveWallX -1] = Free;
			Maze[MoveWallY][MoveWallX] = MoveWall;
		}

		if (MoveWallX < MazeHeight && Maze[MoveWallY][MoveWallX+1] == Free)
		{
			Maze[MoveWallY][MoveWallX+1] = MoveWall;
			Maze[MoveWallY][MoveWallX] = Free;

			if (Solve(X, Y - 1))
			{
				return true;
			}

			Maze[MoveWallY][MoveWallX+1] = Free;
			Maze[MoveWallY][MoveWallX] = MoveWall;
		}

		if (MoveWallY > 0 && Maze[MoveWallY - 1][MoveWallX] == Free)
		{
			Maze[MoveWallY - 1][MoveWallX] = MoveWall;
			Maze[MoveWallY][MoveWallX] = Free;

			if (Solve(X, Y - 1))
			{
				return true;
			}

			Maze[MoveWallY - 1][MoveWallX] = Free;
			Maze[MoveWallY][MoveWallX] = MoveWall;
		}

		if (MoveWallY < MazeHeight && Maze[MoveWallY + 1][MoveWallX] == Free)
		{
			Maze[MoveWallY + 1][MoveWallX] = MoveWall;
			Maze[MoveWallY][MoveWallX] = Free;

			if (Solve(X, Y - 1))
			{
				return true;
			}

			Maze[MoveWallY + 1][MoveWallX] = Free;
			Maze[MoveWallY][MoveWallX] = MoveWall;
		}
	}

	if (Y < MazeHeight && Maze[Y + 1][X] == MoveWall)
	{
		int MoveWallY = Y + 1;
		int MoveWallX = X;

		//std::cout << "Move wall at Y: " << Y + 1 << " X: " << X << std::endl;

		if (MoveWallX > 0 && Maze[MoveWallY][MoveWallX -1] == Free)
		{
			Maze[MoveWallY][MoveWallX -1] = MoveWall;
			Maze[MoveWallY][MoveWallX] = Free;

			if (Solve(X, Y + 1))
			{
				return true;
			}

			Maze[MoveWallY][MoveWallX -1] = Free;
			Maze[MoveWallY][MoveWallX] = MoveWall;
		}

		if (MoveWallX < MazeHeight && Maze[MoveWallY][MoveWallX+1] == Free)
		{
			Maze[MoveWallY][MoveWallX+1] = MoveWall;
			Maze[MoveWallY][MoveWallX] = Free;

			if (Solve(X, Y + 1))
			{
				return true;
			}

			Maze[MoveWallY][MoveWallX+1] = Free;
			Maze[MoveWallY][MoveWallX] = MoveWall;
		}

		if (MoveWallY > 0 && Maze[MoveWallY - 1][MoveWallX] == Free)
		{
			Maze[MoveWallY - 1][MoveWallX] = MoveWall;
			Maze[MoveWallY][MoveWallX] = Free;

			if (Solve(X, Y + 1))
			{
				return true;
			}

			Maze[MoveWallY - 1][MoveWallX] = Free;
			Maze[MoveWallY][MoveWallX] = MoveWall;
		}

		if (MoveWallY < MazeHeight && Maze[MoveWallY + 1][MoveWallX] == Free)
		{
			Maze[MoveWallY + 1][MoveWallX] = MoveWall;
			Maze[MoveWallY][MoveWallX] = Free;

			if (Solve(X, Y + 1))
			{
				return true;
			}

			Maze[MoveWallY + 1][MoveWallX] = Free;
			Maze[MoveWallY][MoveWallX] = MoveWall;
		}
	}


    // Otherwise we need to backtrack and find another solution.
    Maze[Y][X] = Free;

    // If you want progressive update, uncomment these lines...
    PrintDaMaze();
    usleep(1000*1000);
    return false;
}


#endif /* LABYRINTH_WALL_H_ */
