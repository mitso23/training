/*
 * insertion_sort.h
 *
 *  Created on: 25 Mar 2018
 *      Author: mitso23
 */

#ifndef INSERTION_SORT_H_
#define INSERTION_SORT_H_

void insertion_sort(int arr[], unsigned int size)
{
	int i=1;
	while(i < size)
	{
		int j=i;
		//std::cout << "i: " << i << " j: " << j << " arr[j]: " << arr[j] << std::endl;
		while(j > 0)
		{
			if (arr[j-1] > arr[j])
			{
				//std::cout << "swapping: " << arr[j-1] << " with: " << arr[j] << std::endl;

				int temp = arr[j];
				arr[j] = arr[j-1];
				arr[j-1] = temp;
				--j;
			}
			else
			{
				break;
			}
		}

		++i;
	}
}

#endif /* INSERTION_SORT_H_ */
