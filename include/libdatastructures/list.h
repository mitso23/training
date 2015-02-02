/*
 * datastructures.h
 *
 *  Created on: Jul 6, 2014
 *      Author: dimitrios
 */
#ifndef DATASTRUCTURES_H_
#define DATASTRUCTURES_H_

#define DECLARE_LIST_TYPE(type, postfix) \
typedef struct postfix##_Node \
{ \
	struct postfix##_Node* next; \
	struct postfix##_Node* previous; \
	__typeof__(type) data; \
\
}postfix##Node; \
\
typedef struct \
{\
	postfix##Node* listHead; \
	postfix##Node* listTail; \
	size_t size; \
}postfix##List; \
\

#define DECLARE_LIST(postfix, name) \
postfix##List name= { 0 }; \


#define LIST_FOR_EACH(name, currentNode)\
	for(; currentNode != NULL; currentNode=currentNode->next) \

#define LIST_FOR_EACH_SAFE(name, currentNode, temp)\
	for(; currentNode != NULL; currentNode=temp) \

#define DELETE_SAFE_NODE(postfix, name, currentNode, tmpNode) \
	tmpNode=currentNode->next; \
	list_remove_node_##postfix(name, currentNode) \

#define __remove_node(postfix, name, deleteNode) \
{ \
	postfix##Node* previous= deleteNode->previous; \
	postfix##Node* next= deleteNode->next; \
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

#define DECLARE_REMOVE_NODE(postfix) bool list_remove_node_##postfix(postfix##List* name, postfix##Node* deleteNode) \
{ \
		if (!name->listHead) \
		{ \
			return false; \
		}\
		\
		\
		__remove_node(postfix, name, deleteNode); \
		return true; \
}\

#define DECLARE_SIZE(postfix)  const size_t list_size_##postfix(postfix##List* list) \
{ \
	return list->size; \
} \

#define DECLARE_IS_EMPTY(postfix) int list_is_empty_##postfix(postfix##List* list)\
{\
	return !list->listHead ? 1 : 0; \
}\


// HEAD   MID    TAIL      NEW
// 0->  <-1->  <-2->       <-3
#define DECLARE_PUSH_BACK(postfix) void list_push_back_##postfix(postfix##List* name, __typeof__(postfix##Node::data) value) \
{ \
	if (name->listHead == NULL) \
	{\
		name->listHead= new postfix##Node(); \
		name->listHead->data= value; \
		name->listHead->next= NULL; \
		name->listHead->previous= NULL; \
		name->listTail= name->listHead; \
	}\
	else \
	{ \
		postfix##Node* newNode= new postfix##Node();\
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


#define DECLARE_POP_BACK(postfix) bool list_pop_back_##postfix(postfix##List* name, __typeof__(postfix##Node::data)* value) \
{\
	if (!name->listHead)\
	{ \
		return false; \
	} \
	\
	*value= name->listTail->data; \
	__remove_node(postfix, name, name->listTail); \
	return true; \
}\

// NEW      HEAD    MID     TAIL
// 3->    <-0->   <-1->   <-2
#define DECLARE_PUSH_FRONT(postfix) void list_push_front_##postfix(postfix##List* name, __typeof__(postfix##Node::data) value) \
{\
	if (name->listHead == NULL) \
	{\
		name->listHead= new postfix##Node(); \
		name->listHead->data= value; \
		name->listHead->next= NULL;       \
		name->listHead->previous= NULL;    \
		name->listTail= name->listHead;    \
	}\
	else \
	{\
		postfix##Node* newNode= new postfix##Node(); \
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

#define DECLARE_CLEAR_LIST(postfix) void list_clear_list_##postfix(postfix##List* name) \
{ \
		postfix##Node* current= name->listHead; \
		for(; current != NULL; ) \
		{ \
			postfix##Node* next= current->next; \
			__remove_node(postfix, name, current); \
			current= next; \
		}\
}\


#define DECLARE_LIST_FUNCTIONS(type, postfix) \
		DECLARE_LIST_TYPE(type, postfix) \
		DECLARE_IS_EMPTY(postfix); \
		DECLARE_REMOVE_NODE(postfix); \
		DECLARE_PUSH_BACK(postfix); \
		DECLARE_POP_BACK(postfix); \
		DECLARE_PUSH_FRONT(postfix); \
		DECLARE_CLEAR_LIST(postfix); \
		DECLARE_SIZE(postfix); \


#endif
/* DATASTRUCTURES_H_ */
