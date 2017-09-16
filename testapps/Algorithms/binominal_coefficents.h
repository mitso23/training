#ifndef BINOMINAL_COEFFICENTS_H_
#define BINOMINAL_COEFFICENTS_H_

#include <algorithm>

int binom_cache[100][100] = { 0 };

unsigned long long binomialCoeff(int n, int k)
{
	if (k == 0 || k == n)
	{
		return 1;
	}

	if (binom_cache[n][k] != 0)
	{
		return binom_cache[n][k];
	}

	int res = binomialCoeff(n-1, k-1) + binomialCoeff(n-1, k);
	binom_cache[n][k] = res;
}

unsigned Ctable[100][100] = { 0 };

unsigned long long binomialCoeffBottomUp(unsigned int n, unsigned int k)
{
	for(unsigned int i=0; i<=n; ++i)
	{
		for(unsigned int j=0; j<= std::min(i, k); ++j)
		{
			if (j == 0 || j == n)
			{
				Ctable[i][j] = 1;
			}
			else
			{
				Ctable[i][j] = Ctable[i-1][j-1] + Ctable[i-1][j];
			}
		}
	}

	return Ctable[n][k];
}

#endif /* BINOMINAL_COEFFICENTS_H_ */
