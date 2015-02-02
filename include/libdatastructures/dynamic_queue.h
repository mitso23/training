#ifndef QUEUE_H_
#define QUEUE_H_

#include "list.h"

#define DECLARE_QUEUE_PUSH_BACK(postfix) void queue_push_back_##postfix(postfix##List* name, __typeof__(postfix##Node::data) value) \
{ \
	list_push_back_##postfix(name, value); \
}\

#define DECLARE_QUEUE_IS_EMPTY(postfix) bool queue_is_empty_##postfix(postfix##List* name) \
{ \
	return list_is_empty_##postfix(name); \
} \

#define DECLARE_QUEUE_SIZE(postfix) const size_t queue_size_##postfix(postfix##List* list) \
{ \
	return list_size_##postfix(list); \
} \

#define DECLARE_QUEUE_POP_BACK(postfix) bool queue_pop_back_##postfix(postfix##List* name, __typeof__(postfix##Node::data)* value) \
{ \
	return list_pop_back_##postfix(name, value); \
} \

#define DECLARE_QUEUE_FUNCTIONS(type, postfix) \
		DECLARE_LIST_TYPE(type, postfix) \
		DECLARE_PUSH_BACK(postfix) \
		DECLARE_POP_BACK(postfix) \
		DECLARE_IS_EMPTY(postfix) \
		DECLARE_SIZE(postfix) \
		DECLARE_QUEUE_PUSH_BACK(postfix) \
		DECLARE_QUEUE_IS_EMPTY(postfix) \
		DECLARE_QUEUE_SIZE(postfix) \
		DECLARE_QUEUE_POP_BACK(postfix) \

#define DECLARE_QUEUE(postfix, name) \
postfix##List name= { 0 }; \


#endif /* QUEUE_H_ */
