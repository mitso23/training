/*
 * sort_array_zero_one_three.h
 *
 *  Created on: 2 Jun 2018
 *      Author: mitso23
 */

#ifndef SORT_ARRAY_ZERO_ONE_THREE_H_
#define SORT_ARRAY_ZERO_ONE_THREE_H_


void sortArrayOneTwoThree(int* arr, unsigned int size)
{
	unsigned int last = 0;
	unsigned int current = 0;
	unsigned int end = size;
	unsigned int expectedValue = 0;

	while(true)
	{
		while(current != end)
		{
			if (arr[current] == expectedValue)
			{
				if (current != last)
				{
					//std::cout << "swapping " << arr[current] << arr[last] << std::endl;

					//swap current with last
					unsigned int temp = arr[current];
					arr[current] = arr[last];
					arr[last] = temp;
				}

				++current;
				++last;
			}
			else
			{
				//std::cout << "not expected: " << arr[current] << std::endl;
				++current;
			}
		}

		++expectedValue;

		if (expectedValue > 2)
		{
			break;
		}

		if (current == last)
		{
			break;
		}

		current = last;

		//std::cout << "next round expected value: " << expectedValue << " starting:"  << current << std::endl;
	}
}

#endif /* SORT_ARRAY_ZERO_ONE_THREE_H_ */
