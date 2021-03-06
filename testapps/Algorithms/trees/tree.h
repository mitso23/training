/*
 * tree.h
 *
 *  Created on: 26 Sep 2017
 *      Author: mitso23
 */

#ifndef TREE_H_
#define TREE_H_

#include <cmath>
#include <queue>

class Tree
{
public:
	class Node
	{
	public:
		Node(int data) : m_data(data)
		{

		}

		int m_data;
		Node* m_left = nullptr;
		Node* m_right = nullptr;
		Node* m_parent = nullptr;
		bool m_visited = false;
	};

	struct DisplayInfo
	{
		int data = 0;
		int pos = 0;
		int parentData = 0;
		int level = 0;
	};

	struct TreeIterator
	{
		TreeIterator(Node* node, Node* root, Node* minNode)
		: m_current(node)
		, m_root(root)
		, m_minNode(minNode)
		{
			m_current->m_visited = true;
		}

		TreeIterator* getPrevious()
		{
			Node* returnNode = nullptr;

			if (!m_current)
			{

			}
			else if (m_current->m_right && !m_current->m_right->m_visited)
			{
				while(m_current && m_current->m_right)
				{
					m_current = m_current->m_right;
				}

				returnNode = m_current;
			}
			else if (m_current->m_left && !m_current->m_left->m_visited)
			{
				m_current = m_current->m_left;

				while(m_current && m_current->m_right && !m_current->m_right->m_visited)
				{
					m_current = m_current->m_right;
				}

				returnNode = m_current;
			}
			else if (m_current->m_parent && !m_current->m_parent->m_visited)
			{
				returnNode = m_current->m_parent;
			}
			else if (m_current != m_minNode)
			{
				std::cout << "going back " << std::endl;
				while(m_current!= m_minNode)
				{
					m_current = m_current->m_parent;
					if (!m_current->m_visited)
					{
						break;
					}
				}

				//std::cout << "grantparent: " << std::endl;
				returnNode = m_current;
			}

			if (returnNode)
			{
				returnNode->m_visited = true;
				return new TreeIterator(returnNode, m_root, m_minNode);
			}
			else
			{
				return nullptr;
			}
		}

		TreeIterator*  getNext()
		{
			Node* returnNode = nullptr;

			if (!m_current)
			{
				//std::cout << "current null " << std::endl;
			}
			else if (m_current == m_root && !m_current->m_right->m_visited)
			{
				m_current = m_current->m_right;

				//Find the smallest element
				while(m_current && m_current->m_left)
				{
					m_current = m_current->m_left;
				}

				returnNode = m_current;
			}
			else if (m_current->m_left && !m_current->m_left->m_visited)
			{
				//std::cout << "left" << std::endl;
				returnNode = m_current->m_left;
			}
			else if (m_current->m_right && !m_current->m_right->m_visited)
			{
				//std::cout << "right" << std::endl;
				returnNode = m_current->m_right;
			}
			else if (m_current->m_parent && !m_current->m_parent->m_visited)
			{
				//std::cout << "parent" << std::endl;
				returnNode = m_current->m_parent;
			}
			else if (m_current->m_parent && m_current->m_parent->m_parent && !m_current->m_parent->m_parent->m_visited)
			{
				//std::cout << "grantparent: " << std::endl;
				returnNode = m_current->m_parent->m_parent;
			}

			if (returnNode)
			{
				returnNode->m_visited = true;
				return new TreeIterator(returnNode, m_root, m_minNode);
			}
			else
			{
				std::cout << "null node" << m_current->m_parent << std::endl;
				return nullptr;
			}
		}

		unsigned int getData()
		{
			return m_current->m_data;
		}

	private:
		Node* m_current;
		Node* m_root;
		Node* m_minNode;
	};

	TreeIterator* GetMaxNode()
	{
		return new TreeIterator(m_maxNode, m_root, m_minNode);
	}

	TreeIterator* GetMinNode()
	{
		return new TreeIterator(m_minNode, m_root, m_minNode);
	}

	void AddData(int data)
	{
		if (!m_root)
		{
			m_root = new Node(data);
			m_maxNode = m_root;
			m_minNode = m_root;
		}
		else
		{
			auto start = m_root;
			while(start)
			{
				if (data < start->m_data)
				{
					if (!start->m_left)
					{
						start->m_left = new Node(data);
						start->m_left->m_parent = start;
						m_minNode = start->m_left;
						break;
					}
					else
						start = start->m_left;
				}
				else
				{
					if (!start->m_right)
					{
						start->m_right = new Node(data);
						start->m_right->m_parent = start;
						if (start->m_right->m_data > m_maxNode->m_data)
						{
							m_maxNode = start->m_right;
						}
						break;
					}
					else
						start = start->m_right;
				}
			}
		}
	}

