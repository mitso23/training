#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <list>
#include <set>

class Graph
{
public:
	Graph(int numberVertices) : m_numberVertices(numberVertices)
	{
		m_connections.resize(m_numberVertices);
		m_visited.resize(m_numberVertices);

		for(unsigned int i=1; i< m_numberVertices; ++i)
		{
			m_distances.insert(std::make_pair(std::numeric_limits<int>::max(), i));
			m_distances_reverse.insert(std::make_pair(i, std::numeric_limits<int>::max()));
		}

		m_distances.insert(std::make_pair(0, 0));
		m_distances_reverse.insert(std::make_pair(0, 0));

	}

	Graph(int* arr, int numCols, int numRows) : m_numberVertices(numCols)
	{
		m_connections.resize(m_numberVertices);
		m_visited.resize(m_numberVertices);

		for (unsigned int i = 1; i < m_numberVertices; ++i)
		{
			m_distances.insert(
					std::make_pair(std::numeric_limits<int>::max(), i));

			m_distances_reverse.insert(
					std::make_pair(i, std::numeric_limits<int>::max()));
		}

		m_distances.insert(std::make_pair(0, 0));
		m_distances_reverse.insert(std::make_pair(0, 0));

		for(unsigned int j=0; j< numCols; ++j)
		{
			for(unsigned int i=0; i< numRows; ++i)
			{
				int distance = arr[j*numCols + i];
				if (distance != 0)
					m_connections[j].push_back(std::make_pair(i, distance));
			}
		}
	}

	void AddEdge(int v, std::pair<int, int> p)
	{
		m_connections[v].push_back(p);
	}

	void traverseGraphDfs(int currentNode)
	{
		if (m_visited[currentNode]) { return; };

		std::cout << "visiting node: " << currentNode << std::endl;
		m_visited[currentNode] = true;

		auto edges = m_connections[currentNode];

		for(auto it= edges.begin(); it != edges.end(); ++it)
		{
			if (!m_visited[it->first])
			{
				traverseGraphDfs(it->first);
			}
		}
	}

	void calculateMinDistanceDijkta()
	{
		while(m_minDistances.size() != m_numberVertices)
		{
			auto it = m_distances.begin();

			auto currentNode = -1;
			auto currentDistance = -1;

			while(it != m_distances.end())
			{
				if (m_minDistances.find(it->second) == std::end(m_minDistances))
				{
					std::cout << "min distance: " << it->first << std::endl;

					// get the next smallest distance
					currentNode = it->second;
					currentDistance = it->first;
					break;
				}

				++it;
			}

			if (currentNode == -1)
			{
				std::cerr << "Couldn't find any nodes" << std::endl;
				return;
			}

			//update the set as this is the minimum distance so far
			m_minDistances.insert(currentNode);

			for(auto it = m_connections[currentNode].begin(); it != m_connections[currentNode].end(); ++it)
			{
				auto dstNode = it->first;
				auto dstDistance = it->second;

				if (dstDistance + currentDistance < m_distances_reverse[dstNode])
				{
					auto totalDistance = dstDistance + currentDistance;
					auto distance = m_distances_reverse[dstNode];
					auto range = m_distances.equal_range(distance);

					bool found = false;
					for(auto it2 = range.first; it2 != range.second; ++it2)
					{
						if (it2->second == dstNode)
						{
							found = true;
							m_distances.erase(it2);
							m_distances.insert(std::make_pair(totalDistance, dstNode));
							break;
						}
					}

					if (!found)
					{
						std::cerr << "Couldn't update m_distances for node: " << dstNode << std::endl;
						return;
					}

					m_distances_reverse[dstNode] = totalDistance;

				}
			}
		}

		for(auto item : m_distances)
		{
			std::cout << "distance: " << item.first << " node: " << item.second << std::endl;
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

#if 0
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
#endif

public:
	std::vector<std::list<std::pair<int, int>>> m_connections; ///< The connection between the nodes
	int m_numberVertices;						///< how many nodes we have
	std::vector<bool> m_visited;			///< Nodes that we have already visited
	std::set<int> m_minDistances;			///< a set of minimum distances
	std::multimap<int, int> m_distances;	///< required for djikita algorithm, maintains the distance of the visited nodes so far
	std::map<int, int> m_distances_reverse;	///< required for djikita algorithm, maintains the distance of the visited nodes so far
};

#endif /* GRAPH_H_ */
