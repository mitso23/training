/*
 * num_ways_to_reach_stairs.h
 *
 *  Created on: 20 May 2017
 *      Author: mitso23
 */

#ifndef NUM_WAYS_TO_REACH_STAIRS_H_
#define NUM_WAYS_TO_REACH_STAIRS_H_
#include <map>

std::map<int, int> cache;

unsigned long long stepDynamicProg(int dst)
{
	if (dst < 0)
	{
		return 0;
	}
	else if (dst == 0)
	{

		return 1;
	}
	else if (cache.find(dst) != cache.end())
	{
		return cache[dst];
	}
	else
	{
		unsigned long long result = stepDynamicProg(dst - 1) + stepDynamicProg(dst - 2) + stepDynamicProg(dst - 3);
		cache[dst] = result;

		return result;
	}

}

unsigned long long stepNaive(int dst)
{
	//std::cout << dst << std::endl;
	if (dst == 0)
	{
		return 1;
	}
	else if (cache.find(dst) != cache.end())
	{
		return cache[dst];
	}

	unsigned long long count = 0;
	for(unsigned int i=1; i<= 3; ++i)
	{
		if (dst - i >= 0)
		{
			count+= stepNaive(dst - i);
			cache[dst] = count;
		}
	}

	return count;
}


#endif /* NUM_WAYS_TO_REACH_STAIRS_H_ */
