#ifndef LOCKBASEDDESIGN_H_
#define LOCKBASEDDESIGN_H_

#include <exception>
#include <thread>
#include <stack>
#include <mutex>
#include <memory>
#include <condition_variable>
#include <queue>
#include <list>
#include <iostream>
#include <map>
#include <algorithm>
#include <libbase/rwlock.h>
#include <libbase/random_generator.h>
#include <boost/shared_ptr.hpp>

#include <containers/thread_safe_list.h>
#include <containers/thread_safe_hash.h>
#include <containers/thread_safe_queue.h>

struct empty_stack: std::exception
{
	const char* what() throw ()
	{
		return "stack is empty";
	}
};

template<typename T>
class thread_safe_stack
{

public:
	thread_safe_stack()
	{

	}

	thread_safe_stack(const thread_safe_stack& other)
	{
		std::lock_guard < std::mutex > lock(m_mutex);
		m_data = other.m_data;
	}

	thread_safe_stack& operator=(const thread_safe_stack& rhs) = delete;

	void push(T newValue)
	{
		std::lock_guard < std::mutex > lock(m_mutex);
		m_data.push(std::move(newValue));
	}

	boost::shared_ptr<T> pop()
	{
		std::lock_guard < std::mutex > lock(m_mutex);

		if (m_data.empty())
		{
			return boost::shared_ptr<T>();
		}

		boost::shared_ptr<T> res(new T(std::move(m_data.top())));

		m_data.pop();

		return res;
	}

private:
	std::stack<T> m_data;
	mutable std::mutex m_mutex;
};

template<typename T>
class Threadsafe_queue
{
public:
	void push(std::shared_ptr<T> value)
	{
		std::lock_guard < std::mutex > lock(m_mutex);
		m_data.push(value);
		//lock.unlock();
		m_condVar.notify_one();
	}

	std::shared_ptr<T> wait_pop()
	{
		std::unique_lock < std::mutex > lock(m_mutex);
		m_condVar.wait(lock, [this]
		{	return !m_data.empty();});
		auto value = m_data.front();
		m_data.pop();
		return value;
	}

	bool empty() const
	{
		std::lock_guard < std::mutex > lock(m_mutex);
		return m_data.empty();
	}

private:
	std::queue<std::shared_ptr<T>> m_data;
	mutable std::mutex m_mutex;
	std::condition_variable m_condVar;

};

void producer_thread();

void consumer_thread();

void hash_lookup_thread();

void hash_insert_thread();

#endif /* LOCKBASEDDESIGN_H_ */
