#include "tree.h"


//Algorithmic complexity is n^2 as we need to calculate the height of the tree at every single level
int CheckTreeBalanced(Tree::Node* node)
{
	if (node == nullptr)
	{
		return true;
	}

	int leftCount = Height(node->m_left);
	int rightCount = Height(node->m_right);

	std::cout << "parent: " << node->m_data <<  "leftCount: " << leftCount << " rightCount: " << rightCount << std::endl;

	if (std::abs(leftCount - rightCount) <=1 && CheckTreeBalanced(node->m_left) && CheckTreeBalanced(node->m_right))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Optimised version of checking if a tree is balanced
bool CheckTreeBalanced(Tree::Node* node, int* height)
{
	int lh, rh = 0;
	bool lTree , rTree = 0;

	if (node == nullptr)
	{
		*height = 0;
		return true;
	}

	lTree = CheckTreeBalanced(node->m_left, &lh);
	rTree = CheckTreeBalanced(node->m_right, &rh);

	*height = std::max(lh, rh) + 1;

	if (std::abs(lh -rh) >=2)
	{
		return false;
	}

	return lTree && rTree;

}
