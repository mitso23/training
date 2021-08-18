#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <chrono>

template <class T>
class FixedBlockingQueue
{
 public:
	/**
	 * Constructor
	 * @param size the maximum size of the fixed queue before it blocks
	 */
	explicit FixedBlockingQueue(unsigned size)
		: m_maxSize(size)
	{

	}

	/**
	 * Destructor
	 */
	~FixedBlockingQueue();

	/**
	 * Push an event to the queue
	 * @note This will block the caller if queue is full
	 * @param event
	 */
	void Push(T&& event);

	/**
	 * @return an element from the queue.
	 * @note the caller will block if the queue is empty
	 */
	 T Pop();

	/**
	 * clear the queue and unblock producer
	 */
	void Clear();

	/**
	 * @return true if the queue is full
	 */
	bool IsFull() const;

	/**
	 * @return the size of the queue
	 */
	typename std::queue<T>::size_type Size()const ;

 private:
	std::queue<T> m_queue;
	mutable std::mutex m_mutex;
	std::condition_variable m_con;
	unsigned m_maxSize;
};

template <class T>
FixedBlockingQueue<T>::~FixedBlockingQueue()
{
	std::lock_guard<std::mutex> lock(m_mutex);
	m_con.notify_all();
}

template <class T>
void FixedBlockingQueue<T>::Push(T&& event)
{
	std::unique_lock<std::mutex> lock(m_mutex);
	if (m_queue.size() < m_maxSize)
	{
		m_queue.push(std::move(event));
		m_con.notify_one();
	}
	else
	{
		while(m_queue.size() >= m_maxSize)
		{
			m_con.wait(lock);
		}

		m_queue.push(std::move(event));
		m_con.notify_one();
	}
}

template <class T>
typename std::queue<T>::size_type FixedBlockingQueue<T>::Size() const
{
	std::lock_guard<std::mutex> lock(m_mutex);
	return m_queue.size();
}

template<typename T>
bool FixedBlockingQueue<T>::IsFull() const
{
	std::lock_guard<std::mutex> lock(m_mutex);
	return (m_maxSize == m_queue.size());
}

template <class T>
T FixedBlockingQueue<T>::Pop()
{
	std::unique_lock<std::mutex> lock(m_mutex);
	while(m_queue.empty())
	{
		m_con.wait(lock);
	}

	auto  event = std::move(m_queue.front());
	m_queue.pop();

	m_con.notify_one();

	return std::move(event);
}

template <class T>
void
FixedBlockingQueue<T>::Clear()
{
	std::unique_lock<std::mutex> lock(m_mutex);
	std::queue<T> empty;
	std::swap(m_queue, empty);
	m_con.notify_one();
}

