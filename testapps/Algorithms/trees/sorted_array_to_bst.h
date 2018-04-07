#ifndef SORTED_ARRAY_TO_BST_H_
#define SORTED_ARRAY_TO_BST_H_

#include "red_black_tree.h"

void sortedArrayToTree(int arr[], int low, int high, RED_BLACK_TREE::RBTree* tree)
{
	if (low > high)
	{
		return;
	}

	auto mid = (high + low  + 1)/2;
	tree->insert(arr[mid]);

	std::cout << "low: " << low << " high: " << high << " mid: " << mid << " val: " << arr[mid] << std::endl;

	sortedArrayToTree(arr, low, mid - 1, tree);
	sortedArrayToTree(arr, mid + 1, high, tree);
}


#endif /* SORTED_ARRAY_TO_BST_H_ */
