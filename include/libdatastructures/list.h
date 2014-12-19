/*
 * datastructures.h
 *
 *  Created on: Jul 6, 2014
 *      Author: dimitrios
 */
#ifndef DATASTRUCTURES_H_
#define DATASTRUCTURES_H_

#define DECLARE_LIST_TYPE(type) \
typedef struct type##_Node \
{ \
	struct type##_Node* next; \
	struct type##_Node* previous; \
	__typeof__(type) data; \
\
}type##Node; \
\
typedef struct \
{\
	type##Node* listHead; \
	type##Node* listTail; \
	size_t size; \
}type##List; \
\

#define DECLARE_LIST(type, name) \
type##List name= { 0 }; \


#define LIST_FOR_EACH(name, currentNode)\
	for(; currentNode != NULL; currentNode=currentNode->next) \

#define LIST_FOR_EACH_SAFE(name, currentNode, temp)\
	for(; currentNode != NULL, temp= currentNode->next; currentNode=temp) \


#define __remove_node(type, deleteNode) \
{ \
	type##Node* previous= deleteNode->previous; \
	type##Node* next= deleteNode->next; \
	\
	if(deleteNode == name->listTail)		\
	{\
		if (name->listTail == name->listHead) \
		{ \
			delete name->listTail; \
			name->listTail= NULL; \
			name->listHead= NULL; \
		}\
		else \
		{ \
			name->listTail= previous; \
		} \
	}\
	else if (deleteNode == name->listHead) \
	{ \
		if (name->listTail == name->listHead) \
		{ \
			delete name->listTail; \
			name->listTail= NULL; \
			name->listHead= NULL; \
		}\
		else \
		{ \
			name->listHead= next; \
		}\
	}\
	else \
	{ \
		deleteNode->previous->next= deleteNode->next; \
		deleteNode->next->previous= previous; \
		delete deleteNode; \
	} \
	\
	--name->size; \
}\

#define DECLARE_REMOVE_NODE(type) int remove_node(type##List* name, type##Node* deleteNode) \
{ \
		if (!name->listHead) \
		{ \
			return 0; \
		}\
		\
		\
		__remove_node(type, deleteNode); \
		return 1; \
}\

#define DECLARE_SIZE(type)  const size_t size(type##List* list) \
{ \
	return list->size; \
} \

#define DECLARE_IS_EMPTY(type) int is_empty(type##List* list)\
{\
	return !list->listHead ? 1 : 0; \
}\


// HEAD   MID    TAIL      NEW
// 0->  <-1->  <-2->       <-3
#define DECLARE_PUSH_BACK(type) void push_back(type##List* name, __typeof__(type##Node::data) value) \
{ \
	if (name->listHead == NULL) \
	{\
		name->listHead= new type##Node(); \
		name->listHead->data= value; \
		name->listHead->next= NULL; \
		name->listHead->previous= NULL; \
		name->listTail= name->listHead; \
	}\
	else \
	{ \
		type##Node* newNode= new type##Node();\
		newNode->data= value; 				   \
							   	   	   	   	   	\
		newNode->previous= name->listTail; 			 \
		newNode->next= NULL; 		  \
										   	   	   \
		name->listTail->next= newNode; 			\
		name->listTail= newNode;    					 \
													\
	} \
	++name->size; \
														\
}														\


#define DECLARE_POP_BACK(type) int pop_back(type##List* name, __typeof__(type##Node::data)* value) \
{\
	if (!name->listHead)\
	{ \
		return 0; \
	} \
	\
	*value= name->listTail->data; \
	__remove_node(type, name->listTail); \
	return 1; \
}\

// NEW      HEAD    MID     TAIL
// 3->    <-0->   <-1->   <-2
#define DECLARE_PUSH_FRONT(type) void push_front(type##List* name, __typeof__(type##Node::data) value) \
{\
	if (name->listHead == NULL) \
	{\
		name->listHead= new type##Node(); \
		name->listHead->data= value; \
		name->listHead->next= NULL;       \
		name->listHead->previous= NULL;    \
		name->listTail= name->listHead;    \
	}\
	else \
	{\
		type##Node* newNode= new type##Node(); \
		newNode->data= value; \
									\
		newNode->next= name->listHead; 	  \
		newNode->previous= NULL;		  \
											\
		name->listHead->previous= newNode; \
		name->listHead= newNode; \
	}\
	\
	++name->size; \
}\

#define DECLARE_CLEAR_LIST(type) void clear_list(type##List* name) \
{ \
		type##Node* current= name->listHead; \
		for(; current != NULL; ) \
		{ \
			type##Node* next= current->next; \
			__remove_node(type, current); \
			current= next; \
		}\
}\


#define DECLARE_LIST_FUNCTIONS(type) \
	DECLARE_LIST_TYPE(type) \
	DECLARE_IS_EMPTY(type); \
	DECLARE_REMOVE_NODE(type); \
	DECLARE_PUSH_BACK(type); \
	DECLARE_POP_BACK(type); \
	DECLARE_PUSH_FRONT(type); \
	DECLARE_CLEAR_LIST(type); \
	DECLARE_SIZE(type); \

#endif

/* DATASTRUCTURES_H_ */
