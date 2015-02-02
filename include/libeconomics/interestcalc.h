#ifndef INTERESTCALC_H_
#define INTERESTCALC_H_

#include <stddef.h>
#include <iostream>
#include <math.h>

size_t calculateNumYearsUntilRepaiment(size_t money, float interest, size_t yearlyRepayment)
{
	static size_t numYears= 0;

	if (yearlyRepayment > money)
	{
		return numYears;
	}
	else
	{
		size_t moneyOwned = (money - yearlyRepayment) * interest + (money
				- yearlyRepayment);

		++numYears;

		calculateNumYearsUntilRepaiment(moneyOwned, interest, yearlyRepayment);
	}

	return numYears;
}

size_t calculateSumWithInterest(size_t money, float interest, unsigned numberYears, size_t yearlyRepayment)
{
	static size_t sum= 0;

	if (--numberYears == 0 || yearlyRepayment > money)
	{
		sum= money;
		return sum;
	}
	else
	{
		size_t moneyOwned = (money - yearlyRepayment) * interest + (money
				- yearlyRepayment);

		calculateSumWithInterest(moneyOwned, interest, numberYears, yearlyRepayment);
	}

	return sum;
}

size_t caclulateYearlyRepaiments(size_t money, float interest, unsigned numYears)
{
	size_t yearlyRepayment= money / numYears;
	size_t totalInterest= calculateSumWithInterest(money, interest, numYears, yearlyRepayment);
	size_t yearlyInterestRepayment= totalInterest / numYears;

	return yearlyRepayment + yearlyInterestRepayment;

}

#endif /* INTERESTCALC_H_ */
