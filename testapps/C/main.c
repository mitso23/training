#include "Arrays.h"
#include "Io.h"
#include "bithacks.h"
#include "strings.h"
#include "algorithms.h"
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

	for(int i=0; i<= 5; ++i)
	{
		printf("%d:%d\n", i, fibonacciRec(i));
	}
}



