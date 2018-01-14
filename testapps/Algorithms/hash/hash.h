/*
 * hash.h
 *
 *  Created on: 12 Jan 2018
 *      Author: mitso23
 */

#ifndef HASH_H_
#define HASH_H_

class Hash
{
public:
	Hash(unsigned int size ) : m_size(size)
	{

	}

	class BucketNode
	{
	public:
		BucketNode(int key, int data) : m_key(key), m_data(data)
		{

		}
	public:
		int m_key;
		int m_data;
		BucketNode* nextNode = nullptr;
	};

	class Bucket
	{
	public:
		void addItem(int key, int value)
		{
			if (m_head == nullptr)
			{
				m_head = new BucketNode(key, value);
				std::cout << "add head,  key: " << key << " data: " << value << std::endl;
			}
			else
			{
				BucketNode* current = m_head;
				while(current && current->nextNode)
				{
					current = current->nextNode;
				}

				current->nextNode = new BucketNode(key, value);
				std::cout << "add,  key: " << key << " data: " << value << std::endl;
			}
		}

		bool findValue(int key, int& result)
		{
			BucketNode* current = m_head;
			while(current)
			{
				if (current->m_key == key)
				{
					result = current->m_data;
					std::cout << "found key: " << key << " data: " << result << std::endl;
					return true;
				}
				else
				{
					std::cout << "not match key: " << key << " data: " << result << std::endl;
				}

				current= current->nextNode;
			}

			std::cout << "failed key: " << key << " data: " << result << std::endl;
			return false;
		}

	private:
		BucketNode* m_head = nullptr;
	};

public:
	void addItem(int key, int value)
	{
		int hashedKey = key % m_size;
		Bucket& backet = m_bucket[hashedKey];

		backet.addItem(key, value);
	}

	bool findValue(int key, int& result)
	{
		int hashedKey = key % m_size;
		Bucket& backet = m_bucket[hashedKey];
		return backet.findValue(key, result);
	}

private:
	unsigned int m_size;
	Bucket m_bucket[10];
};

#endif /* HASH_H_ */
