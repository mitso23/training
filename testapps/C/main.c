#include "Arrays.h"
#include <libdatastructures/c_vector.h>
#include <stdio.h>

DECLARE_VECTOR_FUNCTIONS(int, int)
DEFINE_VECTOR(int, myVector)

//this is much slower version
unsigned long long paragontiko_rec(unsigned n)
{
	if(n == 1)
	{
		return 1;
	}
	else
	{
		return (n * paragontiko_rec(n - 1));
	}
}

unsigned long long paragontiko(unsigned int n)
{
	unsigned long long sum= 1;

	for(int i=1; i<= n; ++i)
	{
		sum= sum * i ;
	}

	return sum;
}

int main(int argc, char* argv[])
{

#if 0 //Array related stuff
	sizeTest();
	char* strings[10];
	enterStrings(strings, 10);
#endif

#if 0
	//this will not work as there is no implicit cast from const int* to int*
	//const int arr[]= { 1, 2 ,3 ,4 ,5 };
	//increment(arr);
	for(int i=0; i< 100000; ++i)
		paragontiko_rec(200);
#endif

}



