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

#endif /* LAMBDAS_H_ */
