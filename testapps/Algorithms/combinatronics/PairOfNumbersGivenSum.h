/*
 * PairOfNumbersGivenSum.h
 *
 *  Created on: 16 Sep 2017
 *      Author: mitso23
 */

#ifndef PAIROFNUMBERSGIVENSUM_H_
#define PAIROFNUMBERSGIVENSUM_H_

#include <vector>

void pairOfNumbersSumToGivenN(std::vector<unsigned>& v, unsigned int sum)
{
	std::sort(v.begin(), v.end());

	for(auto start= v.begin(), end=v.end(); start < end;)
	{
		if (*start + *end == sum)
		{
			std::cout << *start << " : " << *end << std::endl;
			++start;
			--end;
		}
		else if (*start + *end > sum)
		{
			--end;
		}
		else
		{
			++start;
		}
	}
}



#endif /* PAIROFNUMBERSGIVENSUM_H_ */
