/*
 * find_element_sorted_rotated.h
 *
 *  Created on: 15 Feb 2018
 *      Author: mitso23
 */

#ifndef FIND_ELEMENT_SORTED_ROTATED_H_
#define FIND_ELEMENT_SORTED_ROTATED_H_

bool find_element_rec(int* arr, unsigned int low, unsigned int high, int value)
{
	if (low <= high)
	{
		unsigned int m = low + (high - low)/2;

		std:cout << "low: " << low << " high: " << high << " medium: " << m << std::endl;

		if (value == m)
		{
			std::cout << "found " << std::endl;
			return true;
		}

		if (value <= arr[high] && value >=arr[m])
		{
			return find_element_rec(arr, m + 1, high, value);
		}
		else if (value >= arr[low] && value <=arr[m])
		{
			return find_element_rec(arr, low, m - 1, value);
		}
		else if (arr[low] > arr[m])
		{
			return find_element_rec(arr, low, m - 1, value);
		}
		else if (arr[high] < arr[m])
		{
			return find_element_rec(arr, m + 1, high, value);
		}
	}

	return false;

}

bool find_element(int* arr, unsigned int size, int value)
{
	return find_element_rec(arr, 0, size - 1, value);
}

#endif /* FIND_ELEMENT_SORTED_ROTATED_H_ */
