#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Node
{
	int data;
	struct _Node* pnext;

}Node;

//this is much slower version as the recursion ends up in a deep tree structure
unsigned long long paragontiko_rec(unsigned n)
{
	if(n == 1)
	{
		return 1;
	}
	else
	{
		return (n * paragontiko_rec(n - 1));
	}
}

unsigned long long paragontiko(unsigned int n)
{
	unsigned long long sum= 1;

	for(int i=1; i<= n; ++i)
	{
		sum= sum * i ;
	}

	return sum;
}

static Node x[] =
{
		{ 0, &x[1] },

		{ 1, &x[2] },

		{ 2, &x[3] },

		{ 3, &x[4] },

		{ 4, &x[5] },

		{ 5, NULL }
};

void init_list(Node** pphead)
{
	*pphead= malloc(sizeof(x));
	Node* phead= *pphead;

	memcpy(phead, x, sizeof(x) );
}


// 1 -> 2 -> 3 -> 4 -> 5null
void reverse_list(Node** head)
{
	Node* current= head ? *head : NULL;
	Node* previous= NULL;
	Node* next= NULL;

	while(current)
	{
		*head = current;
		next= current->pnext;

		current->pnext= previous;

		previous= current;
		current= next;
	}
}

void print_list(Node* head)
{
	while(head)
	{
		printf("%d\n", head->data);
		head= head->pnext;
	}
}

int main(int argc, char* argv[])
{

#if 0 //Array related stuff
	sizeTest();
	char* strings[10];
	enterStrings(strings, 10);
#endif

#if 0
	//this will not work as there is no implicit cast from const int* to int*
	//const int arr[]= { 1, 2 ,3 ,4 ,5 };
	//increment(arr);
	for(int i=0; i< 100000; ++i)
		paragontiko_rec(200);
#endif

	Node* head;
	init_list(&head);
	print_list(head);
	reverse_list(&head);
	print_list(head);

}



