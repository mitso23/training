#include "Arrays.h"

struct _alarm
{
	const char* name;
	int enabled;
};

int add(int a, int b)
{
	return a + b;
}

int sub(int a, int b)
{
	return a - b;
}

//An array of integers
unsigned int test_arr[2][3] = { { 1, 2, 3 }, { 4, 5, 6 } };

//An array of function pointers
funct_ptr test_arr2[] = { add, sub };

//An array of structs
struct _alarm alarm_light_config[2][2] =
{
[0] = { { .name= "Temperature", .enabled= 0 }, { .name= "NTP", .enabled= 0 } },
[1] = { { .name= "Temperature", .enabled= 1 }, { .name= "NTP", .enabled= 0 } }
};

//An array of pointers to string
const char arr_ptr_to_string[][10] = { "Hello", "World", "Strings  " };

void printArrStrings(char (*arr)[10])
{
	printf("arr[0]= %s\n", arr[0]);
}

void printArrStringsHackyWay(char* begin, unsigned size, unsigned numItems)
{
	for (unsigned i = 0; i < numItems; ++i)
	{
		printf("str [%d] is %s \n", i, begin);
		begin+= size;
	}
}

void PrintArrPtrToString(char** strings, unsigned size)
{
	for(unsigned i=0; i< size; ++i)
	{
		printf("str [%d] is %s \n",i, *(strings+i));
	}
}

void printArrayTest()
{
	//This is an array of pointers and it is not contiguous in memory
	// ptr= 9000, ptr[0]= 1023, ptr[1]= 4000, ptr[2]= 5678
	// [1023]= H e l l o [4000]= T h e r e [5678]= Mitse
	char* ptr[3]= { "Hello", "There", "Mitse" };

	//This is a contiguous array so in memory would look like
	// H e l l o      T h e r e         M h t s e
	// Both the address of arr and arr[0] point to the same thing
	char arr[][10]= { "Hello", "There", "Mhtse" };

	printArrStrings(arr);
	//printArrStringsHackyWay((char*)arr, 10, 3);
	PrintArrPtrToString(ptr, SIZEARRAY(ptr));

}
