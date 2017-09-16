#ifndef WARMHOLE_CONTEST_H_
#define WARMHOLE_CONTEST_H_

#include <vector>
#include <algorithm>
#include <ostream>
#include <iterator>
#include <functional>

struct ContestDuration
{
	ContestDuration(unsigned int start, unsigned int end) : startTime(start), endTime(end)
	{

	}

	unsigned int startTime;
	unsigned int endTime;

	friend bool operator < (const ContestDuration& rhs, const ContestDuration& lhs)
	{
		if (rhs.startTime < lhs.startTime)
		{
			return true;
		}
		else if (rhs.startTime == lhs.startTime)
		{
			return rhs.endTime < lhs.endTime;
		}

		return false;
	}

	friend std::ostream& operator << (std::ostream& os, const ContestDuration& duration)
	{
		return os << "start: " << duration.startTime << " end: " << duration.endTime;
	}
};

template<class ForwardIt, typename T>
ForwardIt my_upper_bound(ForwardIt start, ForwardIt end, T value)
{
	typename std::iterator_traits<ForwardIt>::difference_type len = std::distance(start, end);
	if (len <=0)
		return end;

	ForwardIt mid = start;
	std::advance(mid, len/2);

	if (*mid >=value)
	{
		while(*(mid - 1)>=value)
		{
			if (mid != start)
				--mid;
		}

		return mid;
	}
	else
	{
		std::advance(mid, +1);
		my_upper_bound(mid, end, value);
	}

}

template<class ForwardIt, typename T>
ForwardIt my_lower_bound(ForwardIt start, ForwardIt end, T value)
{
	typename std::iterator_traits<ForwardIt>::difference_type len = std::distance(start, end);
	if (len <=0)
		return end;

	ForwardIt mid = start;
	std::advance(mid, len/2);

	if (*mid <=value)
	{
		while(*(mid + 1)<=value)
		{
			std::cout << "mid: " << *mid << std::endl;
			if (mid != end)
				++mid;
		}

		return mid;

	}
	else
	{
		std::advance(mid, -1);
		my_lower_bound(start, mid, value);
	}

}

template<class ForwardIt, typename T>
ForwardIt lower_bound(ForwardIt start, ForwardIt end, T value)
{
	typename std::iterator_traits<ForwardIt>::difference_type len = std::distance(start, end);
	ForwardIt result = end;

	while (len >= 0)
	{
		auto mid = start + len/2;
		//std::cout << "start: " << *start << " mid: " << *mid << " end: " << *end << " len: " << len << std::endl ;

		if (*mid >=value)
		{
			result = mid;
			end = mid - 1;
		}
		else
		{
			start = mid + 1;

		}

		len = std::distance(start, end);
	}

	return result;
}

template<class ForwardIt>
ForwardIt remove_duplicates(ForwardIt begin, ForwardIt end)
{
	ForwardIt nextReplaceLocation = end;
	for(auto it = begin + 1; it != end; ++it)
	{
		if (*it == *(it - 1))
		{
			if (nextReplaceLocation == end)
			{
				nextReplaceLocation = it;
			}
		}
		else if (*it != *(it - 1))
		{
			if (nextReplaceLocation != end)
			{
				*nextReplaceLocation = *it;
				++nextReplaceLocation;
			}
		}
	}

	return nextReplaceLocation;
}

template<class ForwardIt, typename T>
ForwardIt upper_bound(ForwardIt start, ForwardIt end, T value)
{
	typename std::iterator_traits<ForwardIt>::difference_type len = std::distance(start, end);
	ForwardIt result = end;

	while (len >= 0)
	{
		auto mid = start + len/2;
		std::cout << "start: " << *start << " mid: " << *mid << " end: " << *end << " len: " << len << std::endl ;

		if (*mid > value)
		{
			result = mid;
			end = mid - 1;
		}
		else
		{
			start = mid + 1;

		}

		len = std::distance(start, end);
	}

	return result;
}


std::vector<unsigned int> VWarmhole = {4, 14, 25, 2};
std::vector<unsigned int> WWarmhole = { 13, 21 };
std::vector<ContestDuration> Contest = { ContestDuration(15,21), ContestDuration(5,10), ContestDuration(7, 25), ContestDuration(7, 26)} ;
unsigned int minDuration = std::numeric_limits<unsigned int>::max();

unsigned int shortestDuration()
{
	std::sort(VWarmhole.begin(), VWarmhole.end());
	std::sort(WWarmhole.begin(), WWarmhole.end());
	std::sort(Contest.begin(), Contest.end());

	for(auto it= Contest.begin(); it != Contest.end(); ++it)
	{
		std::cout << *it << std::endl;
		using namespace std::placeholders;  // for _1, _2, _3...

		auto minVIt = my_lower_bound(VWarmhole.begin(), VWarmhole.end(), it->startTime);
		if (minVIt == VWarmhole.end())
		{
			continue;
		}

		auto maxVIt = my_upper_bound(WWarmhole.begin(), WWarmhole.end(), it->endTime);

		if (maxVIt == WWarmhole.end())
		{
			continue;
		}

		std::cout << "minVIt: " << *minVIt << std::endl;
		std::cout << "maxVIt: " << *maxVIt << std::endl;

	}

	return minDuration;
}

#endif /* WARMHOLE_CONTEST_H_ */
