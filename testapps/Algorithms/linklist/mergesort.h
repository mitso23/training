#ifndef _MERGESORT_H_
#define _MERGESORT_H_

#include "list.h"

void FrontBackSplit(struct Node* source, struct Node** frontRef, struct Node** backRef)
{
	if (source == NULL || source->next == NULL)
	{
		// < length of list less than 2
		*frontRef = source;
		*backRef = nullptr;
		return;
	}
	else
	{
		auto slow = source;
		auto fast = source->next;

		while(fast != nullptr && fast->next != nullptr)
		{
			slow = slow->next;
			fast = fast->next->next;

			//std::cout << "slow: " << slow->data << " fast: " << fast->data << std::endl;
		}

		std::cout << "mid point is " << slow->data << std::endl;

		*frontRef = source;
		//slow now points to one element before the mid
		*backRef = slow->next;

		slow->next = nullptr;
	}

}

struct Node* SortedMerge2(struct Node* a, struct Node* b)
{

	Node dummy;
	dummy.data = -1;

	Node* head = &dummy;
	Node* tail = &dummy;

	Node* a_start = a;
	Node* b_start = b;

	while(a_start && b_start)
	{
		if (a_start->data < b_start->data)
		{
			tail->next = a_start;

			a_start = a_start->next;
			tail = tail->next;
		}
		else
		{
			tail->next = b_start;

			b_start = b_start->next;
			tail = tail->next;
		}
	}

	while(a_start)
	{
		tail->next = a_start;
		tail = tail->next;
		a_start = a_start->next;
	}

	while(b_start)
	{
		tail->next = b_start;
		tail = tail->next;
		b_start= b_start->next;
	}

	head = head->next;
	return head;
}

struct Node* SortedMerge(struct Node* a, struct Node* b)
{
  struct Node* result = NULL;

  /* Base cases */
  if (a == NULL)
     return(b);
  else if (b==NULL)
     return(a);

  /* Pick either a or b, and recur */
  if (a->data <= b->data)
  {
     result = a;
     result->next = SortedMerge(a->next, b);
  }
  else
  {
     result = b;
     result->next = SortedMerge(a, b->next);
  }
  return(result);
}


void MergeSortList(Node*& list)
{
	//base case
	if (list == nullptr || *list == nullptr || (*list)->next == nullptr)
	{
		return;
	}

	Node* a = nullptr;
	Node* b = nullptr;

	FrontBackSplit(*list, &a, &b);

	MergeSortList(&a);
	MergeSortList(&b);

	*list = SortedMerge(a, b);
}

#endif /* MERGESORT_H_ */
