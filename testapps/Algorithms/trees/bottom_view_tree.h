/*
 * bottom_view_tree.h
 *
 *  Created on: 12 Jan 2018
 *      Author: mitso23
 */

#ifndef BOTTOM_VIEW_TREE_H_
#define BOTTOM_VIEW_TREE_H_

#include "tree.h"
#include <queue>

#define MAX_TREE_DEPTH 100
int DistanceHash[MAX_TREE_DEPTH*2];

struct NodeInfo
{
	NodeInfo(Tree::Node* _node, unsigned int _distance) : node(_node), distance(_distance)
	{

	}
	Tree::Node* node;
	unsigned int distance;
};

std::queue<NodeInfo> qNodes;

void traverseTree(Tree::Node* node, int distance)
{
	if (node == nullptr)
	{
		return;
	}

	//std::cout << "node: " << node->m_data << " distance: " << distance << std::endl;

	DistanceHash[distance + MAX_TREE_DEPTH] = node->m_data;

	if (node->m_left)
		qNodes.push(NodeInfo(node->m_left, distance + 1));

	if (node->m_right)
		qNodes.push(NodeInfo(node->m_right, distance - 1));

	while(!qNodes.empty())
	{
		auto& nextNode = qNodes.front();
		qNodes.pop();

		traverseTree(nextNode.node, nextNode.distance);
	}
}

void printBottomView(Tree::Node* node)
{
	for (unsigned int i=0; i< MAX_TREE_DEPTH*2; ++i)
	{
		DistanceHash[i] = -100;
	}
	traverseTree(node, 0);

	for(unsigned int i=MAX_TREE_DEPTH*2; i> 0; --i)
	{
		if (DistanceHash[i - 1] != -100)
		{
			std::cout << "node: " << DistanceHash[i-1] << std::endl;
		}
	}
}

#endif /* BOTTOM_VIEW_TREE_H_ */
