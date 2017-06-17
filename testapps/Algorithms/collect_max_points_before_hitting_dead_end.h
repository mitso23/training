#include<bits/stdc++.h>
using namespace std;

char arr[5][5] = { { 'E', 'C', 'C', 'C', 'C' },
				   { 'C', '#', 'C', '#', 'E' },
				   { '#', 'C', 'C', '#', '#' },
				   { 'C', 'E', 'C', '#', 'E' },
				   { 'C', 'E', '#', 'C', 'E' }
};


char visitedArrRight[100][100] = { 0 };
char visitedArrLeft[100][100] = { 0 };
unsigned MaxCount = 0;
int Xmax = 5;
int Ymax = 5;


void move(int Y, int X, bool directionRight, int count)
{
	std::cout << "Going to: " << arr[Y][X] << " count: " << count << " Y: " << Y << " X: " << X << " direction: " << directionRight << std::endl;

	if (count > MaxCount)
	{
		MaxCount = count;
		//std::cout << "maxCount" << MaxCount << std::endl;
	}

	if (directionRight)
	{
		if ((X+1 < Xmax) && (arr[Y][X+1] != '#'))
		{
			if (arr[Y][X+1] == 'C')
			{
				++count;
			}

			move(Y, X+1, true, count);

			if (count > 0)
			{
				--count;
			}
		}

		if ((Y+1 < Ymax) && (arr[Y+1][X] != '#'))
		{
			if (arr[Y+1][X] == 'C')
			{
				++count;
			}

			move(Y+1, X, false, count);

			if (count > 0)
			{
				--count;
			}
		}
	}
	else
	{
		if ((X - 1 >=0) && (arr[Y][X - 1] != '#'))
		{
			if (arr[Y][X-1] == 'C')
			{
				++count;
			}

			move(Y, X - 1, false, count);

			if (count > 0)
			{
				--count;
			}
		}

		if ((Y + 1 < Ymax) && (arr[Y + 1][X] != '#'))
		{
			if (arr[Y+1][X] == 'C')
			{
				++count;
			}

			move(Y + 1, X, true, count);

			if (count > 0)
			{
				--count;
			}
		}
	}

	std::cout << "Returning from Y: " << Y << " X: " << X << std::endl;

}

#define R 5
#define C 5

// to check whether current cell is out of the grid or not
bool isValid(int i, int j)
{
    return (i >=0 && i < R && j >=0 && j < C);
}

// dir = 0 for left, dir = 1 for facing right.  This function returns
// number of maximum coins that can be collected starting from (i, j).
int maxCoinsRec(char arr[R][C],  int i, int j, int dir)
{
    // If this is a invalid cell or if cell is a blocking cell
    if (isValid(i,j) == false || arr[i][j] == '#')
        return 0;

    // Check if this cell contains the coin 'C' or if its empty 'E'.
    int result = (arr[i][j] == 'C')? 1: 0;

    // Get the maximum of two cases when you are facing right in this cell
    if (dir == 1) // Direction is right
       return result + max(maxCoinsRec(arr, i+1, j, 0),     // Down
                             maxCoinsRec(arr, i, j+1, 1));  // Ahead in right

    // Direction is left
    // Get the maximum of two cases when you are facing left in this cell
     return  result + max(maxCoinsRec(arr, i+1, j, 1),    // Down
                           maxCoinsRec(arr, i, j-1, 0));  // Ahead in left
}

