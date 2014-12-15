#ifndef RANDOM_GENERATOR_H_
#define RANDOM_GENERATOR_H_
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

class RandomGenerator
{
public:
	RandomGenerator(int range) : m_range(range)
	{

	}

	int generate()
	{
		srand(time(NULL));
		return rand() % m_range;
	}

private:
	int m_range;


};



#endif /* RANDOM_GENERATOR_H_ */
