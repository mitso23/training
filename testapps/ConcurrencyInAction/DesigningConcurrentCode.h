#ifndef DESIGNINGCONCURRENTCONDE_H
#define DESIGNINGCONCURRENTCONDE_H

#include <containers/thread_safe_queue.h>
#include <utils/utils.h>

class Sorter
{

public:
	typedef struct _chunk_to_sort
	{
		_chunk_to_sort()
		{

		}

		_chunk_to_sort(std::list<int>& data) : m_data(data)
		{

		}

		_chunk_to_sort(_chunk_to_sort&& rhs)
		{
			m_data= std::move(rhs.m_data);
			m_promise= std::move(rhs.m_promise);
		}

		std::list<int> m_data;
		std::promise<std::list<int>> m_promise;
		std::vector<std::thread> m_threads;

	}chunk_to_sort;

	void do_sort(std::list<int>& input)
	{
		//Find the partition element and remove it from the list
		std::list<int> partitionList;
		partitionList.splice(partitionList.begin(), input, input.begin());
		auto partition= *partitionList.begin();

		auto divide_point= std::partition(input.begin(), input.end(), [partition](int value) {return value < partition;});

		//get the left
		std::list<int> left;
		left.splice(left.end(), input, input.begin(), divide_point);
		left.splice(left.end(), partitionList);

		//get the right
		std::list<int> right;
		right.splice(right.end(), input);



		print_cont(left);
		print_cont(right);
	}

private:
	FineGrainLockQueue<chunk_to_sort> m_chunks;
};


#endif
