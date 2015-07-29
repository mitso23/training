#ifndef ARRAYS_H_
#define ARRAYS_H_

#include <string.h>
#include <stdio.h>

typedef int(*funct_ptr)(int, int);
//struct _alarm;

#define SIZEARRAY(arr) (sizeof(arr)/sizeof(arr[0]))

int add(int a, int b);

int sub(int a, int b);

void increment(int* arr);

//The arrays has been defined in the Arrays.h here it is being declared
extern unsigned int test_arr[2][3];

//The arrays has been defined in the Arrays.h here it is being declared
extern funct_ptr test_arr2[2];

//The arrays has been defined in the Arrays.h here it is being declared
//extern struct _alarm alarm_light_config[2][3];

// In C we loose the array size when passing an array to a function it becomes a pointer
void enterStrings(char**strings, unsigned size);

#endif /* ARRAYS_H_ */
