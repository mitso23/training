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

int findSumSegmentTree(int* sumTree, int currentNode, int start, int end, int segmentStart, int segmentEnd)
{
	if (segmentEnd == segmentStart)
	{
		//std::cout << "last node" << currentNode << " sum: " << sumTree[currentNode]  << std::endl;
		return sumTree[currentNode];
	}

	std::cout << "start: " << start << " end: " << end << " segmStart: " << segmentStart << " segmentEnd: " << segmentEnd << " node: " << currentNode << std::endl;

	//check if the entire region is inside the current region
	if (segmentStart >= start  && segmentEnd <= end)
	{
		//std::cout << "entire region in returnin sum" <<  sumTree[currentNode] << std::endl;
		return sumTree[currentNode];
	}

	int mid = segmentStart + (segmentEnd - segmentStart)/2;

	//std::cout << " mid: " << mid << std::endl;

	int sum = 0;
	if (start <= mid || end <=mid)
	{
		//std::cout << " going left: " << std::endl;
		sum+= findSumSegmentTree(sumTree, 2*currentNode + 1, start, end, segmentStart, mid);
	}

	if (start >= (mid + 1) || end >= (mid + 1))
	{
		//std::cout << " going right: " << std::endl;
		sum+= findSumSegmentTree(sumTree, 2*currentNode + 2, start, end, mid+1, segmentEnd);
	}

	//std::cout << "return sum " << sum << std::endl;
	return sum;
}

void updateSegmentTree(int* segmentTree, int currentNode, int targetValue, int updateValue, int startSegment, int endSegment)
{
	std::cout << "currentNode " << currentNode << " start: " << startSegment << " end: " << endSegment << std::endl;

	if ((startSegment == endSegment) && segmentTree[currentNode] == targetValue)
	{
		std::cout << "found target value " << targetValue << " at node: " << currentNode << std::endl;
		segmentTree[currentNode]+= updateValue;
		return;
	}
	else if (startSegment == endSegment)
	{
		std::cout << "can't find the value" << std::endl;
		return;
	}

	int mid = startSegment + (endSegment - startSegment)/2;
	segmentTree[currentNode]+=updateValue;

	if (targetValue < mid)
	{
		updateSegmentTree(segmentTree, 2*currentNode + 1, targetValue, updateValue, startSegment, mid);
	}
	else
	{
		updateSegmentTree(segmentTree, 2*currentNode + 2, targetValue, updateValue, mid + 1, endSegment);
	}
}

#endif /* SEGMENT_TREE_H_ */
