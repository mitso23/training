#include "Arrays.h"
#include "Io.h"
#include "bithacks.h"
#include "strings.h"
#include "algorithms.h"
#include <libdatastructures/c_vector.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//this is much slower version as the recursion ends up in a deep tree structure
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

	//sscanfTest();
	//sprintfTest();
	//readFile();

#if 0
	int x=-1;
	int y= 1;
	printf("%d\n", isNegative(x));
	printf("%d\n", isNegative(y));

	int xx=-4;
	printf("%x, %d\n", xx, xx);
	x= x << 1;
	printf("%x, %d \n", xx, xx);
#endif

#if 0
	//this will not work as there is no implicit cast from const int* to int*
	//const int arr[]= { 1, 2 ,3 ,4 ,5 };
	//increment(arr);
	for(int i=0; i< 100000; ++i)
		paragontiko_rec(200);
#endif

#if 0
	for(int i=0; i<= 5; ++i)
	{
		printf("%d:%d\n", i, fibonacciRec(i));
	}
#endif
#if 0
	int x = 123;
	reverseInt(&x);
#endif

	//reverseSentence("Hello World Dimitrios");
	//reverseSentence2("Hello        He is THE  ENENMY \n\n HELP GOD");
	//find_longest_non_repeative_str("abcdafdqwert");

	const char* arr[2] = { "Hello", "World"};
	char arr2[2][10] = {"Hello", "World"};

	sort_array_string(arr, 2);
	sort_array_string_2(arr2, 2);
}



