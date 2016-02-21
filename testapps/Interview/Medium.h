#ifndef MEDIUM_H
#define MEDIUM_H

#include <utils/utils.h>
#include <memory>
#include <iterator>
#include <functional>
#include <boost/bind.hpp>
#include <utils/Noisy.h>
#include <iostream>
#include <mutex>
#include <memory>
#include <list>
#include <vector>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <functional>

template<typename T, typename Key, typename H>
class Hash
{
public:
	Hash(unsigned int size, H f) : h(f)
	{
		m_vector.resize(size);
	}

	void addItem(const T& data, const Key& key)
	{
		auto item= getBacket(key);

		if (item)
		{
			auto new_data= std::make_shared<T>(data);

			std::lock_guard < std::mutex > lock(item->m_mutex);
			item->m_list.push_back(new_data);
		}
		else
		{
			std::shared_ptr<Bucket> bucket= std::make_shared<Bucket>();

			bucket->m_list.push_back(std::make_shared<T>(data));
			addBacket(key, bucket);
		}
	}

	void printItems()
	{
		for(auto& item : m_vector)
		{
			for(auto& data : item->m_list)
			{
				if (data.get())
					std::cout << *data << std::endl;
			}
		}
	}

private:
	struct Bucket
	{
		std::mutex m_mutex;
		std::list<std::shared_ptr<T>> m_list;
	};

	std::mutex m_vectorMutex;
	std::vector<std::shared_ptr<Bucket>> m_vector;

private:
	std::shared_ptr<Bucket> getBacket(Key key)
	{
		std::lock_guard < std::mutex > lock(m_vectorMutex);
		return m_vector[h(key)];
	}

	void addBacket(Key key, std::shared_ptr<Bucket> bucket)
	{
		std::lock_guard < std::mutex > lock(m_vectorMutex);
		m_vector[h(key)]= bucket;
	}

	H h;
};

int hash(unsigned int key, unsigned int size)
{
	return key % size;
}

class Bb1
{
public:
	virtual void foo()
	{
		std::cout << "Bb1: foo has been called " << std::endl;
	}

	int* ptr;

	static int x;
};

class Bc1 : protected Bb1
{
public:
	void foo()
	{
		std::cout << "Bc1: foo has been called " << std::endl;
	}
};

class Suicide
{
public:

	Suicide() : m_i(0)
	{

	}

	void suicide()
	{
		delete this;
		std::cout << "MI IS " << m_i << std::endl;
	}

private:
	int m_i;
};

#include <iostream>
#include <list>
#include <vector>


/// Represents the duration of an order.
struct Order
{
    uint8_t startTime;
    uint8_t endTime;

    Order(uint8_t startTime_, uint8_t endTime_)
    : startTime(startTime_), endTime(endTime_)
    {}
};

/// Represents a bank with trading start and end times in UTC.
struct Bank
{
    std::string name;
    uint8_t tradingStart;
    uint8_t tradingEnd;

    Bank(const std::string& name_, uint8_t tradingStart_, uint8_t tradingEnd_)
    : name(name_), tradingStart(tradingStart_), tradingEnd(tradingEnd_)
    {}
};

// Prototypes implemented at the bottom of the file - you may assume
// that these are correct. Any other operator implementations beyond
// those found in the STL that you rely on will need to be provided by
// you as part of this exercise.
std::ostream& operator<<(std::ostream& os, const Bank& rhs);

struct ListComparator : public std::binary_function<Bank, Bank, bool>
{
	bool operator()(const Bank& rhs, const Bank& lhs) const
	{
		if (rhs.tradingStart < lhs.tradingStart)
		{
			return true;
		}
		else if (rhs.tradingStart == lhs.tradingStart)
		{
			return rhs.tradingEnd > lhs.tradingEnd;
		}
		else
		{
			return false;
		}
	}
};

template<typename C>
void print(C c)
{
	for(auto& item: c)
	{
		std::cout << item << std::endl;
	}
}

