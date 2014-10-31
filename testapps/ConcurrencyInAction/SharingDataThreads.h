#ifndef SHARINGDATATHREADS_H_
#define SHARINGDATATHREADS_H_

#include<algorithm>
#include<mutex>
#include<list>
#include<stack>
#include<memory>
#include<string.h>

std::list<int> some_list;
std::mutex some_mutex;
std::stack<int> s;


void add_to_list(int new_value)
{
	std::lock_guard<std::mutex> guard(some_mutex);
	some_list.push_back(new_value);
}

bool list_contains(int value_to_find)
{
	std::lock_guard<std::mutex> guard(some_mutex);
	return std::find(some_list.begin(), some_list.end(), value_to_find)
			!= some_list.end();
}

void stackCheck()
{
	if (!s.empty())
	{
		//We are copying the value returned from top and then removing it from the stack
		//NOTE: If pop was supposed to return a value and then removing it, the copy could through an exception so the popped value will be lost
		//in this case value= s.pop();
		int const value = s.top();
		s.pop();

		if (value)
		{

		}
	}
}

//NAIVE IMPLEMENTATION OF STACK WITH RE-ALLOCATION
template<typename T>
class my_stack
{
public:
	my_stack() :
			m_writeIndex(0), m_readIndex(0)
	{
		m_capacity = 2;
		m_ptr = new T(m_capacity);
	}

	bool empty()
	{
		return m_writeIndex;
	}

	T& top()
	{
		return m_ptr[m_readIndex];
	}

	void push(T& newValue)
	{
		if (m_writeIndex >= m_capacity)
		{
			m_capacity *= 2;
			T* temp = new T[m_capacity];
			memcpy(temp, m_ptr, m_writeIndex * sizeof(T));

			delete[] m_ptr;
			m_ptr = temp;
		}

		m_readIndex = m_writeIndex;
		m_ptr[m_writeIndex++] = newValue;

	}

	void pop()
	{
		m_writeIndex--;
	}

	T& topPop()
	{
		T& value = m_ptr[m_readIndex];
		m_writeIndex--;
		m_readIndex--;

		//If exception is thrown here we are fucked as the value is already popped
		//a statement like that could fail x= pop();
		return value;
	}

private:
	size_t m_capacity;
	T* m_ptr;
	size_t m_writeIndex;
	size_t m_readIndex;
};

//THREAD SAFE STACK WITH POP RETURNING VALUE
template<typename T>
class threadsafe_stack
{
	threadsafe_stack()
	{

	}

	threadsafe_stack(const threadsafe_stack& stack)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_data = stack.m_data;
	}

	threadsafe_stack& operator=(const threadsafe_stack& stack) = delete;

	void push(T newValue)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_data.push(newValue);

	}

	void pop(T& value)
	{
		if (empty())
		{
			return;
		}

		std::lock_guard<std::mutex> lock(m_mutex);
		value = m_data.top();
		m_data.pop();

	}

	std::shared_ptr<T> pop()
	{
		if (empty())
		{
			throw 1;
		}

		std::lock_guard<std::mutex> lock(m_mutex);
		std::shared_ptr < T > res(std::make_shared < T > (m_data.top()));
		m_data.pop();
		return res;
	}

	bool empty() const
	{
		return m_data.empty();
	}

private:
	std::stack<T> m_data;
	std::recursive_mutex m_mutex;

};

//USE LOCK FOR LOCKING TWO MUTEXES AT THE SAME TIME AND SAME ORDER
#if 0
class some_big_object;
void swap(some_big_object& lhs,some_big_object& rhs);
class X
{
private:
	some_big_object some_detail;
	std::mutex m;
public:
	X(some_big_object const& sd) :
	some_detail(sd)
	{
	}

	friend void swap(X& lhs, X& rhs)
	{
		if (&lhs == &rhs)
		return;

		//
		std::lock(lhs.m, rhs.m);
		std::lock_guard<std::mutex> lock_a(lhs.m, std::adopt_lock);
		std::lock_guard<std::mutex> lock_b(rhs.m, std::adopt_lock);

		swap(lhs.some_detail, rhs.some_detail);
	}
};

