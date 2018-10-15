/*
 * reverse_alternate_levels.h
 *
 *  Created on: 4 Feb 2018
 *      Author: mitso23
 */

#ifndef REVERSE_ALTERNATE_LEVELS_H_
#define REVERSE_ALTERNATE_LEVELS_H_

#include "tree.h"

#include <queue>

struct MyNodeInfo
{
	MyNodeInfo(Tree::Node* parent, Tree::Node* node)
			: m_parent(parent)
			, m_node(node)
	{

	}

	Tree::Node* m_parent = nullptr;
	Tree::Node* m_node = nullptr;

};

unsigned my_pow(unsigned int level)
{
	if (level == 0)
	{
		return 1;
	}
	else
	{
		return 2 * my_pow(level - 1);
	}
}

void reverseAlternateLevels(Tree::Node* current, Tree::Node* parent, unsigned int level, MyNodeInfo** arr, unsigned int numItems, unsigned int size, std::queue<MyNodeInfo>& queue)
{
	if (!current)
	{
		return;
	}

	std::cout << "current: " << current->m_data << " level: " << level << " arr pos: " << size << std::endl;

	if (current->m_left)
		queue.push(MyNodeInfo(current, current->m_left));

	if (current->m_right)
		queue.push(MyNodeInfo(current, current->m_right));

	auto nextLevel = level;
	auto numItemsLevel = my_pow(level);
	numItems++;

	if (level & 1)
	{
		arr[size++] = new MyNodeInfo(parent, current);

		if (size == numItemsLevel)
		{
			for(unsigned int i=size, j=0; i>0; i-=2,j+=2)
			{
				Tree::Node* parent = arr[j]->m_parent;

				std::cout << "orig ptr: " << parent << std::endl;
				auto leftChildData = arr[i - 1]->m_node->m_data;
				auto rightChildData = arr[i - 2]->m_node->m_data;

				parent->m_left->m_data =  leftChildData;
				parent->m_right->m_data = rightChildData;

			}

			size = 0;
			nextLevel += 1;
			numItems = 0;
		}
	}
	else
	{
		if (numItems == numItemsLevel)
		{
			nextLevel += 1;
			numItems = 0;
		}
	}

	while(!queue.empty())
	{
		auto item = queue.front();
		queue.pop();

		reverseAlternateLevels(item.m_node, item.m_parent, nextLevel, arr, numItems, size, queue);
	}
}

#endif /* REVERSE_ALTERNATE_LEVELS_H_ */
