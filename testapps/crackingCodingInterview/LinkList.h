#ifndef TRAINING_TESTAPPS_CRACKINGCODINGINTERVIEW_LINKLIST_H_
#define TRAINING_TESTAPPS_CRACKINGCODINGINTERVIEW_LINKLIST_H_

#include <iostream>

namespace LinkList
{
	template<typename T>
	struct Node
	{
		Node() = default;

		explicit Node(T val) : value(val)
		{

		}

		T value = T();
		Node* next = nullptr;
	};

	template<typename T>
	void CreateSingleList(T arr[], unsigned size, Node<T>*& head)
	{
		for(unsigned int count = 0; count < size; ++count)
		{
			if (!head)
			{
				head = new Node<T>(arr[count]);
			}
			else
			{
				Node<T>* n = new Node<T>(arr[count]);
				n->next = head;
				head = n;
			}
		}
	}

	template<typename T>
	void DisplaySingleList(Node<T>& head)
	{
		Node<T>* current = &head;
		while(current)
		{
			std::cout << current->value << std::endl;
			current = current->next;
		}
	}

	// 1 2 3 4 5 6 7 8
	template<typename T>
	void RemoveMiddleElement(Node<T>*& head)
	{
		if (!head)
		{
			return;
		}

		Node<T>* previous = nullptr;
		Node<T>* current = head;
		Node<T>* nextNext = current->next ? current->next->next : current->next;

		if (!previous)
		{
			head = nullptr;
		}
		else
		{
			previous->next = current->next;
			delete current;
		}
	}

	// 1, 2, 3, 2, 1
	// 1, 2, 2, 1
	Node<int>*  CheckIfLinkListPalindrome(Node<int>* list, int length)
	{
		std::cout << "value: " << list->value << " length: " << length << std::endl;
		//we are in the middle
		if(length == 1)
		{
			return list->next;
		}
		//for even elements
		else if (length == 0)
		{
			return list;
		}

		Node<int>* r = CheckIfLinkListPalindrome(list->next, length - 2);
		if (r == nullptr)
		{
			std::cout << "not a palindrome or the end: " <<  list->value << std::endl;
			return nullptr;
		}
		else if (list->value == r->value)
		{
			std::cout << "it is a match: " << list->value << std::endl;
			return r->next;
		}

		return nullptr;
	}

	int ReturnIntersectionPoint(Node<int>* list1, Node<int>* list2)
	{
		int counter1 = 0;
		int counter2 = 0;

		Node<int>* current1 = list1;
		Node<int>* current2 = list2;

		while(current1 && current2)
		{
			current1 = current1->next;
			current2 = current2->next;
			++counter1;
			++counter2;
		}

		while(current1)
		{
			current1 = current1->next;
			++counter1;
		}

		while(current2)
		{
			current2 = current2->next;
			++counter2;
		}

		if (current2 > current1)
		{
			return current2 - current1;
		}
		else
		{
			return current1 - current2;
		}
	}
}

#endif //TRAINING_TESTAPPS_CRACKINGCODINGINTERVIEW_LINKLIST_H_
