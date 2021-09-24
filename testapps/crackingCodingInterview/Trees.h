//
// Created by mitso23 on 1/17/21.
//
#ifndef TRAINING_TESTAPPS_CRACKINGCODINGINTERVIEW_TREES_H_
#define TRAINING_TESTAPPS_CRACKINGCODINGINTERVIEW_TREES_H_

#include <iostream>

namespace Tree
{
	struct Node
	{
		int id;
		Node* sibling;
		Node* child;
	};

	struct Employee
	{
		void AddEmployee(unsigned int childId, unsigned int parentId)
		{
			Node* parent = nullptr;
			if (employees[parentId] == nullptr)
			{
				employees[parentId] = new Node();
				parent = employees[parentId];
				parent->id = parentId;
			}
			else
			{
				parent = employees[parentId];
			}

			Node* child;
			if (employees[childId] == nullptr)
			{
				employees[childId] = new Node();
				child = employees[childId];
				child->id = childId;
			}
			else
			{
				child = employees[childId];
			}

			if (!parent->child)
			{
				parent->child = child;
			}
			else
			{
				if (parent->child->sibling == nullptr)
				{
					parent->child->sibling = child;
				}
				else
				{
					Node* previous = parent->child->sibling;
					Node* current = parent->child->sibling->sibling;
					while (current)
					{
						previous = current;
						current = current->sibling;
					}

					previous->sibling = child;
				}
			}
		}

		void _DisplayEmployeeRec(Node* current)
		{
			if(current == nullptr)
			{
				return;
			}

			std::cout << current->id << std::endl;
			_DisplayEmployeeRec(current->child);
			_DisplayEmployeeRec(current->sibling);
		}

		void DisplayEmployee(unsigned int id)
		{
			Node* current = employees[id];
			_DisplayEmployeeRec(current->child);
		}

		Node* employees[1000];
	};

	struct BinNode
	{
		BinNode() = default;
		BinNode(int _data) : data(_data)
		{

		}
		BinNode* left;
		BinNode* right;
		int height;
		int data;
	};

	struct BinTree
	{
		BinNode* root;
	};

	void CreateBinaryTree(int sorted[], int start, int end, BinNode*& node)
	{
		if (start > end)
		{
			return;
		}

		int mid = start + (end - start) / 2;

		if (node == nullptr)
		{
			node = new BinNode();
			node->data = sorted[mid];
		}
		else
		{
			BinNode* current = node;
			while(current)
			{
				if(sorted[mid] >= current->data)
				{
					if (current->right)
					{
						current = current->right;
					}
					else
					{
						current->right = new BinNode();
						current->right->data = sorted[mid];
						break;
					}
				}
				else
				{
					if (current->left)
					{
						current = current->left;
					}
					else
					{
						current->left = new BinNode();
						current->left->data = sorted[mid];
						break;
					}
				}
			}
		}

		CreateBinaryTree(sorted, start, mid - 1, node);
		CreateBinaryTree(sorted, mid + 1, end, node);
	}

	void PrintBinaryTree(BinNode* node)
	{
		if (!node)
		{
			return;
		}

		std::cout << node->data << std::endl;
		PrintBinaryTree(node->left);
		PrintBinaryTree(node->right);
	}

	int CheckTreeBalanced(BinNode* node)
	{
		if (!node)
		{
			return -1;
		}

		auto leftCount = CheckTreeBalanced(node->left);
		auto righCount = CheckTreeBalanced(node->right);

		std::cout << "parent: " << node->data << " left: " << leftCount << " right: " << righCount << std::endl;

		if (leftCount == -2 || righCount == -2)
		{
			return  -2;
		}

		if(std::abs(leftCount - righCount) >=2)
		{
			return -2;
		}

		return std::max(leftCount, righCount) + 1;
	}

	bool CheckTreeBinarySearch(BinNode* node, int max, int min)
	{
		if(!node)
		{
			return true;
		}

		std::cout << "node->data: " << node->data << " max: " << max << " min: " << min << std::endl;

		if(node->data >= min && node->data <=max)
		{
			bool leftTree = CheckTreeBinarySearch(node->left, node->data, min);
			bool rightTree = CheckTreeBinarySearch(node->right, max, node->data);

			if (leftTree && rightTree)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	int FindCommonAncestor(BinNode* current, BinNode* left, BinNode* right)
	{
		static bool found = false;

		if (!current)
		{
			return 0;
		}

		int counter = 0;
		if (current == left || current == right)
		{
			++counter;
		}

		std::cout << "current: " << current->data << " counter: " << counter << std::endl;

		int lCounter = FindCommonAncestor(current->left, left, right);
		if (found)
		{
			return 2;
		}
		else
		{
			counter += lCounter;
			if (counter == 2 && current != left && current != right)
			{
				std::cout << "found: " << current->data << std::endl;
				found = true;
				return 2;
			}
		}

		int rCounter = FindCommonAncestor(current->right, left, right);
		if (found)
		{
			return 2;
		}
		else
		{
			counter += rCounter;
			if (counter == 2 && current != left && current != right)
			{
				std::cout << "found: " << current->data << std::endl;
				found = true;
				return counter;
			}
		}

		return counter;
	}

	bool CheckTreeMatch(BinNode* l, BinNode* r)
	{
		if (!l && !r)
		{
			return true;
		}
		else if (!l || !r)
		{
			return false;
		}
		else if (l->data == r->data)
		{
			return CheckTreeMatch(l->left, r->left) && CheckTreeMatch(l->right, r->right);
		}
		else
		{
			return false;
		}
	}

	bool CheckSubTree(BinNode* l, BinNode* r)
	{
		if (r == nullptr)
		{
			return true;
		}
		else if (l == nullptr)
		{
			return false;
		}

		if (CheckTreeMatch(l, r))
		{
			return true;
		}
		else
		{
			return CheckSubTree(l->left, r) || CheckSubTree(l->right, r);
		}
	}

	int FindCommonAncestor2(BinNode* current, BinNode* l, BinNode* r)
	{
		if (!current)
		{
			return 0;
		}

		int count = 0;
		if (current == l || current == r)
		{
			++count;
		}

		count+= FindCommonAncestor2(current->left, l, r);
		if (count == 2 && (current != r && current != l))
		{
			std::cout << "common ancestor is: " << current->data << std::endl;
			return count;
		}

		count+= FindCommonAncestor2(current->right, l, r);
		if (count == 2 && (current != r && current != l))
		{
			std::cout << "common ancestor is: " << current->data << std::endl;
			return count;
		}

		return count;

	}
}





#endif //TRAINING_TESTAPPS_CRACKINGCODINGINTERVIEW_TREES_H_
