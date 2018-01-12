/*
 * graph_mst_prime.h
 *
 *  Created on: 31 Oct 2017
 *      Author: mitso23
 */

#ifndef GRAPH_MST_PRIME_H_
#define GRAPH_MST_PRIME_H_

#include "graph.h"
#include <map>

/*Algorithm
1) Create a set mstSet that keeps track of vertices already included in MST.
2) Assign a key value to all vertices in the input graph. Initialize all key values as INFINITE.
 	 Assign key value as 0 for the first vertex so that it is picked first.
3) While mstSet doesn’t include all vertices
….a) Pick a vertex u which is not there in mstSet and has minimum key value.
….b) Include u to mstSet.
….c) Update key value of all adjacent vertices of u. To update the key values, iterate through all adjacent vertices.
	 For every adjacent vertex v, if weight of edge u-v is less than the previous key value of v, update the key value as weight of u-v

*/
typedef int vertex_t;
typedef int vertex_key_t;

void calculateMstTree(Graph* graph)
{
	std::multimap<vertex_key_t, vertex_t> KeyToVertex;
	std::map<vertex_t, vertex_key_t> VertexToKey;
	std::vector<vertex_t> vertices;

	for(int i=1; i< graph->m_connections.size(); ++i)
	{
		KeyToVertex.insert(std::make_pair(std::numeric_limits<int>::max(), i));
		VertexToKey.insert(std::make_pair(i, std::numeric_limits<int>::max()));
	}

	KeyToVertex.insert(std::make_pair(0, 0));
	VertexToKey.insert(std::make_pair(0, 0));

	while (vertices.size() != graph->m_connections.size())
	{
		//get the minimum weight vertex
		auto vertex = KeyToVertex.begin()->second;

		if (std::find(vertices.begin(), vertices.end(), vertex) != std::end(vertices))
		{
			std::cout << "vertex already in the list: " << vertex << " map size: " << KeyToVertex.size() << std::endl;
			KeyToVertex.erase(KeyToVertex.begin()->first);
			continue;
		}

		std::cout << "new vertex: " << vertex << std::endl;

		//remove it from the maps
		KeyToVertex.erase(KeyToVertex.begin());
		VertexToKey.erase(vertex);

		//Add it to the list of vertices
		vertices.push_back(vertex);

		for(auto it= graph->m_connections[vertex].begin(); it != graph->m_connections[vertex].end(); ++it)
		{
			auto adjVertex = it->first;
			auto adjVertexWeight = it->second;

			//if the new distance from vertex->adjVertex is smaller that the stored weight of adjVertex then update it
			if (VertexToKey.find(adjVertex) != std::end(VertexToKey) && adjVertexWeight < VertexToKey[adjVertex])
			{
				//erase previous entries
				{
					// Find all the vertices which have the provided weight [This is not very efficient]
					auto range = KeyToVertex.equal_range(VertexToKey[adjVertex]);
					for(auto it = range.first; it != range.second; ++it)
					{
						if (it->second == adjVertex)
						{
							KeyToVertex.erase(it);
						}
					}

					VertexToKey.erase(adjVertex);
				}

				//Add new entries
				std::cout << " updating: " << adjVertex << " with: " << adjVertexWeight << std::endl;
				VertexToKey[adjVertex] = adjVertexWeight;
				KeyToVertex.insert(std::make_pair(adjVertexWeight, adjVertex));
			}
			else
			{
				std::cout << " not updating: " << adjVertex << " with: " << adjVertexWeight << std::endl;
			}
		}
	}

}


#endif /* GRAPH_MST_PRIME_H_ */
