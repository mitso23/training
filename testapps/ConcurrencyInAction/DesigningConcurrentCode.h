#ifndef DESIGNINGCONCURRENTCONDE_H
#define DESIGNINGCONCURRENTCONDE_H

#include <containers/thread_safe_queue.h>
#include <utils/utils.h>
#include <mutex>


#if 0
class Sorter
{

public:
	typedef struct _chunk_to_sort
	{
		_chunk_to_sort()
		{

		}

		_chunk_to_sort(std::list<int> data) : m_data(std::move(data))
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

	}chunk_to_sort;

	//The fact that this is a list complicates things
	void do_sort(std::list<int>& input)
	{
		if (input.empty())
		{
			return;
		}

		//this will have the result in the end
		std::list<int> result;
		result.splice(result.begin(), input, input.begin());

		//Find the partition element
		auto partition= *result.begin();

		auto divide_point= std::partition(input.begin(), input.end(), [partition](int value) {return value < partition;});

		//get the left
		std::list<int> left;
		left.splice(left.end(), input, input.begin(), divide_point);

		//get the right
		std::list<int> right;
		right.splice(right.end(), input);
		chunk_to_sort right_chunk(std::move(right));

		if (m_threads.size() < 4)
		{
			m_threads.push_back(std::thread(std::bind(&Sorter::sort_thread,this)));
		}

		//We need a way of checking if we have finished
		do_sort(left);

		while (right_chunk.promise.get_future().wait_for(std::chrono::seconds(1))
						!= std::future_status::ready)
		{

		}

		print_cont(left);
		print_cont(right);
	}

	void sort_thread()
	{
		chunk_to_sort chunk;
		m_chunks.wait_pop(chunk);

	}

private:
	FineGrainLockQueue<chunk_to_sort> m_chunks;
	std::vector<std::thread> m_threads;
};

#endif

std::atomic<unsigned int> counter;

// The counter now will be populated in each threads cache
// which means that every time the value gets modified we will get a CPU stall until all the caches get updated
void processData()
{
	volatile unsigned x= 0;
	//The atomic variable serialises threads at a processor level
	while (counter.fetch_add(1, std::memory_order_relaxed) < 10000000)
	{
		for(int i=0; i< 10000; ++i)
		{
			for(int j=0; j< 10000; ++j)
			{
				x+= j+i;
			}
		}
		break;
	}
}

std::mutex _mutex;

void processData2()
{
	unsigned x = 0;
	unsigned temp= 0;

	//The lock serialises a thread at an operating system level
	//std::unique_lock<std::mutex> lock(_mutex);

	while (temp++ < 10000000)
	{
		//lock.unlock();

		for (int i = 0; i < 10000; ++i)
		{
			for (int j = 0; j < 10000; ++j)
			{
				x += j + i;
			}
		}

		break;
	}
}

// 1 2 3  			1 1 1 			14 6 6
// 3 4 6    * 		2 1 1   = 		29 13 13
// 7 8 9			3 1 1			50 24 24
void calculateSingleRow(unsigned int j, unsigned int k,
		const std::vector<std::vector<int> >& matrix1,
		const std::vector<std::vector<int> >& matrix2,
		std::vector<std::vector<int> >& result)
{
	for (auto i = 0U; i < matrix1.size(); ++i)
	{
		result[j][k] += (matrix1[j][i] * matrix2[i][k]);
	}

}


struct MatrixThreadData
{
	MatrixThreadData(std::reference_wrapper<const std::vector<std::vector<int>>> matrix1, std::reference_wrapper<const std::vector<std::vector<int>>> matrix2,
			std::reference_wrapper<std::vector<std::vector<int>>> result, unsigned int row1, unsigned int column2) : m_matrix1(matrix1), m_matrix2(matrix2), m_result(result),
			m_row1(row1),
			m_column2(column2)

	{

	}
	std::reference_wrapper<const std::vector<std::vector<int>>> m_matrix1;
	std::reference_wrapper<const std::vector<std::vector<int>>> m_matrix2;
	std::reference_wrapper<std::vector<std::vector<int>>> m_result;
	unsigned int m_row1;
	unsigned int m_column2;

};

FineGrainLockQueue<MatrixThreadData>* threadQueue;

void matrixMultiplication(const std::vector<std::vector<int> >& matrix1, const std::vector<std::vector<int> >& matrix2,
		std::vector<std::vector<int> >& result)
{
	std::vector<scoped_thread> threads;

	std::cout << "address of result is " << &result << std::endl;

	for(auto j= 0U; j< matrix1.size(); ++j)
	{
		for(auto k=0U; k< matrix2.size(); ++k)
		{
			if (threads.size() < 4)
			{
				threads.push_back(scoped_thread(std::thread(calculateSingleRow, j, k, std::ref(matrix1), std::ref(matrix2), std::ref(result))));
			}
			else
			{
				calculateSingleRow(j, k, matrix1, matrix2, result);
			}
		}
	}
}

// 1 2 3  			1 1 1 			14 6 6
// 3 4 6    * 		2 1 1   = 		29 13 13
// 7 8 9			3 1 1			50 24 24
void calculateSingleRowThread()
{
	while(1)
	{
		MatrixThreadData* data = static_cast<MatrixThreadData*> (operator new(
				sizeof(MatrixThreadData)));
		threadQueue->wait_pop(*data);

		const std::vector<std::vector<int>>& matrix1 = data->m_matrix1;
		const std::vector<std::vector<int>>& matrix2 = data->m_matrix2;
		std::vector<std::vector<int>>& result = data->m_result;

		for (auto i = 0U; i < matrix1.size(); ++i)
		{
			result[data->m_row1][data->m_column2] += (matrix1[data->m_row1][i]
					* matrix2[i][data->m_column2]);

		}

		delete data;
	}
}

void matrixMultiplication2(const std::vector<std::vector<int> >& matrix1, const std::vector<std::vector<int> >& matrix2,
		std::vector<std::vector<int> >& result)
{
	std::vector<scoped_thread> threads;
	threads.push_back(scoped_thread(std::thread(calculateSingleRowThread)));

	threadQueue= new FineGrainLockQueue<MatrixThreadData>(std::ref(matrix1), std::ref(matrix2), std::ref(result), 0, 0);

	for(auto j= 0U; j< matrix1.size(); ++j)
	{
		for(auto k=0U; k< matrix2.size(); ++k)
		{
			threadQueue->push(MatrixThreadData(std::ref(matrix1), std::ref(matrix2), std::ref(result), j, k));
		}
	}

	//How do we wait here trying to figure out when the data is finished
}


#endif
