#ifndef AUTOCORRECTION_H_
#define AUTOCORRECTION_H_

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
	unsigned sum = 0;
	for(unsigned int i=0; i< strlen(str); ++i)
	{
		sum+= sum * 131 + str[i];
	}

	return sum % 70000;
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
		if (index < 20)
		{
			buckets[index] = *bucket;
			++index;
		}
		else
		{
			std::cout << "SHIT" << std::endl;
			abort();
		}
	}

	Bucket buckets[20];
	unsigned int index;
};

struct Hash
{
	Hash()
	{

	}

	void AddWord(const char* str)
	{
		unsigned int key = HashGenerator(str);
		static int counter = 0;
		//std::cout << "Add str: " << str << " key: " << key << std::endl;

		Bucket bucket = { str, key };

		if(table[bucket.key].index != 0)
		{
			//std::cout << "collision detected for string " << bucket.str << " count: " << ++counter << std::endl;
		}

		table[bucket.key].AddBucket(&bucket);
	}

	bool CheckWordExists(const char* str)
	{
		unsigned int key = HashGenerator(str);
		//std::cout << "Get str: " << str << " key: " << key << std::endl;

		for(unsigned int i=0; i< table[key].index; ++i)
		{
			if (strcmp(table[key].buckets[i].str, str) == 0)
			{
				return true;
			}
		}

		return false;
	}

	static Array table[70000];
};

Array Hash::table[70000];


#endif /* AUTOCORRECTION_H_ */
