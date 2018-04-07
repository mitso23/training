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

/*
If r > l
     1. Find the middle point to divide the array into two halves:
             middle m = (l+r)/2
     2. Call mergeSort for first half:
             Call mergeSort(arr, l, m)
     3. Call mergeSort for second half:
             Call mergeSort(arr, m+1, r)
     4. Merge the two halves sorted in step 2 and 3:
             Call merge(arr, l, m, r)
*/

void merge2(unsigned int* arr, unsigned int start, unsigned int mid, unsigned int end)
{
	auto leftArrSize = mid - start + 1;
	auto rightArrSize = end - mid;

	//std::cout << "start: " << start << " mid: " << mid << " end: " << end << "l size: " << leftArrSize << " r size: " << rightArrSize << std::endl;

	int *leftArr = new int[leftArrSize];
	int* rightArr = new int[rightArrSize];
	unsigned int leftArrIndex = 0;
	unsigned int rightArrIndex = 0;
	unsigned int arrIndex = start;

	for(unsigned int i=0; i< leftArrSize; ++i)
	{
		//std::cout << "left arr[i] " << arr[start + i] << std::endl;
		leftArr[i] = arr[start + i];
	}

	for(unsigned int i=0; i< rightArrSize; ++i)
	{
		rightArr[i] = arr[mid + i + 1];
		//std::cout << "right arr[i] " << rightArr[i] << std::endl;
	}

	while(leftArrIndex < leftArrSize && rightArrIndex < rightArrSize)
	{
		if (leftArr[leftArrIndex] < rightArr[rightArrIndex])
		{
			//std::cout << "arr[i] " << leftArr[leftArrIndex] << std::endl;
			arr[arrIndex++] = leftArr[leftArrIndex++];
		}
		else
		{
			//std::cout << "arr[i] " << rightArr[rightArrIndex] << std::endl;
			arr[arrIndex++] = rightArr[rightArrIndex++];
		}
	}

	while(leftArrIndex < leftArrSize)
	{
		//std::cout << "arr[i] " << leftArr[leftArrIndex] << std::endl;
		arr[arrIndex++] = leftArr[leftArrIndex++];
	}

	while( rightArrIndex < rightArrSize)
	{
		//std::cout << "arr[i] " << rightArr[rightArrIndex] << std::endl;
		arr[arrIndex++] = rightArr[rightArrIndex++];
	}
}

void mergeSort2(unsigned int* arr, unsigned int start, unsigned int end)
{
	//std::cout << "start: " << start << " end: " << end << std::endl;
	if (start >= end)
	{
		return;
	}

	auto middle = start + (end - start)/2;

	mergeSort2(arr, start, middle);
	mergeSort2(arr, middle + 1, end);

	merge2(arr, start, middle, end);
}

#endif /* MERGESORT_H_ */
