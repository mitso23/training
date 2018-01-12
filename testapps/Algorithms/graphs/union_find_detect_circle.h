#include "graph.h"


int Find(int* group, int size, int element)
{
	if (element >= size)
	{
		printf("index out of bounds for element %d: \n", element);
		return -1;
	}

	if (group[element] == -1)
	{
		return element;
	}
	else
	{
		return Find(group, size, group[element]);
	}
}

void Union(int* group, int size, int x, int y)
{
	auto xParent = Find(group, size, x);
	auto yParent = Find(group, size, y);

	group[xParent] = yParent;
}


bool CheckIfLoopGraph(Graph* graph)
{
	int* group = new int[graph->m_connections.size()];
	for(int i= 0; i< graph->m_connections.size(); ++i)
		group[i] = -1;

	for(int i=0; i< graph->m_connections.size(); ++i)
	{
		auto iParent = Find(group, graph->m_connections.size(), i);

		std::cout << "i: " << i << " parent: " << iParent << std::endl;

		for(auto it = graph->m_connections[i].begin(); it != graph->m_connections[i].end(); ++it)
		{
			int j = it->first;

			auto jParent = Find(group, graph->m_connections.size(), j);

			std::cout << "j: " << j << " parent: " << jParent << std::endl;

			if (iParent == jParent)
			{
				return true;
			}
			else
			{
				Union(group, graph->m_connections.size(), iParent, jParent);
			}

		}
	}

}
