#ifndef LAMBDAS_H_
#define LAMBDAS_H_

#include <vector>
#include <algorithm>

class TestLambdas
{

public:

void test1()
{
	//NOTE: we need to capture this in order to be able to access the m_filter
	// &m_filter will not work
	auto l = [=](int x)
	{
		return x < m_filter;
	};

	auto it = std::find_if(m_v.begin(), m_v.end(), l);

	std::cout << "data: " << *it << std::endl;
}

private:
	int m_filter = 3;
	std::vector<int> m_v = { 1, 2, 3, 4 };
};


void test2()
{
	std::vector<int> data = { 1, 2, 3};

	auto l = [](const std::vector<int>& data)
	{
		std::cout << data[0] << std::endl;
	};

	auto f = std::bind(l, std::move(data));
	f();

	std::cout << "vector size is: " << data.size();
}

void test3(Noisy&& ns)
{

}

#endif /* LAMBDAS_H_ */
