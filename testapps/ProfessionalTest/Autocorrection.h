#ifndef AUTOCORRECTION_H_
#define AUTOCORRECTION_H_

#include "../Algorithms/trees/ternary_search_tree.h"

#include <string.h>
#include <deque>

struct Trie
{
	Trie()
	{
		for(unsigned int i=0; i< NUM_CHARACTERS; ++i)
		{
			content[i] = NULL;
		}

		lastCharacter = false;
	}

	Trie* AddChar(char c)
	{
		int cc = c - 'a';

		if (content[cc] == NULL)
		{
			content[cc] = new Trie();
			return content[cc];
		}
		else
		{
			return content[cc];
		}
	}

	void AddWord(const char* str)
	{
		unsigned int len = strlen(str);
		if (!len)
		{
			std::cout << "0 length str: " << std::endl;
			return;
		}

		Trie* currentTrie = NULL;
		for(unsigned int i=0; i< len; ++i)
		{
			if (currentTrie)
			{
				currentTrie = currentTrie->AddChar(str[i]);
			}
			else
			{
				currentTrie = AddChar(str[i]);
			}
		}

		currentTrie->lastCharacter = true;
	}

	bool CheckWordExists(const char* str)
	{
		int c = str[0] - 'a';
		Trie* current = content[c];
		if (!current)
		{
			return false;
		}

		for(unsigned int i=1; i< strlen(str); ++i)
		{
			int c = str[i] - 'a';
			current = current->content[c];

			if (!current)
			{
				return false;
			}
		}

		if (current && current->lastCharacter)
		{
			return true;
		}

		return false;
	}

	void PrintAllWords(Trie* currentTrie, std::deque<char>& q)
	{
		if (!currentTrie)
		{
			if (q.size())
				q.pop_back();

			return;
		}

#if 0
		if (currentTrie->lastCharacter)
		{
			for(unsigned int i=0; i< q.size(); ++i)
			{
				std::cout << q[i];
			}

			std::cout << std::endl;
		}
#endif
		for(unsigned int i=0; i< NUM_CHARACTERS; ++i)
		{
			if (currentTrie->content[i])
			{
				q.push_back(i + 'a');
				PrintAllWords(currentTrie->content[i], q);
			}
		}

		if (q.size())
			q.pop_back();
	}

	void PrintAllWords()
	{
		std::deque<char> q;
		PrintAllWords(this, q);
	}

private:
	static const int NUM_CHARACTERS = 36;
	Trie* content[NUM_CHARACTERS];
	bool lastCharacter;
};

unsigned int HashGenerator(const char* str)
{
	unsigned sum = 5381;
	for(unsigned int i=0; i< strlen(str); ++i)
	{
		sum+= sum * 33 + str[i];
	}

	return sum % 70000;
}

inline uint32_t HashGenerator2(const char* str) {

    uint32_t hash = 123456;
    uint32_t prime = 13;

    for(int i = 0; i < strlen(str); ++i) {
        uint8_t value = str[i];
        hash = hash ^ value;
        hash *= prime;
    }

    return hash % 70000;

}

struct Bucket
{
	const char* str;
	unsigned int key;
};

struct ListNode
{
	ListNode(const Bucket* bucket_)
		: next(NULL)
		, bucket(*bucket_)
	{

	}

	ListNode* next;
	Bucket bucket;
};

struct List
{
	List()
	{
		head = NULL;
		tail = NULL;
		counter = 0;
	}

	void AddBucket(const Bucket* bucket)
	{
		if (!head)
		{
			head = new ListNode(bucket);
			tail = head;
			++counter;
		}
		else
		{
			ListNode* node = new ListNode(bucket);
			tail->next = node;
			tail = node;
			++counter;

			std::cout << "number of items bucket: " << counter << std::endl;
		}
	}

	ListNode* head;
	ListNode* tail;
	unsigned int counter;

};

struct Array
{
	Array()
	{
		index = 0;
	}

	void AddBucket(const Bucket* bucket)
	{
		if (index < 10)
		{
			buckets[index] = *bucket;
			++index;

			//if (index >=2)
			  //  std::cout << "collision detected for string " << bucket->str << " count: " << index << std::endl;
		}
		else
		{
			std::cout << "SHIT: " << index << std::endl;
			abort();
		}
	}

	void Print()
	{
	    for(unsigned int i=0; i< index; ++i)
	    {
	        //std::cout << "i: " << i << " str: " << buckets[i].str<< std::endl;
	    }
	}

	Bucket buckets[10];
	unsigned int index;
};

struct Hash
{
	Hash()
	{

	}

	void AddWord(const char* str)
	{
		unsigned int key = HashGenerator2(str);
		static int counter = 0;
		char* strCopy = (char*)malloc(strlen(str) + 1);
		strcpy(strCopy, str);
		//std::cout << "Add str: " << str << " key: " << key << std::endl;

		Bucket bucket = { strCopy, key };

		if(table[bucket.key].index != 0)
		{

		}
		else
		{
		    //std::cout << "no collision" << std::endl;
		}

		table[bucket.key].AddBucket(&bucket);
	}

	bool CheckWordExists(const char* str)
	{
		unsigned int key = HashGenerator2(str);
		//std::cout << "Get str: " << str << " key: " << key << std::endl;

		for(unsigned int i=0; i< table[key].index; ++i)
		{
		    if (table[key].buckets[i].key != key)
		    {
		        //std::cerr << "keys are not the same " << std::endl;
		        return false;
		    }

			if (strcmp(table[key].buckets[i].str, str) == 0)
			{
				return true;
			}
		}

		return false;
	}

	void PrintAllWords()
	{
	    for(unsigned int i=0; i< 70000; ++i)
	    {
	        table[i].Print();
	    }
	}

	static Array table[70000];
};

Array Hash::table[70000];


#endif /* AUTOCORRECTION_H_ */
