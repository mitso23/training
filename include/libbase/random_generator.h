#ifndef RANDOM_GENERATOR_H_
#define RANDOM_GENERATOR_H_
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <sys/time.h>

class RandomGenerator
{
public:
	RandomGenerator(int range) : m_range(range)
	{

	}

	int generate()
	{
		timespec ts;
		clock_gettime(CLOCK_REALTIME, &ts); // Works on Linux
		srand(ts.tv_nsec);

		return rand() % m_range;
	}

private:
	int m_range;


};



#endif /* RANDOM_GENERATOR_H_ */
