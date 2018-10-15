#ifndef TESTAPPS_ALGORITHMS_LIST_
#define TESTAPPS_ALGORITHMS_LIST_

#include <iostream>

struct Node
{
	int data;
	Node* next = nullptr;
	Node* previous = nullptr;
};

Node arrayPool[10000000];
static int arrPoolIdx = 0;

/* Function to insert a node at the beginging of the linked list */
void push_front(struct Node** head_ref, int new_data)
{
  /* allocate node */
  struct Node* new_node = &arrayPool[arrPoolIdx++];       //(struct Node*) malloc(sizeof(struct Node));

  /* put in the data  */
  new_node->data  = new_data;

  /* link the old list off the new node */
  new_node->next = (*head_ref);

  if (new_node->next)
  {
	  new_node->next->previous = new_node;
  }

  /* move the head to point to the new node */
  (*head_ref)    = new_node;

}

void push_back(struct Node** tail, int new_data)
{
	/* allocate node */
	struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));

	new_node->data = new_data;

	new_node->previous = *tail;

	if (new_node->previous)
	{
		new_node->previous->next = new_node;
	}

	(*tail) = new_node;
}


/* Function to print nodes in a given linked list */
void printList(struct Node *head)
{

	std::cout << "printing list " << std::endl;

	while (head != NULL)
	{
		std::cout << head->data << std::endl;
		head = head->next;
	}
}





#endif
