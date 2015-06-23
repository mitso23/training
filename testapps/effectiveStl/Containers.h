#ifndef CONTAINERS_H_
#define CONTAINERS_H_

#include <vector>
#include <iostream>
#include <utils/utils.h>
#include <set>

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

void remove_if_example()
{
	std::vector<int> vec = { 1, 2, 3, 1, 5, 6 };
	auto funct= [](int item) {	return item < 3;};

	print_cont(vec);
	vec.erase(remove_if(vec.begin(), vec.end(), funct), vec.end());
	print_cont(vec);
}

//ASSOCIATIVE CONTAINERS:
// Two values are equal if x == y
// Two values are equivalent if ! (x<y) && !(x>y)
// Prefer to use the member functions of the containers like find e.g set.find("persephone") would succeed while find(set.begin()...) would fail

#endif /* CONTAINERS_H_ */
