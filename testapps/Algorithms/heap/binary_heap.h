/*
 * binary_heap.h
 *
 *  Created on: 6 Feb 2018
 *      Author: mitso23
 */

#ifndef BINARY_HEAP_H_
#define BINARY_HEAP_H_

class Heap
{

public:
	Heap(unsigned int capacity)
	: m_capacity(capacity)
	, m_size(0)
	{
		m_array = new int[m_capacity];
	}

	Heap(unsigned int capacity, int array[], unsigned int size)
		: m_capacity(capacity)
		, m_array(array)
		, m_size(size)
	{
		//on average this will be n
		int i = (m_size - 1) / 2;

		while(i-->=0)
		{
			heapify(i);
		}
	}

	int getKthSmallestElement(int k)
	{
		int value = 0;
		for(auto i=0; i< k; ++i)
		{

			getMinValue(value);
		}

		return value;
	}

	void insertItem(int item)
	{
		if (m_size > m_capacity)
		{
			std::cout << "error size greater than capacity: " << std::endl;
		}
		auto childIndex = m_size;
		m_array[childIndex] = item;

		fixHeapBottomUp(childIndex);
		//std::cout << "item: " << item << " index " << childIndex << std::endl;

		++m_size;
	}

	void decreaseKey(int i, int val)
	{
		if (i > m_size)
		{
			std::cerr << " error " << i << " greater than size: " << m_size << std::endl;
			return;
		}

		m_array[i] = val;
		fixHeapBottomUp(i);
	}

	void deleteKey(int i)
	{
		decreaseKey(i, std::numeric_limits<int>::min());
		auto minValue = 0;
		getMinValue(minValue);
	}

	bool getMinValue(int& value)
	{
		if (m_size == 0)
		{
			return false;
		}

		value = m_array[0];

		if (m_size != 1)
		{
			m_array[0] = m_array[m_size - 1];
			heapify(0);
		}

		--m_size;

		return true;
	}

	void printHeap()
	{
		for(unsigned int i=0; i< m_size; ++i)
		{
			std::cout << m_array[i] << std::endl;
		}
	}

	void sortHeap()
	{
		auto origSize = m_size;

		for(unsigned int i=0; i< origSize; ++i)
		{
			swap(&m_array[0], &m_array[origSize-i]);
			--m_size;
			heapify(0);
		}

		m_size = origSize;
	}

	void heapify(unsigned int index)
	{
		auto parentNode = &m_array[index];

		auto leftChildIndex = index;
		auto rightChildIndex = index;

		auto leftChild = getLeftChild(leftChildIndex);
		auto rightChild = getRightChild(rightChildIndex);

		if (!leftChild && !rightChild)
		{
			return;
		}
		else if (leftChild && !rightChild)
		{
			if (*leftChild < *parentNode)
			{
				swap(leftChild, parentNode);
				heapify(leftChildIndex);
				return;
			}
		}
		else if (leftChild && rightChild)
		{
			if (*leftChild < *rightChild)
			{
				if (*leftChild < *parentNode)
				{
					swap(leftChild, parentNode);
					heapify(leftChildIndex);
					return;
				}
			}
			else
			{
				if (*rightChild < *parentNode)
				{
					swap(rightChild, parentNode);
					heapify(rightChildIndex);
					return;
				}
			}
		}
		else if (rightChild && !leftChild)
		{
			std::cout << "ERROR: not possible to have right child without a left child, index: " << index << " data: " << m_array[index] << std::endl;
		}
		else
		{
			std::cout << "ERROR: not possible" << std::endl;
			return;
		}

	}

	int* getArr()
	{
		return m_array;
	}

private:

	void swap(int* l, int* r)
	{
		//std::cout << "swapping " << *l << " with: " << *r << std::endl;
		auto temp = *l;
		*l = *r;
		*r = temp;
	}

	void fixHeapBottomUp(unsigned int childIndex)
	{
		auto parentIndex = childIndex;

		while(auto parent = getParent(parentIndex))
		{
			if (*parent > m_array[childIndex])
			{
				swap(parent, &m_array[childIndex]);
			}
			else
			{
				break;
			}

			childIndex = parentIndex;
		}
	}

	int* getParent(unsigned int& i)
	{
		if (i & 1)
		{
			if (i >= 1)
			{
				i = (i - 1) /2;
				return &m_array[i];
			}
		}
		else
		{
			if (i >= 2)
			{
				i = (i - 2)/2;
				return &m_array[i];
			}
		}

		return nullptr;
	}

	int* getLeftChild(unsigned int& i)
	{
		auto childIndex = 2*i + 1;

		if (childIndex >= m_size)
		{
			return nullptr;
		}

		i = childIndex;

		return &m_array[i];
	}

	int* getRightChild(unsigned int& i)
	{
		auto childIndex = 2*i + 2;

		if (childIndex >= m_size)
		{
			return nullptr;
		}

		i = childIndex;
		return &m_array[i];
	}

private:
	unsigned int m_capacity;
	unsigned int m_size;
	int* m_array;
};

#endif /* BINARY_HEAP_H_ */
