/*
 * binary_indexed_tree.h
 *
 *  Created on: 1 Dec 2018
 *      Author: mitso23
 */

#ifndef BINARY_INDEXED_TREE_H_
#define BINARY_INDEXED_TREE_H_

void updateNode(int* binaryIndexedTree, int size, int start, int value)
{
    int index = start + 1;

    while(index < size )
    {
        binaryIndexedTree[index]+= value;
        index+= index &(-index);
    }
}

int* createBinaryIndexedTree(const int* arr, int size)
{
    int* binaryIndexedTree = new int[size + 1]();

    for(unsigned int i=0; i< size + 1; ++i)
    {
        updateNode(binaryIndexedTree, size+1, i, arr[i]);
    }

    return binaryIndexedTree;
}

int getSum(const int* arr, int start)
{
    int index = start + 1;
    int sum = 0;
    while(index > 0)
    {
        std::cout << "index: " << index << std::endl;

        sum+= arr[index];
        index-= index&(-index);
    }

    return sum;
}

#endif /* BINARY_INDEXED_TREE_H_ */
