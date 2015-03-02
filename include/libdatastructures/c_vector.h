/*
 * c_vector.h
 *
 *  Created on: 31 Jan 2015
 *      Author: root
 */
#ifndef C_VECTOR_H_
#define C_VECTOR_H_

#include <stdlib.h>

#ifndef DEBUG_VECTOR
#define DEBUG_VECTOR_PRINT(args) printf(args); printf("\n");
#else
#define DEBUG_VECTOR_PRINT(args)
#endif

typedef unsigned long long int vector_size_t;

#define DECLARE_VECTOR(type, prefix) \
\
typedef struct \
{ \
	__typeof__(type)* data; \
	vector_size_t length; \
	vector_size_t capacity; \
}prefix##_vector_t; \

#define DEFINE_VECTOR(prefix, name) \
	prefix##_vector_t name = { 0 }; \

#define DECLARE_VECTOR_PUSH_BACK(prefix, type) void   vector_push_back_##prefix(prefix##_vector_t* vector, type value) \
{\
	prefix##_vector_t* old_vector= (prefix##_vector_t*)malloc(sizeof(prefix##_vector_t));\
	memcpy(old_vector, vector, sizeof(prefix##_vector_t));\
\
	if (vector->length > vector->capacity) \
	{ \
		DEBUG_VECTOR_PRINT("Capacity can't be bigger than length");\
		goto __error;\
	}\
	else if (vector->capacity == 0U)\
	{\
		vector->capacity= 2;\
		vector->data= (__typeof__(vector->data))malloc(sizeof(void*) * vector->capacity);\
		\
		if (!vector->data) \
		{\
			DEBUG_VECTOR_PRINT("Failed to allocate memory");\
			goto __error;\
		}\
	}\
	else if (vector->capacity == vector->length)\
	{\
		vector->capacity*= 2; \
		__typeof__(vector->data) tmp; \
		tmp= (__typeof__(vector->data))realloc(vector->data, sizeof(void*) * vector->capacity); \
		\
		if(!tmp) \
		{ \
			DEBUG_VECTOR_PRINT("Failed to reallocate memory"); \
			goto __error;\
		}\
		vector->data= tmp; \
	} \
	\
	vector->data[vector->length]= value; \
	++vector->length; \
	\
	return; \
\
__error: \
	memcpy(vector, old_vector, sizeof(prefix##_vector_t)); \
} \

#define DECLARE_VECTOR_AT(prefix, type) type vector_at_##prefix(prefix##_vector_t* vector, vector_size_t index) \
{ \
	return vector->data[index];\
}\

#define DECLARE_VECTOR_SIZE(prefix) vector_size_t vector_size_##prefix(prefix##_vector_t* vector) \
{ \
	return vector->length; \
}\

#define DECLARE_VECTOR_CAPACITY(prefix) vector_size_t vector_capacity_##prefix(prefix##_vector_t* vector) \
{ \
	return vector->capacity; \
}\

#define VECTOR_FOR_EACH(vector, data) \
	for(vector_size_t i=0U, data=vector.data[0]; i< vector.length; data=vector.data[++i])

#define DECLARE_VECTOR_FUNCTIONS(type, prefix) \
		DECLARE_VECTOR(type, prefix) \
		DECLARE_VECTOR_PUSH_BACK(prefix, type) \
		DECLARE_VECTOR_AT(prefix, type) \
		DECLARE_VECTOR_SIZE(prefix) \
		DECLARE_VECTOR_CAPACITY(prefix) \

#endif /* C_VECTOR_H_ */
