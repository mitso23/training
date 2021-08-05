#include "Primitives.h"
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

int main(int argc, char* argv[])
{
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
}


