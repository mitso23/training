#ifndef TESTAPPS_ALGORITHMS_LIST_
#define TESTAPPS_ALGORITHMS_LIST_


struct Node
{
	int data;
	Node* next;
	Node* previous;
};

Node* m_head = NULL;
Node* m_tail = NULL;


/// tail 1 2 3 head
void push_front(int data)
{
	if(m_head == NULL)
	{
		m_head = (Node*)malloc(sizeof(Node));
		m_head->data = data;
		m_head->next = NULL;
		m_head->previous = NULL;
		m_tail = m_head;

		return;
	}

	Node* newNode = (Node*)malloc(sizeof(Node));

	newNode->data = data;
	newNode->next = NULL;
	m_head->next = newNode;
	newNode->previous = m_head;

	m_head = newNode;
}

/// tail 1 2 3 head
void push_back(int data)
{
	if(m_head == NULL)
	{
		m_head = (Node*)malloc(sizeof(Node));
		m_head->data = data;
		m_head->next = NULL;
		m_tail = m_head;

		return;
	}

	Node* newNode = (Node*)malloc(sizeof(Node));

	newNode->data = data;
	newNode->next = m_tail;
	m_tail->previous = newNode;

	m_tail = newNode;
	m_tail->previous = NULL;
}

void remove_back()
{
	if(m_tail == NULL)
	{
		return;
	}

	Node* temp = m_tail;
	m_tail = m_tail->next;
	m_tail->previous = NULL;

	free(temp);
}

void printList()
{
	Node* current = m_head;
	while (current != NULL)
	{
		std::cout << current->data;
		current = current->previous;
	}
	std::cout << std::endl;

}

void clearList()
{
	m_head = NULL;
	m_tail = NULL;
}








#endif
