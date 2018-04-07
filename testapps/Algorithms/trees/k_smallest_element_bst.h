/*
 * k_smallest_element_bst.h
 *
 *  Created on: 13 Mar 2018
 *      Author: mitso23
 */

#ifndef K_SMALLEST_ELEMENT_BST_H_
#define K_SMALLEST_ELEMENT_BST_H_

#include "red_black_tree.h"

int find_k_smallest_element(RED_BLACK_TREE::Node* current, int k)
{
	if (current->numLeftCount + 1 == k)
	{
		return current->data;
	}
}


#endif /* K_SMALLEST_ELEMENT_BST_H_ */
