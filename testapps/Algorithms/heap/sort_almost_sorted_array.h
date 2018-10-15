/*
 * sort_almost_sorted_array.h
 *
 *  Created on: 11 Feb 2018
 *      Author: mitso23
 */

#ifndef SORT_ALMOST_SORTED_ARRAY_H_
#define SORT_ALMOST_SORTED_ARRAY_H_

#include "binary_heap.h"

/*
 * We can sort such arrays more efficiently with the help of Heap data structure. Following is the detailed process that uses Heap.
	1) Create a Min Heap of size k+1 with first k+1 elements. This will take O(k) time (See this GFact)
	2) One by one remove min element from heap, put it in result array, and add a new element to heap from remaining elements.
 */

void sort_almost_sorted_array(int* arr, unsigned int size, unsigned int k)
{
	Heap h(k + 1);
	int* sortedArray = new int[size];
	int index = 0;

	for(unsigned int i=0; i< k + 1; ++i)
	{
		h.insertItem(arr[i]);
	}

	h.printHeap();
	int minValue = 0;
	h.getMinValue(minValue);
	std::cout << "min: " << minValue << std::endl;
	sortedArray[index++] = minValue;

	for(unsigned int i= k+1; i< size; ++i)
	{
		std::cout << "adding new value: " << arr[i] << std::endl;

		h.insertItem(arr[i]);

		h.printHeap();
		h.getMinValue(minValue);
		std::cout << "min: " << minValue << std::endl;
		sortedArray[index++] = minValue;
	}

	for(unsigned int i=0; i< index; ++i)
	{
		//std::cout << sortedArray[i] << std::endl;
	}

	delete[] sortedArray;
}

#endif /* SORT_ALMOST_SORTED_ARRAY_H_ */
