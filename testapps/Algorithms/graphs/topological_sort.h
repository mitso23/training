/*
 * topological_sort.h
 *
 *  Created on: 11 Nov 2017
 *      Author: mitso23
 */

#ifndef TOPOLOGICAL_SORT_H_
#define TOPOLOGICAL_SORT_H_

/*
 * Topological sorting for Directed Acyclic Graph (DAG) is a linear ordering of vertices such that for every directed edge uv,
 * vertex u comes before v in the ordering. Topological Sorting for a graph is not possible if the graph is not a DAG.
 *
 */

#include <stack>

void topological_sort_rec(int currentNode, Graph* graph, std::stack<int>& stack)
{
	//std::cout << "current node: " << currentNode << std::endl;

	if(graph->m_visited[currentNode])
	{
		return;
	}

	graph->m_visited[currentNode] = true;

	for(auto it = graph->m_connections[currentNode].begin(); it != graph->m_connections[currentNode].end(); ++it)
	{
		topological_sort_rec(it->first, graph, stack);
	}

	//std::cout << "pushing node: " << currentNode << std::endl;
	stack.push(currentNode);
}

void topological_sort(Graph* graph, int start)
{
	std::stack<int> stack;

	for(unsigned int i=0; i< graph->m_connections.size(); ++i)
	{
		topological_sort_rec(i, graph, stack);
	}

	while(!stack.empty())
	{
		const auto& node = stack.top();
		std::cout << "node: " << node << std::endl;
		stack.pop();
	}
}


#endif /* TOPOLOGICAL_SORT_H_ */
