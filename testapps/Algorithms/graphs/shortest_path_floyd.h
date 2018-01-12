/*
 * shortest_path_floyd.h
 *
 *  Created on: 23 Sep 2017
 *      Author: mitso23
 */

#ifndef SHORTEST_PATH_FLOYD_H_
#define SHORTEST_PATH_FLOYD_H_

#include <algorithm>

#define V 4
auto INF =  std::numeric_limits<int>::max();

int graph[V][V] = {

		{ 0,    INF, -2, 	INF },
		{ 4,  	0,    3, 	INF },
		{ INF,  INF,  0, 	2 },
		{ INF, -1,    INF, 	0 },

};

int calculateMinDistance(int src, int dst, int intermediate)
{
	//std::cout << "src: " << src << " dst: " << dst << " intermediate: " << intermediate << std::endl;

	if (intermediate == 0)
	{
		//std::cout << "base distance : " << graph[src][dst] << std::endl;
		return graph[src][dst];
	}

	auto l1 = calculateMinDistance(src, dst, intermediate - 1);
	auto l2 = calculateMinDistance(src, intermediate - 1, intermediate - 1);
	auto l3 = calculateMinDistance(intermediate - 1, dst, intermediate - 1);

	//std::cout << "l1: " << l1 << " l2: " << l2 << " l3: " << l3 << std::endl;

	if (l2 == INF || l3 == INF)
	{
		return l1;
	}
	else
	{
		return std::min(l1,	l2 + l3);
	}
}

#endif /* SHORTEST_PATH_FLOYD_H_ */
