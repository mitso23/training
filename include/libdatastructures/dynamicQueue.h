#ifndef QUEUE_H_
#define QUEUE_H_

#include "declareListTypes.h"

#define DECLARE_QUEUE(type, name)

#define DECLARE_QUEUE_PUSH_BACK(type) void queue_push_back(type##List* name, typeof(type##Node::data) value) \
{ \
	push_back(name, value); \
}\

#define DECLARE_QUEUE_IS_EMPTY(type) bool queue_is_empty(type##List* name) \
{ \
	return is_empty(name); \
} \

#define DECLARE_QUEUE_SIZE(type) const size_t queue_size(type##List* list) \
{ \
	return size(list); \
} \

#define DECLARE_QUEUE_POP_BACK(type) bool queue_pop_back(type##List* name, typeof(type##Node::data)* value) \
{ \
	return pop_back(name, value); \
} \


#endif /* QUEUE_H_ */
