#ifndef FIND_MINUMUM_HEIGHT_BINARY_TREE_H_
#define FIND_MINUMUM_HEIGHT_BINARY_TREE_H_

#include "tree.h"

    class QueueNode
    {
    public:
        QueueNode(int _depth, Tree::Node* _node) : depth(_depth), node(_node)
        {

        }
    public:
        int depth = -1;
        Tree::Node* node = nullptr;
        QueueNode* next = nullptr;
    };

    class Queue
    {
    public:
        void push_back(Tree::Node* node, int depth)
        {
            if (!m_root)
            {
                m_root = new QueueNode(depth, node);
            }
            else
            {
                auto current = m_root;

                while(current && current->next)
                {
                    current= current->next;
                }

                current->next = new QueueNode(depth, node);
            }

        }

    public:
        QueueNode* m_root = nullptr;
    };

    int findMinimumHeight(Tree::Node *node)
    {
        if (node == nullptr)
        {
            return 1;
        }

        int leftHeight = findMinimumHeight(node->m_left);
        int rightHeight = findMinimumHeight(node->m_right);

        std::cout << "node: " << node->m_data << " left: " << leftHeight << " right: " << rightHeight << std::endl;

        return std::min(leftHeight, rightHeight) + 1;

    }

    int findMinimumHeightOptimized(Tree::Node* node)
    {
        if (node == nullptr)
        {
            return 0;
        }

        Queue q;
        q.push_back(node, 1);
        auto current = q.m_root;

        while(current)
        {
            int depth = current->depth;
            auto node = current->node;

            if (!node->m_left && !node->m_right)
            {
                return depth;
            }

            if (node->m_left)
            {
                q.push_back(node->m_left, depth + 1);
            }

            if (node->m_right)
            {
                q.push_back(node->m_right, depth + 1);
            }

            current = current->next;
        }
    }

    void findMinimumHeightBackTracking(Tree::Node *node, unsigned int &min, unsigned int &count)
    {
        if (node == nullptr)
        {
            count = 0;
            return;
        }

        std::cout << "current node " << node->m_data << " min: " << min << " count: " << count << std::endl;

        if (node->m_left)
        {
            if (count < min)
            {
                std::cout << "left: count < min" << std::endl;

                ++count;
                findMinimumHeightBackTracking(node->m_left, min, count);
                --count;

                if (count >= min)
                {
                    std::cout << "left: count > min" << std::endl;
                    return;
                }
            } else
            {
                std::cout << "left: count > min" << std::endl;
                return;
            }
        }

        if (node->m_right)
        {
            if (count < min)
            {
                std::cout << "right: count < min" << std::endl;
                ++count;
                findMinimumHeightBackTracking(node->m_right, min, count);
                --count;

                if (count >= min)
                {
                    std::cout << "right: count > min" << std::endl;
                    return;
                }
            } else
            {
                std::cout << "right: count < min" << std::endl;
                return;
            }
        }

        if (node->m_left == NULL && node->m_right == NULL)
        {
            std::cout << "leaf node" << std::endl;
            if (count < min)
            {
                min = count;
            }
        }
    }

#endif /* FIND_MINUMUM_HEIGHT_BINARY_TREE_H_ */
