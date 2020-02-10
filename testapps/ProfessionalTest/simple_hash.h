#pragma once
#include <stdio.h>
#include <unordered_set>

#define MAX_NAME	(15)
#define MAX_ITEM	 (1000000)
#define MAX_HASHTABLE	(100000) // use this for hash table size (prime number is always good)

class Student {
public:
	char name[MAX_NAME + 1]; // key (which is unique)
	int score;	// data
	Student* next; // for seperate chaining - hash table
	Student* prev; // for seperate chaining - hash table (when no deletion, it doesn't need)

	Student() {
		init();
	}

	void init() {
		score = 0;
		name[0] = '\0';
		next = prev = nullptr;
	}
};

Student students[MAX_ITEM];
int numStudents;

namespace test
{

class Node
{
	Student* student;
	Node* next;
};

class List
{
	void Insert(const char* name, int score)
	{
		if (!head && !tail)
		{

		}
	}

	Student* Find(const char* name)
	{

	}

	void Delete(const char* name)
	{

	}

	Node* head;
	Node* tail;
};

#define LOG_INFO(X) //std::cout << __FUNCTION__ << ": " << X << std::endl;
#define LOG_ERROR(X) //std::cout << __FUNCTION__ << ": " << X << std::endl;
#define LOG_DEBUG(X) //std::cout << __FUNCTION__ << ": " << X << std::endl;
#define MAX_COLLISIONS 30

int myStrLen(const char* s)
{
	size_t len = 0;
	for(;;)
	{
		unsigned x = *(unsigned*)s;
		if((x & 0xFF) == 0) return len;
		if((x & 0xFF00) == 0) return len + 1;
		if((x & 0xFF0000) == 0) return len + 2;
		if((x & 0xFF000000) == 0) return len + 3;
		s += 4, len += 4;
	}

	return len;
}

void myStrCopy(const char* src, char* dst)
{
	while (*src)
	{
		*dst++ = *src++;
	}

	*dst = '\0';
}

bool myStrCmp(const char* src, const char* dst)
{

	int lengthSrc = myStrLen(src);
	int lengthDst = myStrLen(dst);

	if (lengthSrc != lengthDst)
	{
		return false;
	}

#if 1
	int numFourBytes = lengthSrc / 4;
	int remaining = lengthSrc % 4;

	int* srcI = (int*)src;
	int* dstI = (int*)dst;

	for (int i = 0; i< numFourBytes; ++i)
	{
		if (dst[i] != src[i])
		{
			return false;
		}
	}

	char* srcC = (char*)srcI;
	char* dstC = (char*)dstI;

	for(int i=0; i< remaining; ++i)
	{
		if (srcC[i + numFourBytes] != dstC[i + numFourBytes])
		{
			return false;
		}
	}
#else

	for (int i=0; i< lengthSrc; ++i)
	{
		if (src[i] != dst[i])
		{
			return false;
		}
	}

#endif


	return true;
}

int convertStringToInt(const char* name)
{
	unsigned long long int hash = 123456;
	uint32_t prime = 13;
	int strLen = myStrLen(name);

	for (int i = 0; i < strLen; ++i)
	{
#if 0
		hash += hash*MAX_HASHTABLE + name[i];
#endif
		//hash += name[i]*(i+1)*26;

		uint8_t value = name[i];
		hash = hash ^ value;
		hash *= prime;
	}

	int calculatedHash = hash %(MAX_HASHTABLE - 1);

	LOG_DEBUG("name: " << name << " hash: " << calculatedHash);

	return calculatedHash;
}

struct Bucket
{
	Bucket()
	{
		this->numberStudents = 0;
	}

	void insert(const char* name, int score)
	{
		LOG_INFO("Adding student to bucket: " << name << " number of students: " << numberStudents);

		if (numberStudents > MAX_COLLISIONS)
		{
			LOG_ERROR("Max number of students reached");
			return;
		}

		for (int i = 0; i < MAX_COLLISIONS; ++i)
		{
			if (students[i].name[0] == '\0')
			{
				myStrCopy(name, students[i].name);
				students[i].score = score;

				LOG_INFO("Found an empty slot: " << i);
				break;
			}
		}

		++numberStudents;
	}

	void remove(const char* name)
	{
		for (int i = 0; i < MAX_COLLISIONS; ++i)
		{
			if (myStrCmp(students[i].name, name))
			{
				LOG_INFO("Found the match for name: " << name);
				students[i].init();
				--this->numberStudents;
				return;
			}
		}

		LOG_INFO("Couldn't find the name: " << name);
	}

	Student* find(const char* name)
	{
		for (int i = 0; i < MAX_COLLISIONS; ++i)
		{
			if (myStrCmp(students[i].name, name))
			{
				LOG_INFO("Found the match for name: " << name);
				return &students[i];

			}
		}

		return nullptr;
	}

	Student students[MAX_COLLISIONS];
	int numberStudents;
};

#if 0
#include <unordered_map>
std::unordered_map<const char*, Student*> stdMap;
#endif

struct Hash
{
	void insert(const char* name, int score)
	{
		int hash = convertStringToInt(name);
		buckets[hash].insert(name, score);

#if 0
		Student* student = new Student();
		myStrCopy(name, student->name);
		student->score = score;

		stdMap.insert(std::make_pair(name, student));
#endif
	}

	void remove(const char* name)
	{
		int hash = convertStringToInt(name);
		buckets[hash].remove(name);

#if 0
		stdMap.erase(name);
#endif
	}

	Student* FindStudent(const char* name)
	{
		int hash = convertStringToInt(name);
		return buckets[hash].find(name);

#if 0
		auto it = stdMap.find(name);
		if (it != std::end(stdMap))
		{
			return it->second;
		}
#endif
	}

	Bucket buckets[MAX_HASHTABLE];
};

static Hash hash;

void init()
{
	numStudents = 0;
}

Student* search(const char name[MAX_NAME + 1])
{
	return hash.FindStudent(name);
}

void insert(const char name[MAX_NAME + 1], const int score)
{
	hash.insert(name, score);
}

void del(const char name[MAX_NAME + 1])
{
	hash.remove(name);
}

}

