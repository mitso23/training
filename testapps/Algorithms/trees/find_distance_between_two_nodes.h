/*
 * find_distance_between_two_nodes.h
 *
 *  Created on: 5 Jan 2018
 *      Author: mitso23
 */

#ifndef FIND_DISTANCE_BETWEEN_TWO_NODES_H_
#define FIND_DISTANCE_BETWEEN_TWO_NODES_H_

Tree::Node* findDistanceNodesRec(Tree::Node* root, int key1, int key2, bool& found, int arr[3], int& count)
{
	if (root == nullptr)
	{
		std::cout << "null" << std::endl;
		return nullptr;
	}

	std::cout << "key: " << root->m_data << " count: " << count << std::endl;

	if (root->m_data == key1 || root->m_data == key2)
	{
		std::cout << "key count: " << count << " node: " << root->m_data << std::endl;

		if (arr[0] == -1)
		{
			arr[0] = count;
		}
		else
		{
			arr[1] = count;
		}

		return root;
	}

	++count;
	auto l = findDistanceNodesRec(root->m_left, key1, key2, found, arr, count);
	auto r = findDistanceNodesRec(root->m_right, key1, key2, found, arr, count);
	--count;

	if (l == nullptr && r == nullptr)
	{
		std::cout << "l and r null " << std::endl;
		return nullptr;
	}
	else if (l && r)
	{
		std::cout << "common ancestor: " << root->m_data << " count: " << count << std::endl;
		found = true;
		arr[2] = count;
		return root;
	}
	else if (l)
	{
		return l;
	}
	else if (r)
	{
		return r;
	}
}

int findDistanceNodes(Tree::Node* root, int key1, int key2)
{
	bool found = false;
	int count = 0;
	int arr[3] = { -1 };

	auto res = findDistanceNodesRec(root, key1, key2, found, arr, count);

	if (found)
		return std::abs(arr[0] + arr[1] - 2*arr[2]);
	else
		return -1;
}


#endif /* FIND_DISTANCE_BETWEEN_TWO_NODES_H_ */
