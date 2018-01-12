#ifndef CHECK_BINARY_TREE_FULL_H_
#define CHECK_BINARY_TREE_FULL_H_

#include "tree.h"

bool check_binary_tree_full(Tree::Node* tree)
{
	if (tree == nullptr)
	{
		return true;
	}

	if (!tree->m_left && !tree->m_right)
	{
		return true;
	}

	if (tree->m_left && tree->m_right)
	{
		return check_binary_tree_full(tree->m_left) && check_binary_tree_full(tree->m_right);
	}

	return false;
}

#endif /* CHECK_BINARY_TREE_FULL_H_ */
