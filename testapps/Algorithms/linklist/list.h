#ifndef TESTAPPS_ALGORITHMS_LIST_
#define TESTAPPS_ALGORITHMS_LIST_

#include <iostream>

struct Node
{
	int data;
	Node* next = nullptr;
	Node* previous = nullptr;
};

/* Function to insert a node at the beginging of the linked list */
void push_front(struct Node** head_ref, int new_data)
{
  /* allocate node */
  struct Node* new_node =
            (struct Node*) malloc(sizeof(struct Node));

  /* put in the data  */
  new_node->data  = new_data;

  /* link the old list off the new node */
  new_node->next = (*head_ref);

  /* move the head to point to the new node */
  (*head_ref)    = new_node;
}

void push_back(struct Node** head_ref, int new_data)
{
	/* allocate node */
	struct Node* new_node =
	            (struct Node*) malloc(sizeof(struct Node));

	new_node->data = new_data;

	if (*head_ref == nullptr)
	{
		*head_ref = new_node;
		return;
	}

	auto current = *head_ref;

	while(current->next != nullptr)
	{
		current = current->next;
	}

	current->next = new_node;
}


/* Function to print nodes in a given linked list */
void printList(struct Node *node)
{

	std::cout << "printing list " << std::endl;

	while (node != NULL)
	{
		std::cout << node->data << std::endl;
		node = node->next;
	}
}





#endif
