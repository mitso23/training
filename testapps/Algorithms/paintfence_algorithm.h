#ifndef PAINTFENCE_ALGORITHM_H_
#define PAINTFENCE_ALGORITHM_H_

//n=3 k=2
// k1 -> k1 -> k2
// k1 -> k2 -> k1
// k1 -> k2 -> k2
void printLevel(unsigned level)
{
	for(unsigned int i=0; i< level; ++i)
	{
		std::cout << "-";
	}
	std::cout << ">";
}
void countWays(int numColours, int colour, int numFences, int& sameColourCount, int level, long unsigned int& count)
{
	static bool firstTime = false;

	if (firstTime)
	{
		++sameColourCount;
		printLevel(level);

		std::cout << "colour " << colour << " n: " << numFences	<< " sameColourCount: " << sameColourCount << " level: "
		<< level << " count: " << count << std::endl;
	}

	firstTime = true;

	if (numFences == 0)
	{
		++count;
		if (sameColourCount)
			--sameColourCount;
		return;
	}

	if (sameColourCount < 2)
	{
		for(int i=0; i< numColours; ++i)
		{
			countWays(numColours, i, numFences - 1, sameColourCount, level + 1, count);
		}
	}
	else
	{
		sameColourCount = 0;
		for(int i=0; i< numColours - 1; ++i)
		{
			countWays(numColours, (colour + i + 1) % numColours, numFences - 1, sameColourCount, level + 1, count);
		}
	}

	if (sameColourCount)
		--sameColourCount;
}

// Returns count of ways to color k posts
// using k colors
long countWays2(int n, int k)
{
    // To store results for subproblems
    long dp[n + 1];
    memset(dp, 0, sizeof(dp));

    // There are k ways to color first post
    dp[1] = k;

    // There are 0 ways for single post to
    // violate (same color_ and k ways to
    // not violate (different color)
    int same = 0, diff = k;

    // Fill for 2 posts onwards
    for (int i = 2; i <= n; i++)
    {
        // Current same is same as previous diff
        same = diff;

        // We always have k-1 choices for next post
        diff = dp[i-1] * (k-1);

        // Total choices till i.
        dp[i] = (same + diff);
    }

    return dp[n];
}

long unsigned int countWays(int n, int k)
{
	long unsigned int diff[n + 1];
	memset(diff, 0, sizeof(diff));

	diff[1] = k;
	diff[2] = k * (k-1);

	if (n == 1)
	{
		return diff[1];
	}
	else if (n == 2)
	{
		return diff[2] + diff[1];
	}
	else
	{
		for(unsigned int i=3; i<= n; ++i)
		{
			diff[i] = (diff[i - 1] + diff[i - 2]) * (k - 1);
		}
	}

	return diff[n] + diff[n - 1];
}

#endif /* PAINTFENCE_ALGORITHM_H_ */
