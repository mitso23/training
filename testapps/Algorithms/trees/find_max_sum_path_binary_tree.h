//
// Created by mitso23 on 27/12/17.
//

#ifndef TRAINING_FIND_MAX_SUM_PATH_BINARY_TREE_H
#define TRAINING_FIND_MAX_SUM_PATH_BINARY_TREE_H

#include "tree.h"

#include <limits>

int findMaxSumPathRec(Tree::Node* node, int& res)
{
    if (node == nullptr)
    {
        return 0;
    }

    l = findMaxSumPath(node->m_left, res);
    r = findMaxSumPath(node->m_right, res);

    const auto single_max = std::max(std::max(l,r) + node->m_data, node->m_data);
    const auto max_top = std::max(single_max, l + r + node->m_data);

    res = std::max(max_top, res);

    return single_max;
}

int findMaxSumPath(Tree::Node* node)
{
    int res = std::numeric_limits<int>::max();
    findMaxSumPathRec(node, res);
    return res;
}


#endif //TRAINING_FIND_MAX_SUM_PATH_BINARY_TREE_H
