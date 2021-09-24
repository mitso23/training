#include "Primitives.h"
#include "Numerics.h"
#include "STLAlgorithms.h"
#include "Threading.h"

#include <vector>
#include <array>
#include <algorithm>
#include <functional>
#include <future>
#include <parallel/algorithm>
#include <parallel/numeric>


using namespace std;

struct Foo
{
	Foo(int&& x, int&& y)
	{
		std::cout << "rvalue ref" << std::endl;
	}

	Foo(int& x, int& y)
	{
		std::cout << "simple ref" << std::endl;
	}

	void Compute()
	{
		std::cout << "Computing" << std::endl;
	}
};

template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init)
{
	unsigned long const length = std::distance(first, last);
	unsigned long const max_chunk_size = 1024*4;
	if (length <= max_chunk_size)
	{
		return std::accumulate(first, last, init);
	}
	else
	{
		Iterator mid_point = first;
		std::advance(mid_point, length / 2);
		std::future<T> first_half_result =
			std::async(parallel_accumulate<Iterator, T>,
				first, mid_point, init);
		T second_half_result = parallel_accumulate(mid_point, last, T());
		return first_half_result.get() + second_half_result;
	}

}

int main(int argc, char* argv[])
{
#if 0
	SP<int> p;

	SP<int> s(new int(), Deleter<int>());
	std::cout << sizeof(p) << std::endl;

	SP<int> s2(new int(), [](int* ){std::cout << "deleting another resource" << std::endl;});
	std::cout << *s2 << std::endl;

	std::vector<SP<int>> sps;
	sps.emplace_back(s);
	sps.emplace_back(s2);

	TestBind t;
	std::function<void(int, int)> f1 = std::bind(&TestBind::foo, &t, std::placeholders::_1, std::placeholders::_2);
	f1(1, 2);
	std::function<void(int)> f2 = std::bind(&TestBind::foo, &t, std::placeholders::_1, 10);
	f2(3);

	auto f3 = [&t](int arg)
	{
		t.foo(arg, 10);
	};

	f3(5);
#endif

#if 0
	MockStrategy* mockStrategy{new MockStrategy};
	SP<PayOffStrategy<MockStrategy>> strategy{mockStrategy};

	EXPECT_CALL(*mockStrategy, payoff(_)).Times(1);
	std::cout << strategy->payoff(120) << std::endl;

	double K1 = 100;
	double K2 = 200;

	MockFunction<double (double)> mockFunction;
	PayOffStrategy2 s2(mockFunction.AsStdFunction());
	EXPECT_CALL(mockFunction, Call(300)).WillOnce(Return(200));

	PayOffStrategy2 s{[&K1, &K2](double S) { return S - K1 - K2;}};
	std::cout << s2.payoff(300) << std::endl;
#endif

#if 0
	double x = 3.5 + 0.000001;
	double y = x + 0.5;
	if (x == 3.5)
	{
		std::cout << "yes: " << std::endl;
	}
	else
	{
		std::cout << "no: " << std::endl;
	}

	CeilingFloorTrunc(-3.7);

	double d = 0.1;
	FloatingPointManipulation(d);
	FloatingPointExtra(d);
	std::cout << "calculate epsilon: " << computeEpsilon() << std::endl;
#endif

#if 0
	RunAlgorithms();
#endif

#if 0
	generateData();

	using FutureType = std::result_of<decltype(&SortElements)(decltype(ll[0]))>::type;
	std::vector<std::future<FutureType>> results;

	for(auto i = 0; i< ll.size(); ++i)
	{
		results.push_back(std::async(std::launch::async, SortElements, std::ref(ll[i])));
	}

	for(auto& fut : results)
	{
		fut.wait();
	}

	auto merged = MergeElements();
#endif

	//std::cout << parallelCompute() << std::endl;
	auto n = std::chrono::high_resolution_clock::now();
	std::vector<char> vv(512 * 1024, 1);
	auto e = std::chrono::high_resolution_clock::now();
	std::cout << "memory allocated: " << std::chrono::duration_cast<std::chrono::microseconds>(e - n).count() << std::endl;
#if 0
	{
		auto now = std::chrono::high_resolution_clock::now();
		auto res = parallelAccumulate(vv.begin(), vv.end());
		auto end = std::chrono::high_resolution_clock::now();
		std::cout << "duration (dimitrios parallel):" << std::chrono::duration_cast<std::chrono::microseconds>(end - now).count() << " res: "
				  << res << std::endl;
	}
#endif

#if 0
	{
		auto now = std::chrono::high_resolution_clock::now();
		auto res = __gnu_parallel::accumulate(vv.begin(), vv.end(), 0);
		auto end = std::chrono::high_resolution_clock::now();
		std::cout << "gnu accumulate parallel: " << std::chrono::duration_cast<std::chrono::microseconds>(end - now).count() << " res: "
				  << res << std::endl;

	}

	{
		auto now = std::chrono::high_resolution_clock::now();
		auto res = std::accumulate(vv.begin(), vv.end(), 0);
		auto end = std::chrono::high_resolution_clock::now();
		std::cout << "std::accumulate: " << std::chrono::duration_cast<std::chrono::microseconds>(end - now).count() << " res: "
				  << res << std::endl;

	}
#endif

#if 0
	{
		auto now = std::chrono::high_resolution_clock::now();
		auto res = parallel_accumulate(vv.begin(), vv.end(), 0);
		auto end = std::chrono::high_resolution_clock::now();
		std::cout << "recursive accumulate: "
				  << std::chrono::duration_cast<std::chrono::microseconds>(end - now).count() << " res: "
				  << res << std::endl;
	}

	{
		auto now = std::chrono::high_resolution_clock::now();
		auto numThreads = 4; //std::thread::hardware_concurrency();
		std::cout << "number of threads: " << numThreads << std::endl;
		ThreadPool pool {numThreads};
		auto l = [](auto begin, auto end)
		{
		  	return std::accumulate(begin, end, 0);
		};

		std::vector<std::future<int>> futures;
		auto d = std::distance(vv.begin(), vv.end());
		auto next = vv.begin();
		auto begin = vv.begin();
		std::advance(next, d / numThreads);

		for (unsigned int i = 0; i < numThreads -1; ++i)
		{
			auto task = pool.PushTask(l, begin, next);
			futures.push_back(std::move(task));
			begin = next;
			std::advance(next, d / numThreads);
		}

		auto finalR = std::accumulate(begin, next, 0);

		int sum = 0;
		for (auto& f : futures)
		{
			std::cout << "waiting for the future: " << std::endl;
			sum += f.get();
			std::cout << "partial result: " << sum << std::endl;
		}

		sum+= finalR;

		auto end = std::chrono::high_resolution_clock::now();

		std::cout << "thread pool " << std::chrono::duration_cast<std::chrono::microseconds>(end - now).count() << " res: "
				  << sum << std::endl;
	}
#endif

	Monitor<string> str{"Hello"};
	auto i = 1;

	auto l = [i](std::string& s)
	{
		s+= std::to_string(i);
	};

	auto p = [](std::string& s)
	{
		std::cout << s << std::endl;
	};

	str(l);
	str(p);

	int x = 1;
	Monitor<Foo> f{x, x};
	f([](Foo& f){f.Compute();});
}


