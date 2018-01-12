/*
 * find_common_anchestor.h
 *
 *  Created on: 3 Jan 2018
 *      Author: mitso23
 */

#ifndef FIND_COMMON_ANCHESTOR_H_
#define FIND_COMMON_ANCHESTOR_H_

#include "tree.h"

Tree::Node* findCommonAnchestor(Tree::Node* root, int key1, int key2, bool& foundKey1, bool& foundKey2)
{
	if (root == nullptr)
	{
		std::cout << "null" << std::endl;
		return nullptr;
	}

	std::cout << "key: " << root->m_data << std::endl;

	if (root->m_data == key1)
	{
		std::cout << "found: " << std::endl;
		foundKey1 = true;
		return root;
	}
	else if (root->m_data == key2)
	{
		std::cout << "found: " << std::endl;
		foundKey2 = true;
		return root;
	}

	auto l = findCommonAnchestor(root->m_left, key1, key2, foundKey1, foundKey2);
	auto r = findCommonAnchestor(root->m_right, key1, key2, foundKey1, foundKey2);

	if (l && r)
	{
		std::cout << "returning root" << std::endl;
		return root;
	}

	return l ? l : r;
}

Tree::Node* findCommonAnchestor(Tree::Node* root, int key1, int key2)
{
	bool foundKey1 = false;
	bool foundKey2 = false;

	auto res = findCommonAnchestor(root, key1, key2, foundKey1, foundKey2);

	if(foundKey1 && foundKey2 || (foundKey1 && findCommonAnchestor(root, key2, key2, foundKey1, foundKey2)) || (foundKey2 && findCommonAnchestor(root, key1, key1, foundKey1, foundKey2)))
	{
		return res;
	}

	return nullptr;
}

#endif /* FIND_COMMON_ANCHESTOR_H_ */
