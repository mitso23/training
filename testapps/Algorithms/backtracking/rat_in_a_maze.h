#ifndef RAT_IN_A_MAZE_H_
#define RAT_IN_A_MAZE_H_

/*The function returns a sorted array of strings which represents
the directions mouse will take to reach the destination.
You are required to complete the below method. */

#include <algorithm>
#include <stack>
#include <string>

#define MAX 6

std::vector<std::string> paths;
std::stack<char> currentPath;

int visitedCell[MAX][MAX];

void getPath(int m[MAX][MAX], int n, int x, int y)
{
	visitedCell[y][x] = 1;

    //std::cout << "going x: " << x << " y: " << y << std::endl;

    if (x == n - 1 && y == n - 1)
    {
        std::string path;
        std::stack<char> tempPath = currentPath;

        while(!tempPath.empty())
        {
            path.insert(0, 1, tempPath.top());
            tempPath.pop();
        }

        paths.push_back(path);
    }

    if (!visitedCell[y][x+1] && x + 1 < n && m[y][x+1] == 1)
    {
        currentPath.push('R');
        getPath(m, n, x+1, y);
    }

    if (!visitedCell[y][x-1] && x - 1 >= 0 && m[y][x-1] == 1)
    {
        currentPath.push('L');
        getPath(m, n, x-1, y);
    }

    if (!visitedCell[y+1][x] && y + 1 < n && m[y+1][x] == 1)
    {
        currentPath.push('D');
        getPath(m, n, x, y+1);
    }

    if (!visitedCell[y-1][x] && y - 1 >= 0 && m[y-1][x] == 1)
    {
        currentPath.push('U');
        getPath(m, n, x, y-1);
    }

    visitedCell[y][x] = 0;
    currentPath.pop();
}


vector<string> printPath(int m[MAX][MAX], int n)
{
    memset(visitedCell, 0, sizeof(visitedCell));
    paths.clear();
    currentPath = std::stack<char>();
    getPath(m, n, 0, 0);
    std::sort(paths.begin(), paths.end());
    paths.erase( unique( paths.begin(), paths.end() ), paths.end() );

    return paths;
}

#endif /* RAT_IN_A_MAZE_H_ */
