#ifndef UTILS_H_
#define UTILS_H_

#include <iterator>
#include <iostream>
#include <algorithm>

// Template-template argument must
// be a class; cannot use typename:
template<typename C>
void print_cont(const C& c)
{
	for(auto& item: c)
		std::cout << item << " ";

	std::cout << std::endl;
}
#endif /* UTIL&S_H_ */
