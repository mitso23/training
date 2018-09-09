/*
 * transform_bst_greater_sum.h
 *
 *  Created on: 30 Jul 2018
 *      Author: mitso23
 */

#ifndef TRANSFORM_BST_GREATER_SUM_H_
#define TRANSFORM_BST_GREATER_SUM_H_

#include "tree.h"

void transform_bst_great_sum(Tree::Node* current, unsigned int* sum)
{
	if (current == nullptr)
	{
		return;
	}

	transform_bst_great_sum(current->m_right, sum);
	current->m_data = sum;
	sum+= current->m_data;

	transform_bst_great_sum(current->m_left, sum);
}


#endif /* TRANSFORM_BST_GREATER_SUM_H_ */
