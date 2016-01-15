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

void increment(int* arr)
{
	*arr= 10;
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

void printMatrix(int matrix[][4], size_t length)
{
	char hash[] = { '\n', ' ' };

	for(unsigned int j=0; j< length; ++j)
	{
		for(unsigned int i=0; i< 4; ++i)
		{
			if (matrix[j][i] < 10)
				printf("%d  %c", matrix[j][i], hash[(3-i) > 0]);
			else
				printf("%d %c", matrix[j][i], hash[(3-i) > 0]);
		}
	}
}

void swap(unsigned int* a1, unsigned int* a2)
{
	unsigned int temp= *a1;
	*a1= *a2;
	*a2= temp;
}

/// 1 2 3  			1 4 6		  6   4	  1
//  4 5 6  ---->>> 	2 5 7  --->   7	  5   2
//  6 7 8 			3 6 8		  8	  6	  3

/// 1  2  3   4
//  5  6  7   8
//  9  10 11 12
//  13 14 15 16

// 1 (j, i) -> 3 (i, 2 - j) -> 8 (2-j, 2 - i)  6(2 - j, i)
void rotateMatrix90(int matrix[][4], size_t length)
{
	unsigned top_j= 3;
	unsigned top_i= 3;
	unsigned bottom_j= 0;
	unsigned bottom_i= 0;

	unsigned int i= bottom_i;
	unsigned int j= bottom_j;
	unsigned k_max= (top_j - bottom_j)/ 2;

	for(unsigned int k=0; k<= k_max; ++k)
	{
		unsigned l_max= (top_i - bottom_i);

		for(unsigned l=0; l< l_max; ++l)
		{
			unsigned top_left = matrix[j][i];

			//copy top_left to top_right
			unsigned top_right = matrix[i][3 - j];
			matrix[i][3 - j] = matrix[j][i];

			//copy top_right to bottom_right
			unsigned bottom_right = matrix[3 - j][3 - i];
			matrix[3 - j][3 - i] = top_right;

			//copy bottom_right to bottom_left
			unsigned bottom_left = matrix[3 - i][j];
			matrix[3 - i][j] = bottom_right;

			//copy bottom_right to top_left
			matrix[j][i] = bottom_left;

			printf(
					"l_max= %u i= %u j= %u top_left= %u , top_right= %u , bottom_right= %u , bottom_left= %u \n",
					l_max, i, j, top_left, top_right, bottom_right, bottom_left);

			++i;
		}

		i= ++bottom_i;
		j= ++bottom_j;
		--top_i;
		--top_j;
	}
}

/// 1  2  3   4  			4   14  12
//  5  6  7   8  ---->>> 	3 	10	11
//  9  10 11 12 			2	6	10
//  13 14 15 16				1	2	9
void rotateMatrix270(int matrix[][3], size_t length)
{

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

void findMinElement(int* arr, unsigned size)
{
	unsigned center= 0 + size/2;

	printf("arr[0] %d mid %d arr[mid + 1]  %d size %d \n", arr[0], arr[center], arr[center + 1], size);

	if ((arr[center] < arr[0]) && (arr[center] < arr[center + 1]))
	{
		printf("Minimum element is %d \n", arr[center]);
		return;
	}
	else if (arr[center] > arr[0])
	{
		findMinElement(&arr[center], (!(size % 2)) ? (size / 2 ) : ((size / 2) + 1));
	}
	else if (arr[center] < arr[0])
	{
		findMinElement(&arr[0], (!(size % 2)) ? (size / 2 ) : ((size / 2) + 1));
	}
}
