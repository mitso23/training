#ifndef ALGORITHMS_H_
#define ALGORITHMS_H_
#include <algorithm>
#include <vector>
#include <set>
#include "DesignPatterns.h"

template<class T, template<typename> class C>
void print(C<T>& c)
{
	std::copy(c.begin(), c.end(), std::ostream_iterator<T>(cout, " "));
}

int generator()
{
	static int count= 0;
	return count++;
}

void fillExample()
{
	std::vector<int> vec;
	std::fill(vec.begin(), vec.end(), 0);
}

void countExample()
{
	std::vector<int> vec;

	std::set<int> se(vec.begin(), vec.end());
	print(vec);

}

#endif /* ALGORITHMS_H_ */
