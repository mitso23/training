/*
 * TypeDeduction.h
 *
 *  Created on: 21 Nov 2016
 *      Author: mitso23
 */

#ifndef TYPEDEDUCTION_H_
#define TYPEDEDUCTION_H_

#include <unordered_map>
#include <string>

//While auto strips off all the specifiers
//decltype gives you the full type of an object
template<typename Container, typename Index>
auto getValue(Container c, Index i) -> decltype(c[i])
{
	decltype(c[i]) y = c[i];
	return y;
}

void iterateOverUnorderMap()
{
	std::unordered_map<std::string, Noisy> m;
	m["Hello"] = 1;

	//if we omit const then we will get a copy of the object even if we do it by reference as the key needs to be const
	for(std::pair<const std::string, Noisy>& p : m)
	{
		std::cout << p.first << std::endl;
	}

	for(auto& p : m)
	{
		std::cout << p.first << std::endl;
	}
}

void AutoToProxyClass()
{
	std::vector<bool> v2 = { true, false, false};

	auto value= static_cast<bool>(v2[0]);

	std::cout << value << std::endl;
}

#endif /* TYPEDEDUCTION_H_ */
