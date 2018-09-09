/*
 * insertion_sort.h
 *
 *  Created on: 25 Mar 2018
 *      Author: mitso23
 */

#ifndef INSERTION_SORT_H_
#define INSERTION_SORT_H_

#include "../linklist/list.h"

void insertion_sort(int arr[], unsigned int size)
{
	int i=1;
	while(i < size)
	{
		int j=i;
		//std::cout << "i: " << i << " j: " << j << " arr[j]: " << arr[j] << std::endl;
		while(j > 0)
		{
			if (arr[j-1] > arr[j])
			{
				//std::cout << "swapping: " << arr[j-1] << " with: " << arr[j] << std::endl;

				int temp = arr[j];
				arr[j] = arr[j-1];
				arr[j-1] = temp;
				--j;
			}
			else
			{
				break;
			}
		}

		++i;
	}
}

void exchange(Node* l, Node* r)
{
	Node* l_previous = l->previous;
	Node* l_next = l->next;

	Node* r_previous = r->previous;
	Node* r_next = r->next;

	r->next = l;
	r->previous = l_previous;
	if (l_previous)
		l_previous->next = r;

	l->next = r_next;
	l->previous = r;
	if (r_next && r_next->previous)
		r_next->previous = l;

}

void link(Node* l, Node* r)
{
	if (r->previous)
		r->previous->next = r->next;

	if (r->next)
		r->next->previous = r->previous;

	r->next = l->next;
	r->previous = l;

	if (l->next)
		l->next->previous = r;

	l->next = r;
}

void insertion_sort_list(Node** phead, Node* hint = nullptr)
{
	Node* head = *phead;

	if (!head || !head->next)
	{
		return;
	}

	Node* start = nullptr;

	if (hint)
	{
		start = hint;
	}
	else
	{
		start = head->next;
	}

	while(start)
	{
		Node* end = start;
		Node* next = start->next;
		Node* l = nullptr;
		Node* r = nullptr;

		while(end)
		{
			if (!r && end->previous && end->previous->data > end->data)
			{
				//std::cout << end->previous->data << " larger than: " << end->data << " try to find the swap point" << std::endl;
				r = end;
			}
			else if (r && end->data < r->data)
			{
				l = end;

				//std::cout << l->data << " smaller than: " << r->data << " moving: " << std::endl;

				link(l, r);
				l = nullptr;
				r = nullptr;
				break;
			}
			else if (r)
			{
				//nothing to do here
			}
			else
			{
				break;
			}

			end = end->previous;
		}

		if (r && !l)
		{
			//std::cout << "found r with no l, making r the head" << std::endl;

			(*phead)->previous = r;

			if (r->previous)
				r->previous->next = r->next;

			if (r->next)
				r->next->previous = r->previous;

			r->next = (*phead);
			r->previous  = nullptr;

			(*phead) = r;
		}

		start = next;
	}


}

#endif /* INSERTION_SORT_H_ */
