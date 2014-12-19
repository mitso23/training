#ifndef ARRAYS_H_
#define ARRAYS_H_
#include <iostream>
#include <string.h>
#include <stdio.h>

typedef int(*funct_ptr)(int, int);
#define SIZEARRAY(arr) (sizeof(arr)/sizeof(arr[0]))

int add(int a, int b);

int sub(int a, int b);

extern unsigned int test_arr[2][3];

extern funct_ptr test_arr2[2];

extern struct _alarm alarm_light_config[3][2];

void enterStrings(char**strings, unsigned size);

void sizeTest();

#endif /* ARRAYS_H_ */
