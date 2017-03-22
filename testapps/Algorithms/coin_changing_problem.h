#ifndef COIN_CHANGING_PROBLEM_H_
#define COIN_CHANGING_PROBLEM_H_

int count(const unsigned* arr, unsigned size, unsigned goal)
{
	unsigned int pos = 0;
	unsigned int count= 0;

	while(pos < size)
	{
		int remain = goal - arr[pos];

		if (remain >= 0)
		{
			++count;
		}
		else
		{
			++pos;
			continue;
		}

		if ((unsigned)remain < arr[pos])
		{
			++pos;
		}

		goal = remain;
	}

	return count;
}

int calculateMinNumberCoins(const unsigned* arr, unsigned size, unsigned goal)
{
	unsigned minCount = 0xFFFFFFFF;

	for(unsigned int i=0; i< size; ++i)
	{
		unsigned int numCoins = count(arr + i, size - i, goal);

		if (numCoins < minCount)
		{
			minCount = numCoins;
		}
	}

	return minCount;
}

int count2(const std::vector<int>& coins, int num)
{
  if (num == 0)
  {
    return 0;
  }

  int best = std::numeric_limits<int>::max();

  for (int c : coins)
  {
    if (num - c >= 0)
    {
      int curr = count2(coins, num - c) + 1;
      best = std::min(curr, best);
    }
  }

  return best;
}



#endif
