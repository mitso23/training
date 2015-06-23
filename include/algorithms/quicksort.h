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

	std::cout << "pivot pos: " << pivotPos <<  " pivot value " << vec[pivotPos] <<  " start: " << start << " end: " << end << std::endl << std::endl;;
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

	return pivotPos;
}
class SortData
{

public:
	SortData() : m_vec(nullptr), m_start(0), m_end(0)
	{

	}

	SortData(std::vector<int>* vec, int start, int end) : m_vec(vec), m_start(start), m_end(end)
	{

	}

public:
	std::vector<int>* m_vec;
	unsigned m_start;
	unsigned m_end;
};

FineGrainLockQueue<SortData> queue;


void quickSort(std::vector<int>& vec, unsigned start, unsigned end, std::vector<scoped_thread>* threads= nullptr)
{
	if (start < end)
	{
		auto pivot= partition(vec, start, end);

		if (pivot != 0)
		{
			//queue.push(SortData(&vec, start, pivot - 1));
			std::thread t { quickSort, std::ref(vec), start, pivot - 1, nullptr, };
			threads->push_back(scoped_thread(std::move(t)));
			//quickSort(vec, start, pivot - 1);
		}

		if (pivot != end)
		{
			std::thread t { quickSort, std::ref(vec), pivot + 1, end, nullptr};
			threads->push_back(scoped_thread(std::move(t)));
			//queue.push(SortData(&vec, pivot + 1, end));
			//quickSort(vec, pivot + 1, end);
		}
	}
	else
	{
		return;
	}
}

void quickSortWrapper1(std::vector<int>& vec, unsigned start, unsigned end)
{
	std::vector<scoped_thread> threads;
	quickSort(vec, start, end, &threads);
	std::cout << "done:" << std::endl;
}


void quickSortWrapper(std::vector<int>& vec, unsigned start, unsigned end)
{
	std::thread t{quickSort, std::ref(vec), start, end, nullptr};

	while(1)
	{
		SortData data;
		queue.wait_pop(data);

		std::thread t{quickSort, std::ref(*data.m_vec), data.m_start, data.m_end, nullptr };
	}
}

#endif
