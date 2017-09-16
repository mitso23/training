/*
 * mergeSort.h
 *
 *  Created on: 18 Mar 2017
 *      Author: mitso23
 */

#ifndef MERGESORT_H_
#define MERGESORT_H_

#include <string.h>
#include <iostream>

void merge(unsigned int* arr, unsigned startLeft, unsigned endLeft, unsigned startRight, unsigned endRight, unsigned int size)
{
	unsigned int leftSize = endLeft - startLeft + 1;
	unsigned int rightSize = endRight - startRight + 1;

	unsigned int* leftStart = arr + startLeft;
	unsigned int* rightStart = arr + startRight;
	unsigned int* resultStart = arr + startLeft;

	unsigned leftPos = 0;
	unsigned rightPos = 0;
	unsigned resultPos = 0;

	unsigned int LeftBuffer[leftSize];
	unsigned int RightBuffer[rightSize];

	memcpy(LeftBuffer, leftStart, sizeof(unsigned) * leftSize);
	memcpy(RightBuffer, rightStart, sizeof(unsigned) * rightSize);

	while(leftPos < leftSize && rightPos < rightSize)
	{
		if (LeftBuffer[leftPos] < rightStart[rightPos])
		{
			resultStart[resultPos++] = LeftBuffer[leftPos++];
		}
		else
		{
			resultStart[resultPos++] = RightBuffer[rightPos++];
		}
	}

	while(leftPos < leftSize)
	{
		resultStart[resultPos++] = LeftBuffer[leftPos++];
	}

	while(rightPos < rightSize)
	{
		resultStart[resultPos++] = RightBuffer[rightPos++];
	}

	return;
}

void mergeSort(unsigned int* arr, unsigned int start, unsigned int end)
{
	if (start == end)
	{
		std::cout << "returning, start: " << start << " end: " << end << std::endl;
		return;
	}

	unsigned middle = start + (end - start) / 2;

	std::cout << "start: " << start << " end: " << end << " middle: " << middle << std::endl;

	mergeSort(arr, start, middle);
	mergeSort(arr, middle + 1, end);

	merge(arr, start, middle, middle + 1, end, end - start + 1);
}


#endif /* MERGESORT_H_ */
