#include "Arrays.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//The default linkage is extern (this is defined in the Array.c
void printArrayTest();

//This is defined in bithacks.c
extern int x;

//This is define in the bithacks.c
extern int countParity(unsigned int value);

int main(int argc, char* argv[])
{
	printArrayTest();
	printf("Value of x is %d",x);
	printf("Parity of the value is %d", countParity(1));
}



