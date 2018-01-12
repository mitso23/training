/*
 * convert_bst_sum_tree.h
 *
 *  Created on: 11 Nov 2017
 *      Author: mitso23
 */

#ifndef CONVERT_BST_SUM_TREE_H_
#define CONVERT_BST_SUM_TREE_H_

#include "tree.h"

int convert_bst_sum_tree(Tree::Node* node)
{
	if (node == NULL)
		return 0;

	int old_data = node->m_data;

	node->m_data = convert_bst_sum_tree(node->m_left) + convert_bst_sum_tree(node->m_right);

	return node->m_data + old_data;
}

#endif /* CONVERT_BST_SUM_TREE_H_ */
