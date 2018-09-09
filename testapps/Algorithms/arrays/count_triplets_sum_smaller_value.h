/*
 * count_triplets_sum_smaller_value.h
 *
 *  Created on: 19 Jun 2018
 *      Author: mitso23
 */

#ifndef COUNT_TRIPLETS_SUM_SMALLER_VALUE_H_
#define COUNT_TRIPLETS_SUM_SMALLER_VALUE_H_


#include <iostream>

void print_triplet_smaller_sum(int* arr, unsigned int size, unsigned int sum)
{
	for(unsigned int i=0; i + 2< size; ++i)
	{
		for(unsigned int j= i + 1 ; j + 1< size; ++j)
		{
			for(unsigned int k=j+1; k< size; ++k)
			{
				if (arr[i] + arr[j] + arr[k] < sum)
				{
					std::cout << "{" << arr[i] << ":" << arr[j] << ":" << arr[k] << "}" << std::endl;
				}
				else
				{
					std::cout << "greater, i: " << i << " j: " << j <<  " k: " << k << std::endl;

					if (j - i == 1)
					{
						std::cout << "breaking early j: " << j << " i: " << i << std::endl;
						return;
					}
					else
					{
						std::cout << "incrementing i: " << i << std::endl;
						i+=1;
						break;
					}
				}
			}
		}
	}
}

//optimized solution
int countTriplets(int arr[], int n, int sum)
{
    // Initialize result
    int ans = 0;

    // Every iteration of loop counts triplet with
    // first element as arr[i].
    for (int i = 0; i < n - 2; i++)
    {
        // Initialize other two elements as corner
        // elements of subarray arr[j+1..k]
        int j = i + 1, k = n - 1;

        // Use Meet in the Middle concept
        while (j < k)
        {
            // If sum of current triplet is more or equal,
            // move right corner to look for smaller values
            if (arr[i] + arr[j] + arr[k] >= sum)
                k--;

            // Else move left corner
            else
            {
                // This is important. For current i and j, there
                // can be total k-j third elements.
                ans += (k - j);
                j++;
            }
        }
    }
    return ans;
}

#endif /* COUNT_TRIPLETS_SUM_SMALLER_VALUE_H_ */
