/*
 * TypeDeduction.h
 *
 *  Created on: 21 Nov 2016
 *      Author: mitso23
 */

#ifndef TYPEDEDUCTION_H_
#define TYPEDEDUCTION_H_

//While auto strips off all the specifiers
//decltype gives you the full type of an object
template<typename Container, typename Index>
auto getValue(Container c, Index i) -> decltype(c[i])
{
	decltype(c[i]) y = c[i];
	return y;
}


#endif /* TYPEDEDUCTION_H_ */
