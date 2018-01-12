#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <list>

class Graph
{
public:
	Graph(int numberVertices) : m_numberVertices(numberVertices)
	{
		m_connections.resize(m_numberVertices);
		m_visited.resize(m_numberVertices);
	}

	void AddEdge(int v, int m)
	{
		m_connections[v].push_back(m);
	}

	void traverseGraphDfs(int currentNode)
	{
		if (m_visited[currentNode]) { return; };

		std::cout << "visiting node: " << currentNode << std::endl;
		m_visited[currentNode] = true;

		auto edges = m_connections[currentNode];

		for(auto it= edges.begin(); it != edges.end(); ++it)
		{
			if (!m_visited[*it])
			{
				traverseGraphDfs(*it);
			}
		}
	}

	void traverseGraphEdgedNotConnected()
	{
		for(unsigned int i=0; i< m_connections.size(); ++i)
		{
			std::cout << "starting traverse from: " << i << std::endl;
			traverseGraphDfs(i);
		}
	}

	void traverseGraph2(int currentNode)
	{
		if (!m_visited[currentNode])
		{
			std::cout << "visiting node: " << currentNode << std::endl;
			m_visited[currentNode] = true;
		}
		std::queue<int> toBeVisited;

		for (auto it= m_connections[currentNode].begin(); it != m_connections[currentNode].end(); ++it)
		{
			if (!m_visited[*it])
			{
				std::cout << "visiting node: " << *it << std::endl;
				toBeVisited.push(*it);
				m_visited[*it] = true;
			}
		}

		while(!toBeVisited.empty())
		{
			auto item = toBeVisited.front();
			traverseGraph2(item);
			toBeVisited.pop();
		}
	}

	void traverseGraphBfs(int currentNode, std::queue<int> toBeVisited)
	{
		if (!m_visited[currentNode])
		{
			std::cout << currentNode << std::endl;
			m_visited[currentNode] = true;
		}

		for (auto it= m_connections[currentNode].begin(); it != m_connections[currentNode].end(); ++it)
		{
			if (!m_visited[*it])
			{
				std::cout << *it << std::endl;
				m_visited[*it] = true;
				toBeVisited.push(*it);
			}
		}

		if (!toBeVisited.empty())
		{
			auto nextNode = toBeVisited.front();
			toBeVisited.pop();
			traverseGraphBfs(nextNode, toBeVisited);
		}
	}

private:
	int m_numberVertices;
	std::vector<std::list<int>> m_connections;
	std::vector<bool> m_visited;
};

#endif /* GRAPH_H_ */
