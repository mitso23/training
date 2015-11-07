#ifndef UTILS_H_
#define UTILS_H_

#include <iterator>
#include <iostream>
#include <algorithm>
#include <bitset>
#include <iomanip>

// Template-template argument must
// be a class; cannot use typename:
template<typename C>
void print_cont(const C& c)
{
	for(auto& item: c)
		std::cout << item << " ";

	std::cout << std::endl;
}

template <typename T>
void dumpValue(T x)
{
	//std::cout.setf(std::ios_base::hex, std::ios_base::basefield);
	//std::cout << x << std::endl;

	std::cout << std::hex << "hex: " << (unsigned)x << std::endl;
	std::cout << "bit: " << std::bitset<sizeof(x)*8>(x) << std::endl;
}
#endif /* UTIL&S_H_ */
