#pragma once
#include <queue>
#include <iostream>

template<unsigned size>
struct Graph
{
	Graph()
	{
		for(unsigned int i=0; i< size; ++i)
		{
			graph[i] = nullptr;
		}
	}

	struct Node
	{
		struct Edge
		{
			Edge(int _id) : id(_id)
			{

			}
			int id;
			Edge* next;
		};

		Node(int _id, int _data)
			: id(_id)
			, data(_data)
		{

		}

		void AddDestination(int dst)
		{
			if (!head)
			{
				head = new Edge(dst);
				head->next = nullptr;
			}
			else
			{
				Edge* e = new Edge(dst);
				e->next = head->next;
				head->next = e;
			}
		}

		Edge* head;
		int id;
		int data;
	};

	void Add(int src, int dst, int data)
	{
		if(graph[src] == nullptr)
		{
			graph[src] = new Node(src, data);
		}

		if (graph[dst] == nullptr)
		{
			graph[dst] = new Node(dst, data);
		}

		graph[src]->AddDestination(dst);
	}

	bool CheckPath(int src, int dst)
	{
		std::queue<int> q;
		return CheckRec(graph[src], q, dst);
	}

	bool CheckRec(Node* parent, std::queue<int> q, int dst)
	{
		std::cout << "parent: " << parent->id << std::endl;
		if (parent->id == dst)
		{
			return true;
		}

		auto* edge = parent->head;

		while(edge)
		{
			std::cout << "adding: " << edge->id << std::endl;
			q.push(edge->id);
			edge = edge->next;
		}

		if (q.empty())
		{
			return false;
		}

		Node* next = graph[q.front()];
		std::cout << "next: " << q.front() << std::endl;
		q.pop();
		return CheckRec(next, q, dst);
	}

	Node* graph[size];
};


template<unsigned size>
struct Graph2
{
	Graph2()
	{
		for(auto i=0U; i< size; ++i)
		{
			visited[i] = false;
		}
	}

	struct Node
	{
		char data;
		int edges[size];
		int numEdges = 0;

		void AddEdge(int edge)
		{
			edges[numEdges++] = edge;
		}
	};

	void AddNode(char data)
	{
		graph[numNodes++].data = data;
	}

	void AddEdge(int src, int dst)
	{
		graph[src].AddEdge(dst);
	}

	void TopologicalSort(int index)
	{
		if (visited[index])
		{
			return;
		}

		visited[index] = true;

		for(auto i=0; i< graph[index].numEdges; ++i)
		{
			auto nextVertex = graph[index].edges[i];
			TopologicalSort(nextVertex);
		}

		std::cout << "building: " << graph[index].data << std::endl;
	}

	Node graph[size];
	int numNodes = 0;
	bool visited[size];
};