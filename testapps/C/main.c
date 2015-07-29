#include "Arrays.h"
#include <libdatastructures/c_vector.h>
#include <stdio.h>

DECLARE_VECTOR_FUNCTIONS(int, int)
DEFINE_VECTOR(int, myVector)

int main(int argc, char* argv[])
{

#if 0 //Array related stuff
	sizeTest();
	char* strings[10];
	enterStrings(strings, 10);
#endif

	//this will not work as there is no implicit cast from const int* to int*
	//const int arr[]= { 1, 2 ,3 ,4 ,5 };
	//increment(arr);

}



