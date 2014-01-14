#ifndef STL_H_
#define STL_H_

#include <iostream>
#include <fstream>
#include <errno.h>
#include <string.h>
#include <sstream>
#include <iomanip>
#include <iterator>
#include <vector>
#include <utils/Noisy.h>
#include <algorithm>
#include <deque>
#include <list>

#if 0
#define DECLARE_LIST(T) \
	struct _Node
	{								\
		T data;						\
		struct _Node* next;			\
		struct _Node* previous;		\
	};								\
	typedef struct _Node Node;      \
	Node* m_current= NULL;			\
	Node* m_head= NULL;						\
	Node* m_tail= NULL;						\

#define ADD_LIST(X)                 \
									\
		if (!m_head)\
		{\
			m_head= new Node();\
			Node* current= m_head;\
\
			m_head->data= X;\
			m_tail= m_head;\
			current= m_head;\
			current->next= NULL;\
			current->previous= NULL;\
		}\
		else\
		{\
			Node* current= m_tail;\
\
			Node* node= new Node();\
			node->data= X; \
\
			node->next= current; \
			current->previous= node; \
			m_tail= node; \
\
			m_head->next= m_tail; \
		}\

#define DISPLAY_LIST() \
		Node* current= m_head; \
\
		while(current && current != m_tail) \
		{ \
			std::cout << current->data << std::endl; \
			current= current->previous; \
		}\
\
		std::cout << m_tail->data << std::endl; \


#define LIST_START() m_head;

#define LIST_END() m_tail

#define GET_NEXT() m_current->next

#define LIST Node*

#endif

template<class T>
class MyList
{
	template<class U>
	struct _Node
	{
		U data;
		struct _Node* next;
		struct _Node* previous;
	};

	typedef struct _Node<T> Node;

public:
	MyList() :
			m_head(NULL), m_tail(NULL)
	{

	}
	;

	void push_back(T data)
	{
		if (!m_head)
		{
			m_head = new Node();
			Node* current = m_head;

			m_head->data = data;
			m_tail = m_head;
			current = m_head;
			current->next = NULL;
			current->previous = NULL;
		}
		else
		{
			Node* current = m_tail;

			Node* node = new Node();
			node->data = data;

			node->next = current;
			current->previous = node;
			m_tail = node;

			m_head->next = m_tail;
		}
	}

	void displayList()
	{
		Node* current = m_head;

		while (current && current != m_tail)
		{
			std::cout << current->data << std::endl;
			current = current->previous;
		}

		std::cout << m_tail->data << std::endl;
	}

private:
	Node* m_head;
	Node* m_tail;
};

template<class Container, class MemFunct>
void Apply(Container& cont, MemFunct funct)
{
	typename Container::iterator it = cont.begin();

	while (it != cont.end())
	{
		((it)->*funct)();
		++it;
	}
}

class Z
{
	Z() :
			m_counter(0)
	{

	}

	int g()
	{
		return m_counter++;
	}

	friend ostream& operator <<(ostream& os, Z& z)
	{
		return os << z.m_counter;
	}

private:
	int m_counter;
};

void insertToVector()
{
	int a[]={ 1, 2, 3, 4, 5, 6 };

	std::vector<int> vec;

	copy(a, a + sizeof(a) / sizeof(int), back_inserter(vec));
	copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));

	cout << endl;
}

void IOStreamIterators()
{
	ifstream istream("/home/dimitrios/training/resources/testFile.txt");

	if (istream)
	{
		std::cout << "Successfully opened file" << std::endl;
	}
	else
	{
		std::cout << "Failed to open the file: " << strerror(errno)
				<< std::endl;
		return;
	}
	std::vector<string> skata;

	istream_iterator<string> start(istream);
	istream_iterator<string> end;

	copy(start, end, back_inserter(skata));
	copy(skata.begin(), skata.end(), ostream_iterator<string>(cout, " "));
}

//NOTE: WHEN  VECTOR RESIZES ITERATOR GET INVALIDATED
void vectorReallocation()
{
	std::vector<Noisy> vect;

	generate_n(back_inserter(vect), 10, NoisyGen());
	ostream_iterator<Noisy> out(cout , "");
	copy(vect.begin(), vect.end(), out);
	vect.erase(vect.begin() + vect.size() / 2);

}

void dequeuReallocation()
{
	std::deque<Noisy> deq;

	generate_n(back_inserter(deq), 10, NoisyGen());
	//ostream_iterator<Noisy> out(cout, "");
	//copy(deq.begin(), deq.end(), out);
	//deq.erase(deq.begin() + deq.size() / 2);
}

void convertContainers()
{
	std::deque<Noisy> deq;

	generate_n(back_inserter(deq), 10, NoisyGen());

	//std::vector<Noisy> vec(deq.begin(), deq.end());
	std::vector<Noisy> vec;
	vec.reserve(10);
	vec.assign(deq.begin(), deq.end());
	copy(deq.begin(), deq.end(), ostream_iterator<Noisy>(cout, ""));

}

void listReallocation()
{
	std::list<Noisy> list;

	generate_n(back_inserter(list), 10, NoisyGen());
	list.erase(list.begin());

}

void listOperations()
{
	std::list<Noisy> list1,list2,list3;

	generate_n(back_inserter(list1), 5, NoisyGen());
	generate_n(back_inserter(list2), 5, NoisyGen());
	generate_n(back_inserter(list3), 5, NoisyGen());

	std::cout << "before splice " << std::endl;

	copy(list1.begin(), list1.end(), ostream_iterator<Noisy>(cout, " "));

	std::list<Noisy>::iterator it= list1.begin();
	it++, it++, it++;

	list1.splice(it,list2 );
	std::cout << "after splice " << std::endl;
	copy(list1.begin(), list1.end(), ostream_iterator<Noisy>(cout, " "));

	std::cout << "after merge " << std::endl;
	list1.merge(list3);
	copy(list1.begin(), list1.end(), ostream_iterator<Noisy>(cout, " "));
}



#endif /* STL_H_ */
