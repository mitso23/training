#ifndef FIND_ARTICULATION_POINT_H_
#define FIND_ARTICULATION_POINT_H_

#include <vector>
#include <list>

class MyTreeNode
{
public:
	MyTreeNode(int edge) : m_edge(edge)
	{

	}

public:
	int m_edge;
	std::vector<MyTreeNode*> m_children;
};

class MyTree
{
public:
	MyTree() : m_parent(nullptr)
	{

	}

	void AddNode(MyTreeNode* node)
	{
		if (m_parent == nullptr)
		{
			m_parent = node;
		}
		else
		{
			m_parent->m_children.push_back(node);
		}
	}

	MyTreeNode* m_parent;
};

class ListNode
{
public:
	ListNode(int _node) : node(_node)
	{

	}

public:
	int node = -1;
	ListNode* next = nullptr;
};

class MyList
{

public:
	void push_back(int data)
	{
		if (!m_root)
		{
			m_root = new ListNode(data);
		}
		else
		{
			ListNode* current = m_root;
			while(current && current->next)
			{
				current = current->next;
			}

			current->next = new ListNode(data);
		}
	}

public:
	ListNode* m_root = nullptr;
};


class MyGraph2
{

public:
	struct NodeInfo
	{
		NodeInfo(int _node = -1) :
			node(_node)
		{

		}

		int node = -1;
		int visitedTime = -1;
		int lowTime = -1;
	};

	void AddEdge(int edge, int adj)
	{
		m_adj[edge].push_back(adj);
	}

	void Dfs(int node)
	{
		std::cout << "visited node: " << node << std::endl;

		static int visitedTime = 0;
		int childCount = 0;
		m_visited[node] = true;
		m_graphInfo[node].visitedTime = ++visitedTime;
		m_graphInfo[node].lowTime = m_graphInfo[node].visitedTime;

		ListNode* adjList = m_adj[node].m_root;

		while(adjList)
		{
			int adjNode = adjList->node;
			//std::cout << "next node: " << adjNode << std::endl;

			if (!m_visited[adjNode])
			{
				++childCount;

				//std::cout << "setting " << node << " parent of " << adjNode << std::endl;

				m_parents[adjNode] = node;
				Dfs(adjNode);

				m_graphInfo[node].lowTime = std::min(m_graphInfo[node].lowTime, m_graphInfo[adjNode].lowTime);

				if (childCount >=2 && m_parents[node] == -1)
				{
					std::cout << "articulation point detected on root node: " << node << std::endl;
				}
				else if (m_graphInfo[node].visitedTime < m_graphInfo[adjNode].lowTime)
				{
					std::cout << "articulation point detected: " << node << std::endl;
				}

			}
			else if (m_parents[node] != adjNode)
			{
				std::cout << "back edge detected: " << adjNode << std::endl;
				m_graphInfo[node].lowTime = std::min(m_graphInfo[node].lowTime, m_graphInfo[adjNode].visitedTime);
			}
			else
			{
				//std::cout << "ignoring " << adjNode << " as parent: " << node << std::endl;
			}

			adjList = adjList->next;
		}
	}

private:
	MyList m_adj[10];
	NodeInfo m_graphInfo[10];
	int m_parents[10] = { -1 };
	bool m_visited[10] = { false };
	bool m_articulationPoint[10] = { false };
};

class MyGraph
{
public:
	struct NodeInfo
	{
		NodeInfo (int _node = -1) : node(_node)
		{

		}

		int node = -1;
		int visitedTime = -1;
		int lowTime = -1;
	};

	MyGraph(int numEdges)
	{
		m_graph.resize(numEdges);
		m_parents.resize(numEdges, -1);
		m_visited.resize(numEdges, false);
		m_articulationPoints.resize(numEdges, -1);
	}

	void AddEdge(int edge, int adj)
	{
		NodeInfo edgeInfo(edge);
		NodeInfo adjInfo(adj);

		m_graph[edge].first.node = edge;
		m_graph[edge].second.push_back(adjInfo);
	}

	int getMinLowTimeAdj(int node)
	{
		int min = std::numeric_limits<int>::max();

		for(auto it = m_graph[node].second.begin(); it != m_graph[node].second.end(); ++it)
		{
			auto& adjNodeInfo = m_graph[it->node].first;
			if (adjNodeInfo.lowTime != -1 && adjNodeInfo.lowTime < min)
			{
				min = adjNodeInfo.lowTime;
			}
		}

		return min;
	}

	void DfsUnDirectedGraph(int node)
	{
		if (m_visited[node])
		{
			std::cout << "node already visited: " << node << std::endl;
			return;
		}

		auto& currentNodeInfo = m_graph[node].first;
		currentNodeInfo.visitedTime = ++m_currentTime;
		currentNodeInfo.lowTime = m_currentTime;

		std::cout << "visiting: " << node << " visited time: " << m_graph[node].first.visitedTime << " low time: " << m_graph[node].first.lowTime << std::endl;

		m_visited[node] = true;

		for(auto it = m_graph[node].second.begin(); it != m_graph[node].second.end(); ++it)
		{
			auto& adjNodeInfo = m_graph[it->node].first;

			if (m_parents[node] == adjNodeInfo.node)
			{
				//std::cout << "ignoring parent of " << node << " : " << adjNodeInfo.node << std::endl;
				continue;
			}
			else if (m_visited[adjNodeInfo.node])
			{
				if (m_articulationPoints[node] == -1)
				{
					currentNodeInfo.lowTime = std::min(currentNodeInfo.lowTime, adjNodeInfo.visitedTime);
					std::cout << "back edge detected: " << adjNodeInfo.node<< " low time: " << currentNodeInfo.lowTime << std::endl;
				}
			}
			else
			{
				m_parents[adjNodeInfo.node] = node;
				if (m_parents[currentNodeInfo.node] == -1)
				{
					std::cout << "transitioning from root node, incrementing child count " << std::endl;
					++m_childCount;

					if (m_childCount >=2)
					{
						if (m_articulationPoints[node] == -1)
						{
							std::cout << "articulation point detected from root: " << node <<  std::endl;
							std::cout << "root node detected: " << std::endl;
							m_articulationPoints[node] = 1;
						}
					}
				}

				DfsUnDirectedGraph(adjNodeInfo.node);
			}

			if (m_parents[currentNodeInfo.node] != -1)
			{
				if (currentNodeInfo.visitedTime < m_graph[adjNodeInfo.node].first.lowTime)
				{
					std::cout << "articulation point detected: " << node <<  " visited time: " << currentNodeInfo.visitedTime << " low time: " << m_graph[adjNodeInfo.node].first.lowTime << " of: " << adjNodeInfo.node << std::endl;
					m_articulationPoints[node] = 1;
				}
				else
				{
					currentNodeInfo.lowTime = std::min(currentNodeInfo.lowTime, adjNodeInfo.lowTime);
					std::cout << "updating low time of " << currentNodeInfo.node << " to: " << currentNodeInfo.lowTime << " of node: " << adjNodeInfo.node << std::endl;
				}
			}
			else
			{
				std::cout << "returning root node: " << node << std::endl;
			}
		}
	}

	std::vector<std::pair<NodeInfo, std::list<NodeInfo>>> m_graph;
	std::vector<int> m_parents;
	std::vector<bool> m_visited;
	std::vector<int> m_articulationPoints;
	int m_currentTime = 0;
	int m_childCount = 0;
};

#endif /* FIND_ARTICULATION_POINT_H_ */
