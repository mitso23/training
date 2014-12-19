#ifndef THREAD_SAFE_LIST_H_
#define THREAD_SAFE_LIST_H_

#include <mutex>
#include <memory>
#include <list>
#include <iostream>
#include <map>
#include <algorithm>

///HEAD->NEXT->NEXT->NEXT->NULL
template <typename T>
class threadsafe_list
{
public:
	void push_front(const T& value)
	{
		std::unique_ptr<node> new_node(new node(value));
		std::lock_guard<std::mutex> lk(head.mutex);
		new_node->next=std::move(head.next);
		head.next=std::move(new_node);
	}

	template<typename Function>
	void for_each(Function f)
	{
		node* current=&head;
		std::unique_lock<std::mutex> lk(head.mutex);

		while(node* const next=current->next.get())
		{
			std::unique_lock < std::mutex > next_lk(next->mutex);
			lk.unlock();
			f(next->data);
			current = next;
			lk = std::move(next_lk);
		}

	}

	template <typename Predicate>
	std::shared_ptr<T> find_first_if(Predicate p)
	{
		std::shared_ptr<T> result;
		for_each([&](std::shared_ptr<int> data)
				{
					if (p(data))
					{
						result= data;
					}
				});

		return result;
	}

	template <typename Predicate>
	bool remove_if(Predicate p)
	{
		node* current = &head;
		std::unique_lock < std::mutex > lk(head.mutex);

		while (node* const next = current->next.get())
		{
			std::unique_lock < std::mutex > next_lk(next->mutex);

			if (p(next->data))
			{
				//HEAD->NEXT->NEXT
				auto old_next= std::move(current->next);
				current->next= std::move(next->next);
				next_lk.unlock();
				return true;
			}
			else
			{
				lk.unlock();
				current = next;
				lk = std::move(next_lk);
			}
		}

		return false;
	}

private:
	class node
	{
		friend class threadsafe_list;
public:
		node() : next()
		{

		}

		node(const T& value) : data(std::make_shared<T>(value))
		{

		}

	private:
		std::mutex mutex;
		std::shared_ptr<T> data;
		std::unique_ptr<node> next;

	};

	node head;

};



#endif /* THREAD_SAFE_LIST_H_ */
