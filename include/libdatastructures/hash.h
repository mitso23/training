#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

#define DECLARE_HASH_TYPE(value_type, key_type) \
\
typedef struct __##value_type##_##key_type##_hash_item\
{ \
	__typeof__(value_type) value; \
	__typeof__(key_type) key; \
	unsigned char present; \
	struct __##value_type##_##key_type##_hash_item* next_item;\
	struct __##value_type##_##key_type##_hash_item* parent;\
	\
}value_type##_##key_type##_hash_item;\
typedef unsigned int (*value_type##_##key_type_##_funct_ptr)(__typeof__(key_type), unsigned int size); \
\

#define DEFINE_HASH(value_type, key_type, hash_name) \
\
value_type##_##key_type##_hash_item* hash_name=NULL; \
value_type##_##key_type##_hash_item* hash_name##_end=NULL; \

#define DECLARE_HASH_CREATE(value_type, key_type) void hash_create(value_type##_##key_type##_hash_item** hash, value_type##_##key_type##_hash_item** hash_end, \
																   unsigned int size) \
{ \
	if (hash && *hash) \
	{ \
		free(hash); \
	} \
	\
	unsigned int alloc_size= size + 1; \
	*hash= (value_type##_##key_type##_hash_item*)malloc(sizeof(value_type##_##key_type##_hash_item) * alloc_size); \
	memset((void*)*hash, 0, sizeof(value_type##_##key_type##_hash_item) * alloc_size); \
	*hash_end= *hash + alloc_size;\
}\

#define DECLARE_HASH_INSERT(value_type, key_type) void hash_insert(value_type##_##key_type##_hash_item* hash, \
							__typeof__(value_type) value, __typeof__(key_type) key, value_type##_##key_type_##_funct_ptr hash_funct_ptr, unsigned int size) \
{ \
	unsigned int hashed_key= 0; \
	if (hash_funct_ptr) \
	{ \
		hashed_key= hash_funct_ptr(key, size); \
	} \
	else \
	{ \
		hashed_key=key; \
	} \
	\
	value_type##_##key_type##_hash_item item; \
	item.key= key; \
	item.value= value; \
	item.present= 1; \
	item.next_item= NULL; \
	item.parent= NULL;\
	if (hash[hashed_key].present == 0) \
	{ \
		hash[hashed_key]= item;  \
	} \
	else \
	{ \
		value_type##_##key_type##_hash_item* current= &hash[hashed_key]; \
		value_type##_##key_type##_hash_item* next= hash[hashed_key].next_item; \
		while(next) \
		{\
			if (next) \
			{ \
				current= next; \
			}\
			next= next->next_item; \
		}\
		\
		current->next_item= (value_type##_##key_type##_hash_item* )malloc(sizeof(value_type##_##key_type##_hash_item)); \
		*current->next_item= item; \
		current->next_item->parent= &hash[hashed_key]; \
	}\
}


#define DECLARE_HASH_GET_NEXT_ITEM(value_type, key_type) value_type##_##key_type##_hash_item* hash_get_next_item(value_type##_##key_type##_hash_item* hash, \
																											value_type##_##key_type##_hash_item* end, value_type* values, \
																											key_type* key) \
{ \
	value_type##_##key_type##_hash_item* current= hash; \
	value_type##_##key_type##_hash_item* next= current; \
	int found= 0; \
	\
	while(current != end) \
	{ \
		if(current->present) \
		{ \
			*values= current->value; \
			*key= current->key; \
			found= 1; \
		}\
		\
		\
		if (current->next_item) \
		{ \
			next= current->next_item;\
		} \
		else if(current->parent) \
		{\
			next= current->parent; \
			++next; \
		}\
		else \
		{ \
			++next; \
		}\
		\
		\
		if (found) \
		{ \
			return next; \
		} \
		else \
		{\
			current= next; \
		}\
	} \
	\
	\
	return NULL; \
} \

#define DECLARE_HASH_FIND(value_type, key_type) unsigned int hash_find(value_type##_##key_type##_hash_item* hash, value_type* value, key_type key, \
																	    value_type##_##key_type_##_funct_ptr generate_key, unsigned int size) \
{ \
	unsigned int hashed_key=0;\
	if(generate_key)\
	{\
		hashed_key= generate_key(key, size); \
	}\
	else\
	{\
		hashed_key= key; \
	}\
	value_type##_##key_type##_hash_item* next= &hash[hashed_key]; \
	while(next) \
	{ \
		if (next->present && next->key == key) \
		{ \
			*value= next->value; \
			return 1; \
		}\
		next= next->next_item; \
	}\
	\
	return 0; \
}\

#define DECLARE_HASH_ERASE(value_type, key_type) void hash_erase(value_type##_##key_type##_hash_item* hash, key_type key, value_type##_##key_type_##_funct_ptr generate_key, unsigned int size)\
{\
	unsigned int hashed_key= 0;\
	if(generate_key)\
	{\
		hashed_key= generate_key(key, size); \
	}\
	else\
	{\
		hashed_key= key; \
	}\
	value_type##_##key_type##_hash_item* next= &hash[hashed_key]; \
	while(next) \
	{ \
		if (next->present && next->key == key) \
		{ \
			next->present= 0x0; \
			break; \
		}\
		next= next->next_item; \
	}\
}\

#define HASH_FOR_EACH(hash, end, value, key) \
		for(__typeof__(hash) start=hash;(start= hash_get_next_item(start, end, value, key));)


#define DECLARE_HASH_FUNCTIONS(value_type, key_type) \
		DECLARE_HASH_TYPE(value_type, key_type) \
		DECLARE_HASH_CREATE(value_type, key_type) \
		DECLARE_HASH_INSERT(value_type, key_type) \
		DECLARE_HASH_GET_NEXT_ITEM(value_type, key_type) \
		DECLARE_HASH_FIND(value_type, key_type) \
		DECLARE_HASH_ERASE(value_type, key_type) \


