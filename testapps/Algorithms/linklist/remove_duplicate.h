/*
 * remove_duplicate.h
 *
 *  Created on: 11 Mar 2018
 *      Author: mitso23
 */

#ifndef REMOVE_DUPLICATE_H_
#define REMOVE_DUPLICATE_H_

#include "list.h"

void removeDuplicate(Node* head)
{
	if (!head)
	{
		return;
	}

	auto previous = head;
	auto replace = head->next;
	auto current = head->next;

	while(current != nullptr)
	{
		if (current->data != previous->data)
		{
			if (current != replace)
			{
				replace->data = current->data;
			}

			replace = replace->next;
		}

		current = current->next;
		previous = previous->next;
	}

	replace->next = nullptr;
}

#endif /* REMOVE_DUPLICATE_H_ */
