/*
 * power_number.h
 *
 *  Created on: 16 Sep 2017
 *      Author: mitso23
 */

#ifndef POWER_NUMBER_H_
#define POWER_NUMBER_H_


unsigned power(unsigned x, unsigned y)
{
	return (y == 1) ?  x : power(x*x, y>>1);
}


#endif /* POWER_NUMBER_H_ */
