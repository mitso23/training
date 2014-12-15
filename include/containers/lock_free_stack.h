#ifndef LOCK_FREE_STACK_H_
#define LOCK_FREE_STACK_H_
#include <memory>

//NEW_NODE->HEAD->NEXT->NEXT->NEXT->LAST
template <typename T>
class lock_free_stack
{
private:
	struct node
	{
		T data;
		node* next;
		node(const T& _data) : data(_data), next(NULL)
		{

		}
	};

	std::atomic<node*> head;

public:
	// 1) create a node
	// 2) set node next pointer to head
	// 3) set head as new node

	void push(const T& data)
	{
		node* const new_node=new node(data);
		new_node->next=head.load();

		while(!head.compare_exchange_weak(new_node->next,new_node));
	}

	//Read the current value of head.
	//Read head->next.
	//Set head to head->next.
	//Return the data from the retrieved node.
	//Delete the retrieved node

	bool pop(T& result)
	{
		bool done = false;
		auto head_copy = head.load();

		while(!done)
		{
			if (!head_copy)
			{
				return false;
			}

			auto next = head_copy->next;
			done = !head.compare_exchange_weak(head_copy, next);
		}

		result= head_copy.data;
		//delete head;

		return true;
	}
};

#endif /* LOCK_FREE_STACK_H_ */
