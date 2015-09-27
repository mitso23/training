#ifndef PROGRAMMINGSTL_H
#define PROGRAMMINGSTL_H

#include <iostream>
#include <functional>
#include <iterator>
#include <string>
#include <algorithm>
#include <deque>
#include <list>
#include <set>

//NOTE: Prefer member functions with the same name as the algorithms

void efficientStringAddition()
{

	{
		std::string hello("Hello");
		std::string world("World");
		hello.reserve(hello.size() + world.size());
		std::copy(world.begin(), world.end(), std::back_inserter(hello));
		print_cont(hello);
	}
}

void assignTest()
{
	std::list<int> list;
	std::vector<int> vect= { 1, 2 ,3 };
	list.assign(vect.begin(), vect.end());
	vect.assign(list.begin(), list.end());
	print_cont(list);
	print_cont(vect);
}

void readArrayAddsDequeue()
{
	//This is how a C programmer will do
	{
		int a[5]=	{ 1, 2, 3, 4, 5 };
		std::deque<int> deq;

		for (int i = 0; i < 5; ++i)
		{
			deq.push_back(a[i] + 41);
		}

		//print_cont(deq);
	}

	//This is how an average STL user will do
	{
		int a[5]={ 1, 2, 3, 4, 5 };
		std::deque<int> deq;
		auto it = deq.begin();

		for (int i = 0; i < 5; ++i)
		{
			it = deq.insert(it, a[i] + 41);
			++it;
		}

		//print_cont(deq);
	}

	//This is what an advance STL user will do
	{
		int a[5]= { 1, 2, 3, 4, 5 };
		std::deque<int> deq;

		std::transform(a, a + sizeof(a)/sizeof(a[0]), std::back_inserter(deq), boost::bind(std::plus<int>(), _1, 41));
		print_cont(deq);

	}
}

void findSet()
{
	std::multiset<int> s = { 1 ,2 ,3 ,3 , 4 , 3 , 8 , 9 , 10 };
	print_cont(s);

	//this will use logarithmic time to find an element + it uses equality to determine if two items are the same
	s.find(3);

	//this will take linear time to find smth in the container (DO NOT USE THIS) + it uses equivalence to determine if two items are the same
	std::find(s.begin(), s.end(), 3);

	//this will print the first key equal to 3 or the first greater value than 3 or end()
	std::cout<< *s.lower_bound(3) << std::endl;
	//this will print the first key greater than 3 or end
	std::cout << *s.upper_bound(3) << std::endl;
	auto range= s.equal_range(3);

	for(auto it=range.first; it != range.second; ++it)
	{
		std::cout << "value is " << *it << std::endl;
	}

}

void testNoisyMov(Noisy&& ns)
{
	if (ns.getId() >= 0)
	{
		std::cout << ns << std::endl;
	}

	ns.setData(1);
}

void keepListSorted()
{
	//std::list<Noisy> list= { Noisy(), Noisy(), Noisy() };
	std::list<Noisy> list;
	list.push_front(std::move(Noisy()));
	list.push_front(std::move(Noisy()));
	list.push_front(std::move(Noisy()));
	std::cout << "before sorting: " << std::endl;
	list.sort();
	std::cout << "after sorting: " << std::endl;
	auto tmp= std::move(Noisy());
	auto pos= std::upper_bound(list.begin(), list.end(), tmp);
	list.insert(pos, std::move(tmp));
	print_cont(list);
}

#endif /* PROGRAMMINGSTL_H_ */
