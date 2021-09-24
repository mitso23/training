/*
 * easy.h
 *
 *  Created on: 12 Nov 2017
 *      Author: mitso23
 */

#ifndef EASY_H_
#define EASY_H_

/*Given a set of yesterday Amazon stock prices {2, -3, 5, 8, 1}
Write a code to buy and sell those stocks at maximum profit.
*/

#include "stdlib.h"
#include <iostream>
#include <algorithm>

struct MaxStock
{
	int max = 0;
	int pos = 0;
};

struct MinStock
{
	int min = 0;
	int pos = 0;
};

void findMaxStock(int* arr, unsigned int start, unsigned int size, struct MaxStock& maxStock)
{
	int max = arr[start];
	int pos = start;

	for(unsigned int i=pos + 1; i< size; ++i)
	{
		if (arr[i] > max)
		{
			max = arr[i];
			pos = i;
		}
	}

	maxStock.max = max;
	maxStock.pos = pos;
}

int calculate_max_profit_stock_sell(int* arr, unsigned int size)
{
	MaxStock maxStock;
	MinStock minStock;
	int maxProfit = 0;

	if (size == 1)
	{
		return arr[0];
	}
	else if (size == 2)
	{
		return abs(arr[1] - arr[0]);
	}
	else
	{
		minStock.min = arr[0];
		minStock.pos = 0;

		findMaxStock(arr, 0, size, maxStock);
		maxProfit = maxStock.max - minStock.min;

		std::cout << "min: " << minStock.min << " max: " << maxStock.max << " profit: " << maxProfit << std::endl;

		for(unsigned int i=2; i< size; ++i)
		{
			if (arr[i] < minStock.min)
			{
				minStock.min = arr[i];
				minStock.pos = i;

				if (i < (unsigned)maxStock.pos)
				{
					std::cout << "new min: " << minStock.min << " profit: " << maxProfit << std::endl;

					maxProfit = maxStock.max - minStock.min;
				}
				else
				{
					findMaxStock(arr, i, size, maxStock);

					std::cout << "new min and max: " << minStock.min << " max: " << maxStock.max << " profit: " << maxProfit << std::endl;

					if ((maxStock.max - minStock.min) > maxProfit)
					{
						maxProfit = maxStock.max - minStock.min;
					}
				}
			}
			else
			{
				continue;
			}
		}
	}

	return maxProfit;
}

void checkIfTwoElementsAddToSum(int* arr, unsigned int size, int sum)
{
	if (size <= 1)
	{
		return;
	}

	std::sort(arr, arr+size);

	for(unsigned int i=0, j=size - 1; i< size && j > i;)
	{
		if (arr[i] + arr[j] == sum)
		{
			std::cout << "found, i: " << i << " val: " << arr[i] << " j: " << j << " val: " << arr[j] << std::endl;
			++i;
			--j;
		}
		else if (arr[i] + arr[j] < sum)
		{
			++i;
		}
		else
		{
			--j;
		}
	}
}

void runLengthEncoding(std::string str)
{
	if (str.empty())
	{
		return;
	}

	if (str.size() == 1)
	{
		std::cout << str[0] << " : " << 1 << std::endl;
	}

	unsigned count = 1;

	for(unsigned int i=1; i< str.size(); ++i)
	{
		if (str[i] == str[i-1])
		{
			++count;
		}
		else
		{
			std::cout << str[i-1] << " : " << count << std::endl;
			count = 1;
		}
	}

	std::cout << str[str.size() - 1] << " : " << count << std::endl;
}

struct ListNode
{
	ListNode(int _data) : data(_data)
	{

	}

	int data;
	ListNode* next = nullptr;
	ListNode* previous = nullptr;
};

struct DoubleList
{

	void insertItem(int data)
	{
		if (m_head == nullptr)
		{
			m_head = new ListNode(data);
			m_tail = m_head;
		}
		else
		{
			ListNode* node = new ListNode(data);

			m_tail->next = node;
			node->previous = m_tail;
			m_tail = node;
		}
	}

	void iterateItemsForward()
	{
		auto current = m_head;

		while(current)
		{
			std::cout << current->data << std::endl;
			current = current->next;
		}
	}

	void iterateItemsBackword()
	{
		auto current = m_tail;

		while(current)
		{
			std::cout << current->data << std::endl;
			current = current->previous;
		}
	}

	ListNode* m_head = nullptr;
	ListNode* m_tail = nullptr;
};

void rotateDoubleLinkList(DoubleList& list, int N)
{
	ListNode* oldHead = list.m_head;
	ListNode* oldTail = list.m_tail;

	auto newHead = oldHead;
	auto newTail = oldTail;

	for(unsigned int i=0; i< N; ++i)
	{
		newHead=newHead->next;
		newTail=newTail->previous;
	}

	newTail->next = nullptr;
	oldTail->next = oldHead;

	list.m_head = newHead;
	list.m_tail = newTail;
}

#endif /* EASY_H_ */