class X
{
private:
	some_big_object some_detail;
	std::mutex m;
public:
	X(some_big_object const& sd):some_detail(sd)
	{}

	friend void swap(X& lhs, X& rhs) l
	{
		if(&lhs==&rhs)
		return;

		//DO NOT Lock the mutex
		std::unique_lock<std::mutex> lock_a(lhs.m,std::defer_lock);
		std::unique_lock<std::mutex> lock_b(rhs.m,std::defer_lock);

		//LOCK the mutex here
		std::lock(lock_a,lock_b);

		swap(lhs.some_detail,rhs.some_detail);

	}
};

#endif

//PATTERN TO AVOID DEADLOCK (DETECT MUTEX ORDER LOCKING DURING RUN TIME)
class hierarchical_mutex
{
public:
	hierarchical_mutex(unsigned long value) :
			m_previous_hierarchy_value(0), m_hierarchy_value(value)
	{

	}

	void lock()
	{
		check_for_hierarchy_violation();
		m_mutex.lock();
		update_hierarchy_value();
	}

	void unlock()
	{
		this_thread_hierarchy_value = m_previous_hierarchy_value;
		m_mutex.unlock();

	}

private:
	void check_for_hierarchy_violation()
	{
		if (m_hierarchy_value > this_thread_hierarchy_value)
		{
			throw std::logic_error("Potential dead lock");
		}
	}

	void update_hierarchy_value()
	{
		m_previous_hierarchy_value = this_thread_hierarchy_value;
		this_thread_hierarchy_value = m_hierarchy_value;
	}

private:
	static /*thread_local*/unsigned long this_thread_hierarchy_value;

	unsigned long m_previous_hierarchy_value;
	const unsigned long m_hierarchy_value;
	std::mutex m_mutex;
};

unsigned long hierarchical_mutex::this_thread_hierarchy_value = 0x0FFFFFFF;

hierarchical_mutex high_level_mutex(10000);
hierarchical_mutex low_level_mutex(5000);

int do_low_level_stuff()
{
	return 0;
}

int low_level_func()
{

	std::lock_guard<hierarchical_mutex> lk(low_level_mutex);
	return do_low_level_stuff();
}

void high_level_stuff(int some_param)
{

}

void high_level_func()
{

	std::lock_guard<hierarchical_mutex> lk(high_level_mutex);
	high_level_stuff(low_level_func());

}

void thread_a()
{
	high_level_func();
}

hierarchical_mutex other_mutex(100);
void do_other_stuff()
{

}

void other_stuff()
{

	high_level_func();
	do_other_stuff();
}

void thread_b()
{
	std::lock_guard<hierarchical_mutex> lk(other_mutex);
	other_stuff();
}

std::unique_lock<std::mutex> getLock()
{
	std::mutex mutex;
	std::unique_lock<std::mutex> lock(mutex);
	//do some stuff
	//move the ownership back to the application
	return lock;
}

//INIT MUTEX
std::shared_ptr<int> someResource;
std::once_flag onceFlag;   /** USEFUL FOR INITIALISATION IN MULTITHREADED APPLICATIONS **/

class HAL
{

private:
	void getDriver()
	{

	}

	static void initialize()
	{
		m_hal= new HAL();
	}

	static const HAL& getInstance()
	{

		//NOTE: This makes it thread safe during early initialization
		std::call_once(onceFlag, initialize);

		return *m_hal;
	}

	static HAL* m_hal;
};

#if 0
//READ-WRITE MUTEX
class dns_entry
{

};

class dns_cache
{
	std::map<std::string, dns_entry> entries;
	mutable boost::shared_mutex entry_mutex;

public:
	dns_entry find_entry(std::string const& domain) const
	{
		boost::shared_lock<boost::shared_mutex> lk(entry_mutex);
		std::map<std::string, dns_entry>::const_iterator const it =
				entries.find(domain);
		return (it == entries.end()) ? dns_entry() : it->second;
	}

	void update_or_add_entry(std::string const& domain,
			dns_entry const& dns_details)
	{
		std::lock_guard<boost::shared_mutex> lk(entry_mutex);
		entries[domain] = dns_details;
	}
};
#endif


#endif /* SHARINGDATATHREADS_H_ */
