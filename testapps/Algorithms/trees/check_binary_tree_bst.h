/*
 * check_binary_tree_bst.h
 *
 *  Created on: 25 Feb 2018
 *      Author: mitso23
 */

#ifndef CHECK_BINARY_TREE_BST_H_
#define CHECK_BINARY_TREE_BST_H_

#include "tree.h"

bool checkBinaryTreeBstRec(Tree::Node* node, int range1, int range2)
{
	if (!node)
	{
		std::cout << "node null " << std::endl;
		return true;
	}

	std::cout << "node: " << node->m_data << " range1: " << range1 << " range2: " << range2 << std::endl;

	if ((node->m_data > range1 && node->m_data < range2))
	{
		return false;
	}

	 return checkBinaryTreeBstRec(node->m_left, std::numeric_limits<int>::min(),node->m_data) &&
			checkBinaryTreeBstRec(node->m_right, node->m_data, range2);

}

bool checkBinaryTreeBst(Tree::Node* node)
{
	return checkBinaryTreeBstRec(node->m_left, std::numeric_limits<int>::min(),node->m_data) &&
		   checkBinaryTreeBstRec(node->m_right, node->m_data, std::numeric_limits<int>::max());
}


#endif /* CHECK_BINARY_TREE_BST_H_ */
