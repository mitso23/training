/*
 * find_path_magic_triangle.h
 *
 *  Created on: 23 Jul 2017
 *      Author: mitso23
 */

#ifndef FIND_PATH_MAGIC_TRIANGLE_H_
#define FIND_PATH_MAGIC_TRIANGLE_H_

unsigned int visitedNumber[1000];

void GetRange(unsigned int level, unsigned& startRange, unsigned& endRange)
{
	unsigned int count = 1;
	unsigned begin = 1;

	for(unsigned int i=1; i< level; ++i)
	{
		begin+=count++;
	}

	startRange = begin;
	endRange = startRange + level - 1;
}

unsigned int minSteps = 0xFFFFFFFF;
#include <deque>

std::deque<int> d;

bool NumberSteps(unsigned int end, unsigned int current, unsigned int level, unsigned int& steps)
{
	//std::cout << "end: " << end << " current: " << current << " level: " << level << " steps: " << steps << std::endl;
	d.push_back(current);
	visitedNumber[current] = true;

	if (current == end)
	{
		if (steps < minSteps)
		{
			minSteps = steps;
		}

#if 1
		for(const auto& item : d)
			std::cout << item << " ";
		std::cout << std::endl;
#endif
		d.pop_back();
		visitedNumber[current] = false;
		return true;
	}
	else if (current > end)
	{
		d.pop_back();
		visitedNumber[current] = false;
		return false;
	}

	unsigned int startRange = 0;
	unsigned int endRange = 0;

	GetRange(level, startRange, endRange);

	//std::cout << "start: " << startRange << " end: " << endRange << std::endl;

	if (current < startRange || current > endRange)
	{
		d.pop_back();
		visitedNumber[current] = false;
		return false;
	}

	if (end >= startRange && end <= endRange)
	{
		//Go left
		if (current + 1 <= endRange && !visitedNumber[current + 1])
		{
			++steps;
			NumberSteps(end, current + 1, level, steps);
			--steps;
		}

		//Go right
		if (current >= startRange + 1 && !visitedNumber[current - 1])
		{
			++steps;
			NumberSteps(end, current - 1, level, steps);
			--steps;
		}
	}

	// Go down right
	{
		unsigned offset = current - startRange;
		unsigned int startRange = 0;
		unsigned int endRange = 0;

		GetRange(level + 1, startRange, endRange);

		++steps;
		NumberSteps(end, startRange + offset, level + 1, steps);
		--steps;
	}

	// Go down left
	{
		unsigned offset = current - startRange;
		unsigned int startRange = 0;
		unsigned int endRange = 0;

		GetRange(level + 1, startRange, endRange);

		++steps;
		NumberSteps(end, startRange + offset + 1, level + 1, steps);
		--steps;
	}

	d.pop_back();
	visitedNumber[current] = false;
}

#endif /* FIND_PATH_MAGIC_TRIANGLE_H_ */
