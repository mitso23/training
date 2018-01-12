#ifndef LONGEST_PATH_GRAPH_H_
#define LONGEST_PATH_GRAPH_H_

#define MAX_GRAPH_SIZE 10

int GraphPaths[MAX_GRAPH_SIZE][MAX_GRAPH_SIZE];
int GraphVisitedNodes[MAX_GRAPH_SIZE];
int MinDistancePath = 0xFFFF;

unsigned int fillGraph()
{
	memset(GraphPaths, 0, sizeof(GraphPaths));
	memset(GraphVisitedNodes, 0, sizeof(GraphVisitedNodes));

	GraphPaths[0][1]  = 1;
	GraphPaths[0][2]  = 5;
	GraphPaths[0][3]  = 2;

	GraphPaths[1][2]  = 3;

	GraphPaths[2][3]  = 1;
	GraphPaths[3][0]  = 5;

}

void FindShortestDestination(unsigned int currentNode, unsigned int destination, unsigned int size, unsigned currentDistance)
{
	if (currentNode >= size)
	{
		return;
	}

	if (currentNode == destination)
	{
		if (currentDistance < MinDistancePath)
		{
			MinDistancePath = currentDistance;
		}

		return;
	}

	GraphVisitedNodes[currentNode] = true;

	for(unsigned int j= 0; j< size; ++j)
	{
		if (GraphPaths[currentNode][j] != 0 && !GraphVisitedNodes[j])
		{
			currentDistance+= GraphPaths[currentNode][j];

			if (currentDistance < MinDistancePath)
				FindShortestDestination(j, destination, size, currentDistance);
		}
	}

	GraphVisitedNodes[currentNode] = false;
}

#endif /* LONGEST_PATH_GRAPH_H_ */
