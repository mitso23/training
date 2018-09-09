/*
 * segment_tree.h
 *
 *  Created on: 11 Aug 2018
 *      Author: mitso23
 */

#ifndef SEGMENT_TREE_H_
#define SEGMENT_TREE_H_

#include "tree.h"
#include <queue>

void createSegmentTree(int* sumTree, int currentNode, int* input, unsigned l, unsigned r)
{
	if (l == r)
	{
		sumTree[currentNode] = input[l];
	}
	else
	{
		//this will prevent overflowing
		int mid = l + (r - l)/2;
		createSegmentTree(sumTree, currentNode*2 + 1, input, l, mid);
		createSegmentTree(sumTree, currentNode*2 + 2, input, mid + 1, r);

		sumTree[currentNode] = sumTree[currentNode*2 + 1] + sumTree[currentNode*2 + 2];

	}
}


void traverseSegmentTree(int* sumTree, int size, int currentNode, std::queue<int>& q)
{
	if (currentNode >= size - 1)
	{
		return;
	}

	std::cout << sumTree[currentNode] << std::endl;

	q.push(2*currentNode + 1);
	q.push(2*currentNode + 2);

	if (!q.empty())
	{
		auto next = q.front();
		q.pop();
		traverseSegmentTree(sumTree, size, next, q);
	}
}

int findSumSegmentTree(int* summTree, int size, int start, int end)
{

}

#endif /* SEGMENT_TREE_H_ */
