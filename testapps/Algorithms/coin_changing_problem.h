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
      int res = count2(coins, num - c);
      int curr = res;
      if (res != std::numeric_limits<int>::max())
      {
    	  ++curr;
      }

      best = std::min(curr, best);

    }
  }

  return best;
}


int count3(const std::vector<int>& coins, int num)
{
	std::vector<std::vector<int>> table;
	table.resize(coins.size());

	for (data : table)
	{
		data.resize(num);
		std::fill(data.begin(), data.end(), 0);
	}

	for (int startPos = 0; startPos < coins.size(); ++startPos)
	{
		for(int sum=1; sum<= num; ++sum)
		{
			// If current coin is larger than the sum try solution from the previous row
			if (coins[startPos] > sum && (startPos - 1 >= 0))
			{
				table[startPos][sum - 1] = table[startPos - 1][sum - 1];
			}
			else
			{
				// We have exact match, use it
				if (sum % coins[startPos] == 0)
				{
					table[startPos][sum - 1] = sum / coins[startPos];
				}
				else
				{
					// Sum is larger than the coin
					if ((startPos - 1 >= 0))
					{
						int remain = sum - coins[startPos];
						int count = std::numeric_limits<int>::max();
						int i = 0;

						while(remain > 0)
						{
							++i;

							if (table[startPos - 1][remain - 1] != 0)
							{
								count = std::min(count, table[startPos - 1][remain - 1] + i);
							}

							remain = remain - coins[startPos];
						}

						//If we didn't find anything better use the previous result
						table[startPos][sum - 1] = (count == std::numeric_limits<int>::max()) ? table[startPos - 1][sum - 1] : count;
					}
				}

			}
		}
	}

	//go through the last column and get the best choice
	int best = std::numeric_limits<int>::max();

	for (int startPos = 0; startPos < coins.size(); ++startPos)
	{
		best = std::min(table[startPos][num - 1], best);
	}

#if 1
	for (data : table)
	{
		print_cont(data);
	}
#endif

	return best;
}



#endif
