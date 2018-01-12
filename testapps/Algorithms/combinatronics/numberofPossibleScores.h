/*
 * numberofPossibleScores.h
 *
 *  Created on: 18 Jul 2017
 *      Author: mitso23
 */

#ifndef NUMBEROFPOSSIBLESCORES_H_
#define NUMBEROFPOSSIBLESCORES_H_

unsigned int bufferScores[100*100];
unsigned int cachedScores[100*100];

// N:1  (2)
// N:2  (3) 5
// N:3  (5) 7 8 10

// [2] [3] 5 [5] 7 8 10
unsigned calculatePossibilities(unsigned int N, unsigned int* arr)
{
	memset(bufferScores, 0, sizeof(bufferScores));
	unsigned int currentCachedScoredIndex = 0;
	unsigned int count = 0;

	for(unsigned int i=0; i<N; ++i)
	{
		//std::cout << "arr[" << i << "] " << arr[i] << std::endl;

		unsigned numeElementsCache = currentCachedScoredIndex;

		for(unsigned int j=0; j< numeElementsCache; ++j)
		{
			unsigned int newValue = cachedScores[j] + arr[i];
			//std::cout << " new value is: " << newValue << " index: " << currentCachedScoredIndex << std::endl;

			if (bufferScores[newValue] == 0)
			{
				cachedScores[currentCachedScoredIndex++] = newValue;
				bufferScores[newValue] = newValue;
				++count;

				std::cout << "adding to map: " << newValue << " count: " << count << std::endl;
			}
		}

		if (bufferScores[arr[i]] == 0)
		{
			//Add this value to the cache
			cachedScores[currentCachedScoredIndex++] = arr[i];
			//Add it to the map
			bufferScores[arr[i]] = arr[i];
			++count;

			std::cout << "adding to map: " << arr[i] << " count: " << count << std::endl;
		}
	}

	return count;
}


#endif /* NUMBEROFPOSSIBLESCORES_H_ */
