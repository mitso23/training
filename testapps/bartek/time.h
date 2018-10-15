/*
 * time.h
 *
 *  Created on: 3 Sep 2018
 *      Author: mitso23
 */

#ifndef TIME_H_
#define TIME_H_

#include <stdint.h>

const unsigned SECONDS_MINUTE = 60;
const unsigned SECONDS_HOUR = 60 * SECONDS_MINUTE;
const unsigned SECONDS_DAY = 24 * SECONDS_HOUR;
const unsigned SECONDS_YEAR = SECONDS_DAY * 365;

void PrintDateFromSecondsSinceEpoch(uint32_t secondsSinceEpoch)
{

}

#endif /* TIME_H_ */
