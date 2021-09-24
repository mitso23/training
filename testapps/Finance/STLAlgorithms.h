#pragma once

#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <bitset>

template <typename C>
void PrintCont(C&& c)
{
	for (const auto& item : c)
	{
		std::cout << item << " ";
	}

	std::cout << std::endl;
}

void RunAlgorithms()
{
	{
		std::vector<int> v = { 1, 2, 3 };

		auto l = [](decltype(v)::value_type x)
		{
		  if (x > 20)
		  {
			  return true;
		  }
		  else
		  {
			  return false;
		  }
		};

		std::cout << "v: " << std::any_of(v.begin(), v.end(), l) << std::endl;
	}

	std::vector<int> v1 = {1, 2, 3, 4};
	std::list<int> l2 = {3, 4};

	std::vector<int> output;
	{
		std::set_difference(v1.begin(), v1.end(), l2.begin(), l2.end(), std::back_inserter(output));
	}

	std::string x("   hello   ");
	x.erase(std::remove_if(x.begin(), x.end(), [](char c) { if (c == ' ') return true; return false; }), x.end());
	std::cout << x << std::endl;

	// {1 2 3}, {1,2} {1,3}, {1} {2}, {3}
	std::vector<int> permutation = {1, 2, 3};
	for(int i=0; i< 8; ++i)
	{
		std::bitset<3> b(i);
		for(size_t pos = 0; pos < 3; ++pos)
		{
			if (b.test(pos))
			{
				std::cout << permutation[pos];
			}
		}

		std::cout << std::endl;


	}

	//PrintCont(output);
}
