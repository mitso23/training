#ifndef LOCKBASEDDESIGN_H_
#define LOCKBASEDDESIGN_H_

#include <exception>
#include <thread>
#include <stack>
#include <mutex>
#include <memory>
#include <condition_variable>
#include <queue>
#include <iostream>



struct empty_stack : std::exception
{
	const char* what() throw()
	{
		return "stack is empty";
	}
};

template<typename T>
class thread_safe_stack
{

public:
	thread_safe_stack(const thread_safe_stack& other)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_data= other.m_data;
	}

	thread_safe_stack& operator=(const thread_safe_stack& rhs) = delete;

	void push(T newValue)
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		m_data.push(std::move(newValue));
	}

	std::shared_ptr<T> pop()
	{
		std::lock_guard < std::mutex > lock(m_mutex);

		if (m_data.empty())
			throw empty_stack();

		std::shared_ptr<T> const res(std::make_shared<T> (std::move(m_data.top())));

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
		std::lock_guard<std::mutex> lock(m_mutex);
		m_data.push(value);
		//lock.unlock();
		m_condVar.notify_one();
	}

	std::shared_ptr<T> wait_pop()
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		m_condVar.wait(lock, [this] { return !m_data.empty(); });
		auto value= m_data.front();
		m_data.pop();
		return value;
	}

	bool empty() const
	{
		std::lock_guard<std::mutex> lock(m_mutex);
		return m_data.empty();
	}

private:
	std::queue<std::shared_ptr<T>> m_data;
	mutable std::mutex m_mutex;
	std::condition_variable m_condVar;

};

void producer_thread();

void consumer_thread();

///NEXT_ITEM->TAIL->ITEM->ITEM->HEAD
template<typename T>
class FineGrainLockQueue
{
private:
	struct Node
	{
		T data;
		Node* next;
		std::mutex m_mutex;

		Node(T _data) : data(_data), next(NULL)
		{

		}
	};

	std::condition_variable m_condVar;
	Node* m_dummyNode;
	Node* m_head;
	Node* m_tail;

public:
	FineGrainLockQueue() : m_dummyNode(new Node(0)), m_head(m_dummyNode), m_tail(m_dummyNode)
	{

	}

	void push(const T& data)
	{
		Node* newNode= new Node(data);

		//First check if we are empty
		{
			std::unique_lock <std::mutex> lock(m_tail->m_mutex);

			if (m_tail == m_dummyNode)
			{
				m_head = newNode;
				m_head->next = NULL;

				m_tail = m_head;
				m_condVar.notify_one();
				return;
			}
		}

		std::unique_lock<std::mutex> lock2(m_tail->m_mutex);
		m_tail->next= newNode;
		m_tail=newNode;

		m_condVar.notify_one();
	}

	void wait_pop(T& data)
	{
		std::unique_lock<std::mutex> lock(m_tail->m_mutex);

		m_condVar.wait(lock, [this] { return m_tail != m_dummyNode; });

		data= m_head->data;
		delete m_head;

		if (m_head->next)
		{
			std::unique_lock<std::mutex> lock2(m_head->next->m_mutex);
			m_head= m_head->next;
		}

	}
};



#endif /* LOCKBASEDDESIGN_H_ */
