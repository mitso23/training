/*
 * sum_digits.h
 *
 *  Created on: 18 Apr 2017
 *      Author: mitso23
 */

#ifndef SUM_DIGITS_H_
#define SUM_DIGITS_H_


unsigned sum_digits(unsigned long long int n)
{
	return n <= 9 ? n : sum_digits(n/10) + n%10;
}

unsigned sum_digits_unti_sum_one_digit(unsigned long long int n)
{
	unsigned long long int sum = n;
	while(sum > 9)
	{
		sum = sum_digits(sum);
	}

	return sum;
}

#endif /* SUM_DIGITS_H_ */