bool canTrade2(uint8_t startTime, uint8_t endTime, std::list<Bank>& banks)
{
	if (startTime >= endTime)
	{
		return true;
	}

	for(auto it=banks.begin(); it != banks.end();)
	{
		if (startTime > it->tradingStart)
		{
			it= banks.erase(it);
			return canTrade2(it->tradingEnd, endTime, banks);
		}
		else
		{
			++it;
		}
	}
}


bool canTrade(const Order& order, std::list<Bank>& banks)
{
	ListComparator cmp;
	banks.sort<ListComparator>(cmp);

	print(banks);

	return canTrade2(order.startTime, order.endTime, banks);
#if 0
    // Fill in your implementation here, but also feel free to create
    // other functions if you feel appropriate.

    bool isOpen[24];
    std::fill(isOpen, isOpen+24, false);

    for (auto bank : banks)
    {
    	std::cout << bank << std::endl;
        for (int h=bank.tradingStart;h<=bank.tradingEnd;h++)
            isOpen[h] = true;
    }

    for (int h=order.startTime;h<=order.endTime;h++)
        if (!isOpen[h])
            return false;

    return true;
#endif

#if 0
    for(auto& bank : banks)
    {
    	std::cout << "TRADE START TIME: " << order.startTime << " TRADE END TIME: " << order.endTime << std::endl;
    	std::cout << bank << std::endl;

    	if (order.startTime >= bank.tradingStart && order.endTime <= bank.tradingEnd)
    	{
    		return true;
    	}
    }
    return false;
#endif

}

// -------- Any bugs in the functions below are not intentional and not
// -------- part of the exercise.

/// Stream a bank to an output stream, for debugging.
std::ostream& operator<<(std::ostream& os, const Bank& rhs)
{
    os << static_cast<int>(rhs.tradingStart) << ":00" << "-" <<
        static_cast<int>(rhs.tradingEnd) << ":00" << " " <<
        rhs.name;
    return os;
}


class Bomb {
    int x;
public:
    Bomb() : x(0) {std::cout << "Constructor called " << std::endl;}

    //DO NOT THROW IN THE DESTRUCTOR
    ~Bomb() {  }

    void * operator new(size_t n) throw()
    {
        printf("operator new called\n");
        return malloc(n);
    }

    void operator delete(void *p) throw()
    {
        printf("operator delete called\n");
        if (p != 0) free(p);
    }
};

void f() throw(int)
{
    Bomb myBomb;

    Bomb *pBomb = new Bomb();
    try
    {
    	delete pBomb;
    } catch (...)
    {
        printf("caught exception\n");
    }

    throw "no boom";
}

void misUseOfDelete()
{
	char* data= new char[10];
	delete data;

	Suicide *d= new Suicide();
	d->suicide();
}

void throwException()
{
	throw 2;
}

void tesetProtectedInheritance()
{
	//protected inheritance prevents you from using multiple inheritance
	//Bb1* bb1= new Bc1();
}

void smartPointers()
{
	std::shared_ptr<int> p = std::make_shared<int>();
	p.reset(new int());

	std::weak_ptr<int> p3(p);

	std::unique_ptr<int> p2(new int());
}

bool compareTwoValues(int x, int y)
{
	return x < y;
}

void functorExample()
{
	std::vector<int> src= { 1, 3, 4, 5, 8, 9, 12, 24, 25, 40};
	std::vector<int> dst;

	std::copy(src.begin(), src.end(), std::back_inserter(src));
	auto new_end = std::remove_if(src.begin(), src.end(), boost::bind(compareTwoValues, _1, 20));
	src.erase(new_end, src.end());
	print_cont(src);
}

void downCastringTest()
{
	printf("%s\n", typeid(int***).name());
	Noisy* ptr;
	std::cout << typeid(ptr).name() << std::endl;
}

template<typename T>
class RefObject
{
	RefObject(T* pointer) : m_pointer(pointer), m_counter(1)
	{

	}

private:
	T* m_pointer;
	uint32_t m_counter;
};


#endif /* MEDIUM_H_ */
