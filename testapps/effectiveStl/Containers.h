#ifndef CONTAINERS_H_
#define CONTAINERS_H_

#include <vector>
#include <iostream>
#include <utils/utils.h>
#include <utils/Noisy.h>
#include <set>
#include <map>

using namespace std;

//NOTE: Use vector reserve to reserve memory before adding items to the vector

// NOTE: String size may vary from implementation to implementation, bare minimum is size, capacity, allocator and pointer to data
// Some implementation will just have a pointer to a struct
// Some strings are ref counted (multi threaded implications ??)
// Some strings may not support per object allocators

template <typename _Tp>
class CustomAllocator
{
public:
     typedef size_t     size_type;
     typedef ptrdiff_t  difference_type;
     typedef _Tp*       pointer;
     typedef const _Tp* const_pointer;
     typedef _Tp&       reference;
     typedef const _Tp& const_reference;
     typedef _Tp        value_type;

	pointer allocate(size_type numObjects, const void *localityHint = 0)
	{
		return static_cast<pointer>(operator new(numObjects * sizeof(_Tp)));
	}

	void deallocate(pointer ptrToMemory, size_type numObjects)
	{
		//operator delete ptrToMemory;
	}
};

struct stringComparisonLess : public binary_function<std::string, std::string, bool>
{
	bool operator() (const std::string& lhs, const std::string& rhs) const
	{
		auto it2= rhs.begin();
		for (auto it= lhs.begin(); it != lhs.end(); ++it)
		{
			int diff= *it - *it2;
			if (abs(diff) == 32 || abs(diff) == 0)
			{
				++it2;
				continue;
			}
			else if (diff > 0)
			{
				std::cout << "Greater" << std::endl;
				return false;
			}
			else if (diff < 0)
			{
				std::cout << "Less" << std::endl;
				return true;
			}
		}

		std::cout << "Equal" << std::endl;
		return false;
	}
};

void setComparatorTest()
{
	std::set<std::string, stringComparisonLess> set;
	set.insert("Hello");
	set.insert("HELLO");
	set.insert("Bloom");
	set.insert("A");
	set.insert("W");

#if 0
	if (less(x,y))
	{
		// x is smaller than y
	}
	else if (less(y, x))
	{
		// x is greater than y
	}
	else
	{
		// x and y are equivalent
	}


#endif
	std::cout << "size of set is " << set.size() << std::endl;
	print_cont(set);
}

void reduceExtraCapacity()
{
	//lets assume the x capacity is 8 and we want to reduce it to 4
	std::vector<int> x= { 1, 2 ,3 , 4 };

	std::vector<int>(x).swap(x);
}

void vectorOfBools()
{
	std::vector<bool> vec;
	vec.push_back(true);

	//That will not compile
	//bool* bl= &vec[0];
}

void sortedVector()
{
	std::vector<int> vec= { 1, 8, 10, 25, 3, 3 , 5, 6};
	std::sort(vec.begin(), vec.end());
	print_cont(vec);

	if (std::binary_search(vec.begin(), vec.end(), 10))
	{
		std::cout << "Success" << std::endl;
	}
	else
	{
		std::cout << "Fail " << std::endl;
	}

	//The equal_range and lower_bound will take advantage that the vector is sorted
	//which means that it is going to be quicker than std::find
	auto range= std::equal_range(vec.begin(), vec.end(), 3);
	std::copy(range.first, range.second, ostream_iterator<int>(cout, " "));
}

struct DereferencePointerToObject
{
	template <typename T>
	const T& operator()(const T* type)
	{
		return *type;
	}
};

void setOfPointers()
{
	std::set<string*> set;
	set.insert(new string("Hello World"));
	set.insert(new string("Good bye "));

	std::transform(set.begin(), set.end(), ostream_iterator<string>(cout, ":"), DereferencePointerToObject());
}

void manual_remove_example()
{
	std::vector<int> vec = { 1, 2, 3, 1, 5, 6 };

	auto first= vec.begin();
	print_cont(vec);

	for (auto it=first; it!= vec.end(); ++it)
	{
		if (*it >= 3)
		{
			*first++= *it;
		}
	}

	print_cont(vec);
}

void modifyElementAssociativeContainer()
{
	std::set<int> s= { 1 , 2 , 3 };
	print_cont(s);
	auto valueIt= s.find(2);
	//Increment value in order to get the next valid iterator
	// this will be used as a hit to as where to insert it.
	s.erase(valueIt++);
	std::cout << "value is " << *valueIt << std::endl;
	s.insert(valueIt, 15);
	print_cont(s);
}

void remove_if_example()
{
	//The remove will put all the items at the end of the container
	// 1 2 3 1 5 6
	// 3 5 6 1 5 6
	// 3 5 6
	std::vector<int> vec = { 1, 2, 3, 1, 5, 6 };
	auto funct= [](int item) {	return item < 3;};

	print_cont(vec);
	auto it= remove_if(vec.begin(), vec.end(), funct);
	print_cont(vec);
	vec.erase(it, vec.end());
	print_cont(vec);
}

void mapUpperLowerBounds()
{
	// 1 2 3 5 8
	std::map<int, int> m = { std::pair<int,int>(1,1), std::pair<int,int>(2,2) ,std::pair<int,int>(5,5) ,std::pair<int,int>(8,8) , std::pair<int,int>(3,3) };

	// lower bound return items >=5
	// upper bound returs items >5
	// equal_range(lower_bound, upper_bound)  1 2 3 5 5 5 8 will return 5 5 5 (make sense only for multu maps)
	auto it= m.lower_bound(5);
	auto it2= m.upper_bound(5);

	m.insert(it, std::pair<int,int>(6, 6));
	for(auto it=m.begin(); it != m.end(); ++it)
	{
		std::cout << "key:" << it->first << " value: " << it->second << std::endl;
	}

	std::cout << "lower bound " << it->second << std::endl;
	std::cout << "upper bound " << it2->second << std::endl;
}

void mapOperators()
{
	std::map<int, Noisy> m;
	//Map will first check if key 0 exists, if yes then it will update it if not it will DEFAULT CONSTRUCT AN OBJECT
	//RETURN A REFERENCE TO IT and then it will update the value
	//m[0]= Noisy();

	//Lookup via the operator[] is very dangerous as if the object is not present the map will default construct one and return
	// a reference to it
	if (m[0] == Noisy())
	{
		std::cout << "upi" << std::endl;
	}
	else
	{
		std::cout << "SHIT" << std::endl;
	}

	auto pair= m.insert(std::pair<int, Noisy>(1, Noisy()));
	if (pair.second)
	{
		std::cout << "Success" << std::endl;
	}

}

//ASSOCIATIVE CONTAINERS:
// Two values are equal if x == y
// Two values are equivalent if ! (x<y) && !(x>y)
// NOTE: Never use for associative containers the operator <= or >= always use < or > notion, equal values are not equivalent
// Prefer to use the member functions of the containers like find e.g set.find("persephone") would succeed while find(set.begin()...) would fail

#endif /* CONTAINERS_H_ */
