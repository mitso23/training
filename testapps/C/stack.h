#ifndef STACK_H_
#define STACK_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	unsigned top;
	unsigned size;
	unsigned int* data;

}stack;

void createStack(stack* st, unsigned size)
{
	st->data= malloc(sizeof(unsigned)*size);
	st->size= size;
	st->top= 0;
}

void destroyStack(stack* st)
{
	free(st->data);
}

int push(stack* sp, unsigned data)
{
	if (sp->top == sp->size)
		return -1;

	sp->data[sp->top++]= data;

	return 0;
}

int pop(stack* sp, unsigned* data)
{
	if (sp->top == 0)
		return -1;

	*data= sp->data[sp->top--];

	return 0;
}

void printStack(stack* sp)
{
	unsigned top= sp->top;

	while(top--)
	{
		printf("top is %d\n", top);
	}
}

#endif /* STACK_H_ */
