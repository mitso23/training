#ifndef TESTLIST_H_
#define TESTLIST_H_
#include <libdatastructures/list.h>

DECLARE_LIST(int, mylist)

void testHeadTail()
{
	std::cout << "tail is " << mylist.listTail->data << std::endl;
	std::cout << "before tail is " << mylist.listTail->previous->data
			<< std::endl;
	std::cout << "after tail is " << mylist.listTail->next->data << std::endl;

	std::cout << "head is " << mylist.listHead->data << std::endl;
	std::cout << "before head is " << mylist.listHead->previous->data
			<< std::endl;
	std::cout << "after head is " << mylist.listHead->next->data << std::endl;
}

void displayIntList()
{
	intNode* current= mylist.listHead;
	LIST_FOR_EACH(mylist, current)
	{
		std::cout << "data: " << current->data << std::endl;
	}
}

void addElementsToListFront()
{
	for (int i = 0; i < 5; ++i)
	{
		push_front(&mylist, i);
	}
}

void addElementsToListBack()
{
	for (int i = 5; i < 10; ++i)
	{
		push_back(&mylist, i);
	}
}

void clearList()
{
	clear_list(&mylist);
}

void removeNodeTest()
{
	intNode* current= mylist.listHead;
	intNode* temp= mylist.listHead;

	LIST_FOR_EACH_SAFE(mylist, current, temp)
	{
		remove_node(&mylist, current);
	}
}




#endif /* TESTLIST_H_ */
