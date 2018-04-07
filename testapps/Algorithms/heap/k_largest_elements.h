/*
 * k_largest_elements.h
 *
 *  Created on: 11 Feb 2018
 *      Author: mitso23
 */

#ifndef K_LARGEST_ELEMENTS_H_
#define K_LARGEST_ELEMENTS_H_

#include "binary_heap.h"

void printKLargestElementsArray(int* arr, unsigned int size, unsigned int k)
{
	Heap h(k);

	for(unsigned int i=0; i< k; ++i)
	{
		h.insertItem(arr[i]);
	}

	//h.printHeap();

	for(unsigned int i=k; i< size; ++i)
	{
		if (arr[i] > h.getArr()[0])
		{

			h.getArr()[0] = arr[i];
			h.heapify(0);
			//h.printHeap();
		}
	}

	//h.printHeap();
}


#endif /* K_LARGEST_ELEMENTS_H_ */
