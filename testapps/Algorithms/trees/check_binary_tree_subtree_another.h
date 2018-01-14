/*
 * check_binary_tree_subtree_another.h
 *
 *  Created on: 14 Jan 2018
 *      Author: mitso23
 */
#ifndef CHECK_BINARY_TREE_SUBTREE_ANOTHER_H_
#define CHECK_BINARY_TREE_SUBTREE_ANOTHER_H_

#include "tree.h"
#include <stack>


class TreeIterator
{
public:
	TreeIterator(Tree::Node* root) : m_root(root)
	{

	}

	bool getNext(int& result)
	{
		if (m_stackNodes.empty())
		{
			m_stackNodes.push(m_root);
			result = m_root->m_data;
			//m_visited[m_root->m_data] = true;
			return true;
		}
		else
		{
			auto& node = m_stackNodes.top();
			//std::cout << "current node: " << node->m_data << " size: " << m_stackNodes.size() << std::endl;

			if (node->m_left)
			{
				m_stackNodes.push(node->m_left);
				result =  node->m_left->m_data;
				//m_visited[node->m_left->m_data] = true;
				return true;
			}
			else if (node->m_right)
			{
				m_stackNodes.push(node->m_right);
				result =  node->m_right->m_data;
				//m_visited[node->m_right->m_data] = true;
				return true;
			}
			else
			{
				//std::cout << " removing: " <<  m_stackNodes.top()->m_data << std::endl;
				m_stackNodes.pop();

				while(!m_stackNodes.empty())
				{
					auto node = m_stackNodes.top();

					if (node->m_right)
					{
						m_stackNodes.pop();

						m_stackNodes.push(node->m_right);
						result =  node->m_right->m_data;
						//m_visited[node->m_right->m_data] = true;
						return true;
					}
					else
					{
						//std::cout << "removing " << node->m_data << std::endl;
						m_stackNodes.pop();
					}
				}

				return false;
			}
		}
	}

private:
	Tree::Node* m_root;
	std::stack<Tree::Node*> m_stackNodes;
	bool m_lastNode = false;
	int m_visited[1000] = { false };
};


#endif /* CHECK_BINARY_TREE_SUBTREE_ANOTHER_H_ */
