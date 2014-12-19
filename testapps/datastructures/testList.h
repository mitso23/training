#ifndef TESTLIST_H_
#define TESTLIST_H_
#include <libdatastructures/list.h>

DECLARE_LIST_FUNCTIONS(int)
DECLARE_LIST(int, mylist)

#if 0
void testHeadTail(void)
{

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
#endif



#endif /* TESTLIST_H_ */
