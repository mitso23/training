#ifndef SYNCHRONIZATION_H_
#define SYNCHRONIZATION_H_

#include <algorithm>
#include <mutex>
#include <list>
#include <deque>
#include <stack>
#include <vector>
#include <memory>
#include <string.h>
#include <queue>
#include <future>
#include <utility>
#include <thread>
#include <boost/function.hpp>
#include <ostream>

//USE OF CONDITIONAL VARIABLE IN THERADS

std::mutex mut;
std::queue<unsigned> data_queue;
std::condition_variable data_cond;
const unsigned numElements= 10;

void data_preparation_thread()
{

	for (unsigned int i = 0; i < numElements; usleep(100), ++i)
	{
		//NOTE: The lock guard has ownership of the mutex, you can't lock it manually
		std::lock_guard<std::mutex> lk(mut);
		data_queue.push(i);

		//NOTIFY ONLY IF THE MUTEX IS UNLOCKED AS THE SIGNAL MIGHT BE LOST
		data_cond.notify_one();

		std::cout << "pushing element " << i << std::endl;
	}

}

void data_processing_thread()
{
	while (true)
	{

		//NOTE: The unique lock has normal lock,unlock methods
		std::unique_lock<std::mutex> lk(mut);
		auto funct= []{ return !data_queue.empty(); };

		data_cond.wait(lk, funct);


		auto data = data_queue.front();
		data_queue.pop();

		lk.unlock();

		//process the data
		usleep(50);
		std::cout << "data is: " << data << std::endl;

		if (data == (numElements - 1))
		{
			break;
		}
	}
}

//Usage of FUTURE in multithreading applications
int find_the_answer_to_ltuae()
{
	for(int i=0; i< 10; i++)
	{
		std::cout << "Calculating" << std::endl;
		usleep(1000);
	}

	return 10;
}

void workerThread()
{
	std::future<int> the_answer=std::async(std::launch::async, find_the_answer_to_ltuae);
	std::cout << "worker thread doing something" << std::endl;
	sleep(1);
	std::cout << "worker thread finished doing something" << std::endl;

	std::cout << "The answer is " << the_answer.get() << std::endl;


}

struct X
{
	int operator()(int a , int b)
	{
		return a+b;
	}

    void foo(int,std::string const&)
    {

    }

    std::string bar(std::string const&)
    {
    	return std::string();
    }
};

void workerThread2()
{
	{
		std::future<int> the_answer=std::async(std::launch::async, X(), 1, 1); // X object will be moved and not copied
	}

	{
		X x;
		auto f1 = std::async(&X::foo, &x, 42, "hello");  	//calls foo(42, hello)
		auto f2 = std::async(&X::bar, x, "goodbye");		//calls bar("goodbye") using a copy of x
	}
}

//Usage of packaged tasks that combine thread and future

#if 0
template<>
class packaged_task<std::string(std::vector<char>*,int)>
{
public:
    template<typename Callable>
    explicit packaged_task(Callable&& f);
    std::future<std::string> get_future();
    void operator()(std::vector<char>*,int);
};
#endif

std::mutex m;
std::deque<std::packaged_task<int(void)>> tasks;


void guiThread()
{

	while(1)
	{
		std::unique_lock<std::mutex> lock(m);
		auto funct= []{ return !tasks.empty(); };
		data_cond.wait(lock, funct);

		auto task= std::move(tasks.front());
		tasks.pop_front();

		std::cout << "GUI Thread executing a task" << std::endl;
		lock.unlock();
		task();
	}
}



template<typename Callable>
std::future<int> postGUIThread(Callable f)
{
	std::packaged_task<int(void)> task(f);
	std::future<int> res= task.get_future();

	std::lock_guard<std::mutex> lock(m);
	tasks.push_back(std::move(task));

	std::cout << "Posting to GUI Thread" << std::endl;

	data_cond.notify_one();

	return res;
}

//Usage of a promise fututre combiniton used for exchanging data
std::promise<std::string> promise;

void setPromise()
{
	sleep(1);
	promise.set_value("Promise Thread");
}

void getFuture()
{
	std::shared_future<std::string> future(promise.get_future().share());

	std::cout << "Future value is " << future.get();
}

void waitForFuture()
{
	std::future<int> f = std::async(find_the_answer_to_ltuae);

	if (f.wait_for(std::chrono::milliseconds(35)) == std::future_status::ready)
	{
		f.get();
	}
}

template<typename T>
void split(const std::list<T>& current, std::vector<std::list<T>>& vec)
{
	T pivot= *current.begin();

	std::list<T> left;
	left.resize(current.size() / 2);
	std::list<T> right;
	right.resize(current.size() / 2);
	bool leftChanged= false;
	bool rightChanged= false;

	for (auto it = current.begin(); it != current.end(); ++it)
	{
		if (*it <= pivot)
		{
			left.push_back(*it);
			leftChanged= true;
		}
		else
		{
			right.push_back(*it);
			rightChanged= true;
		}
	}

	if(!leftChanged && !rightChanged)
	{
		return;
	}

	if (leftChanged)
	{
		vec.push_back(left);
	}

	if (rightChanged)
	{
		vec.push_back(right);
	}

	split(left, vec);

	split(right, vec);
}

template<typename T>
std::list<T> sequential_quick_sort(std::list<T> input)
{
	if(input.empty())
	{
		return std::list<T>();
	}

	std::vector<std::list<T>> vec;

	split(input, vec);
}


#endif /* SYNCHRONIZATION_H_ */
