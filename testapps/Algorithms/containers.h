#ifndef CONTAINERS_H_
#define CONTAINERS_H_

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

// 1 8 3 4 5 6
// 4 5 6 X X X X
template<typename InputIterator, typename Predicate>
void my_remove_if(InputIterator start, InputIterator stop, Predicate predicate)
{
	auto it= start;
	InputIterator substitute= it;

	for(; it != stop; ++it)
	{
		if (!predicate(*it))
		{
			*substitute= *it;
			++substitute;
		}

	}
}


#endif /* CONTAINERS_H_ */