	template<typename F>
	void iterateItems(F f)
	{
		m_iterateItemsInorder(m_root, f);
	}

	void PrintData()
	{
		std::map<int, std::vector<DisplayInfo>> tree;

		auto ll = [&tree](int data, int level, int parentData)
		{
			DisplayInfo info;
			info.data = data;
			info.level = level;
			info.parentData = parentData;

			tree[level].push_back(info);
		};

		//iterateItems(l);
		m_iterateItemsPreOrder(m_root, m_root, ll, 0);
		displayTree(tree);

	}
private:

	int getParentPos(int parentData, int level, std::map<int, std::vector<DisplayInfo>>& tree)
	{
		auto& elements = tree[level];

		for(const auto& item : elements)
		{
			if (item.data == parentData)
			{
				return item.pos;
			}
		}

		return -1;
	}

	void displayTree(std::map<int, std::vector<DisplayInfo>>& tree)
	{
		const auto depth = tree.size();
		int total = std::pow(2, depth - 1) * 2;
		static auto init = 0;

		for(auto it= tree.begin(); it != tree.end(); ++it)
		{
			int level = it->first;
			int currentTotal = std::pow(2, level);
			int numSpaces = total - currentTotal;
			int maxSpace = numSpaces / currentTotal;

			if(level == 0)
			{
				auto location = total / 2;
				init = location;
				for(int i=0; i< location; ++i)
				{
					std::cout << "  ";
				}

				std::cout << it->second[0].data;
				it->second[0].pos = location;

				for(int i=location+1; i< total; ++i)
				{
					std::cout << "  ";
				}

				std::cout << std::endl;
			}
			else
			{
				auto& displayData = it->second;
				std::vector<std::pair<int, int> > positions;
				init = init / 2;

				for(auto it2 = displayData.begin(); it2!= displayData.end(); ++it2)
				{
					const auto position = getParentPos(it2->parentData, level - 1, tree);

					if (position < 0)
					{
						std::cerr << "can't find parent position for data: " << it2->data << " level: " << it2->level << " parent: " << it2->parentData << std::endl;
						return;
					}

					if (it2->data < it2->parentData)
					{

						it2->pos = position - init;
						positions.push_back(std::make_pair(it2->data, it2->pos));

					}
					else
					{
						it2->pos = position + init;
						positions.push_back(std::make_pair(it2->data, it2->pos));
					}

					//std::cout << "data: " << it2->data << " pos: " << it2->pos << " parent: " << it2->parentData << " level: " << level << " space: " << maxSpace << std::endl;
				}

				printLevel(total, positions);

			}
		}
	}

	void printLevel(int length, const std::vector<std::pair<int, int> >& positions)
	{
		auto positionIt = positions.begin();
		for(int i=0; i< length; ++i)
		{
			if (positionIt == std::end(positions))
			{
				std::cout << std::endl;
				return;
			}
			else if (positionIt->second == i)
			{
				std::cout << positionIt->first;
				++positionIt;
			}
			else
			{
				std::cout << "  ";
			}

		}

		std::cout << std::endl;
	}

	template<typename F>
	void m_iterateItemsInorder(Node* node, F f)
	{
		if (node == nullptr)
		{
			return;
		}

		m_iterateItemsInorder(node->m_left, f);
		f(node->m_data);
		m_iterateItemsInorder(node->m_right, f);
	}

	template<typename F>
	void m_iterateItemsPreOrder(Node* node, Node* parent, F f, int actualLevel)
	{
		if (node == nullptr)
		{
			return;
		}

		//std::cout << " data: " << node->m_data << " level: " << actualLevel << "parent: " << parent->m_data << std::endl;
		f(node->m_data, actualLevel, parent->m_data);

		if (node->m_left)
		{
			NodeInfo info;

			info.node = node->m_left;
			info.parent = node;
			info.level = actualLevel + 1;

			m_queue.push(info);
		}

		if (node->m_right)
		{
			NodeInfo info;

			info.node = node->m_right;
			info.parent = node;
			info.level = actualLevel + 1;

			m_queue.push(info);
		}

		if (!m_queue.empty())
		{
			auto next = m_queue.front();
			m_queue.pop();
			m_iterateItemsPreOrder(next.node, next.parent, f, next.level);
		}
	}

public:
	struct NodeInfo
	{
		Node* node;
		Node* parent;
		int level;
	};

	Node* m_root = nullptr;
	Node* m_maxNode = m_root;
	Node* m_minNode = m_root;

	std::queue<NodeInfo> m_queue;
};


int Height(Tree::Node* node)
{
	return node == nullptr ? 0 : std::max(1 + Height(node->m_left), 1 + Height(node->m_right));
}



#endif /* TREE_H_ */
