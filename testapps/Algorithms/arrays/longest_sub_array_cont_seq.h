/*
 * longest_sub_array_cont_seq.h
 *
 *  Created on: 20 Jun 2018
 *      Author: mitso23
 */

#ifndef LONGEST_SUB_ARRAY_CONT_SEQ_H_
#define LONGEST_SUB_ARRAY_CONT_SEQ_H_

#include <numeric>

void longest_cont_sub_array(int* arr, unsigned int size)
{
	int min = arr[0];
	int max = arr[0];
	int* lastPos = arr;
	int* current = arr + 1;
	int* end = arr + size;
	unsigned maxCount = 0;

	while(lastPos < end)
	{
		std::cout << "current: " << *current << " min: " << min << " max: " << max << std::endl;

		if (*current < min)
		{
			min = *current;
			std::cout << "updating min to: " << min << std::endl;
		}
		else if (*current > max)
		{
			max = *current;
			std::cout << "updating max to: " << max << std::endl;
		}

		if (max - min == (current - lastPos))
		{
			std::cout << "new cont sub array found at pos: " << (current - arr) << " num: " << max - min<< std::endl;

			if ((max - min) > maxCount)
			{
				maxCount = (max - min) + 1;
			}
		}
		else if ((max - min) <= (end - current) + (current - lastPos))
		{
			std::cout << "still in the game" << std::endl;
		}
		else
		{
			std::cout << "starting new sub-array at pos: " << current - arr << std::endl;
			++lastPos;
		}

		++current;
		if (current == end)
		{
			std::cout << "current reached the end" << std::endl;
			current = lastPos + 1;
			min = *lastPos;
			max = *lastPos;
		}

	}

	std::cout << "max count: " << maxCount << std::endl;


}

#endif /* LONGEST_SUB_ARRAY_CONT_SEQ_H_ */
