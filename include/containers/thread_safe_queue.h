#ifndef THREAD_SAFE_QUEUE_H_
#define THREAD_SAFE_QUEUE_H_

#include <mutex>
#include <memory>
#include <condition_variable>
#include <queue>
#include <iostream>


//NEXT_ITEM<-TAIL<-ITEM<-ITEM<-HEAD
template<typename T>
class FineGrainLockQueue
{
private:
	struct Node
	{
		T data;
		Node* next;
		std::mutex m_mutex;

		Node(T _data) :
				data(_data), next(NULL)
		{

		}
	};

	std::condition_variable m_condVar;
	Node* m_dummyNode;
	Node* m_head;
	Node* m_tail;

public:
	FineGrainLockQueue() :
			m_dummyNode(new Node(T())), m_head(m_dummyNode), m_tail(m_dummyNode)
	{

	}

	void push(const T& data)
	{
		Node* newNode = new Node(data);

		std::unique_lock < std::mutex > lock(m_tail->m_mutex);

		if (m_tail == m_dummyNode)
		{
			m_head = newNode;
			m_head->next = NULL;
			m_tail = m_head;

			m_condVar.notify_one();
			return;

		}
		else
		{
			m_tail->next= newNode;
			m_tail = newNode;
		}

	}

	void wait_pop(T& data)
	{
		std::unique_lock < std::mutex > lock(m_head->m_mutex);

		m_condVar.wait(lock, [this]	{ return m_head != m_dummyNode;});

		data = m_head->data;
		auto m_nextNode = m_head->next;

		if (m_nextNode)
		{
			std::unique_lock < std::mutex > lock2(m_nextNode->m_mutex);
			delete m_head;
			m_head = m_nextNode;
		}
		else
		{
			delete m_head;

			m_head = m_dummyNode;
			m_tail = m_dummyNode;
		}

	}
};



#endif /* THREAD_SAFE_QUEUE_H_ */
