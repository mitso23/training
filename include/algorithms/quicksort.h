#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <utils/utils.h>

#include <vector>
#include <algorithm>
#include <iostream>
#include <thread>
#include <containers/thread_safe_queue.h>

unsigned int calcPivot(unsigned start, unsigned end)
{
	return (start + end)/ 2 ;
}

// 1, 2, 9, 8, 5, 7, 13, 20, 4, 5 , 9, 3
// 1, 2, 9, 8, 5, 3, 13, 20, 4, 5 , 9, 7
// 1, 2, 9, 8, 5, 3, 13, 20, 4, 5 , 7, 9

unsigned  partition(std::vector<int>& vec, unsigned start, unsigned end)
{
	unsigned pivotPos= calcPivot(start, end);
	std::swap(vec[end], vec[pivotPos]);
	pivotPos= end;

	//std::cout << "pivot pos: " << pivotPos <<  " pivot value " << vec[pivotPos] <<  " start: " << start << " end: " << end << std::endl << std::endl;;
	//print_cont(vec);
	//usleep(1000 * 1000 * 2);

	for (unsigned i = start; i < pivotPos;)
	{
		if (vec[i] > vec[pivotPos] && (i + 1) != pivotPos)
		{
			std::swap(vec[pivotPos], vec[pivotPos - 1]);
			std::swap(vec[i], vec[pivotPos]);
			pivotPos= pivotPos - 1;
		}
		else if (vec[i] > vec[pivotPos] && (i + 1) == pivotPos)
		{
			std::swap(vec[i], vec[pivotPos]);
			pivotPos= pivotPos - 1;
		}
		else
		{
			++i;
		}
	}

	//std::cout << "partition finished " << start << " " << end << " id: " << std::this_thread::get_id() << std::endl;
	return pivotPos;
}

//Original vector:
    //0 1 2 3 4 5 6 7 8 9
//Partitioned vector:
    //0 8 2 6 4  *  5 3 7 1 9
template<class BidirIt, class UnaryPredicate>
BidirIt partition2(BidirIt first, BidirIt last, UnaryPredicate p)
{

}

int numThreads= 0;
const int maxNumberThreads= 4;
void quickSort(std::vector<int>& vec, unsigned start, unsigned end)
{
	std::thread t;
	if (start < end)
	{
		auto pivot= partition(vec, start, end);

		if (pivot != 0)
		{
			if (numThreads < maxNumberThreads)
			{
				t= std::thread(quickSort, std::ref(vec), start, pivot - 1);
				++numThreads;
				std::cout << "Creating a new thread num: " << numThreads  << "id: " << t.get_id() << std::endl;
			}
			else
			{
				//std::cout << "Not Creating a new thread " << std::endl;
				quickSort(vec, start, pivot - 1);
			}
		}

		if (pivot != end)
		{
			//std::cout << "Main thread " << std::endl;
			quickSort(vec, pivot + 1, end);
		}

		if (t.joinable())
		{
			//std::cout << "Waiting for thread num: " << t.get_id() << std::endl;
			t.join();
			std::cout << "Stopping a new thread num: " << numThreads << std::endl;
			--numThreads;

		}
	}
	else
	{
		if (t.joinable())
		{
			//std::cout << "waiting for the thread to stop " << std::endl;
			t.join();
			--numThreads;
			std::cout << "thread has stopped" << std::endl;
		}

		return;
	}
}


#endif
