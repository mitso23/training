#include "dynamic_programming.h"



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
<<<<<<< HEAD
	int x[4][4]= { { 1, 2 ,3, 4 } , { 5, 6, 7, 8 },  { 9, 10, 11, 12,} , { 13, 14, 15, 16 } };

	printMatrix(x, 4);
	rotateMatrix90(x, 4);
	printf("\n");
	printMatrix(x, 4);
#endif

#if 0
	Tree_Node* root= NULL;
	addNode(&root, 20);
	addNode(&root, 25);
	addNode(&root, 15);
	addNode(&root, 30);
	addNode(&root, 22);
	addNode(&root, 17);

	//printPreorder(root);
	printPostOrder(root);
	//findCommonAnchestorTwoNodes(root, root->leftChild, root->leftChild->leftChild);
#endif



#if 0
	int arr[]= { 3, 4 , 5, 6 , 7, 8, 9 , 10, 11, 12, 1 , 2 };
	findMinElement(arr, sizeof(arr)/ sizeof(arr[0]));
#endif

	//printAllPermutation("ab");
#if 0
	char str[] = "hello";
	reverseString(str);
	printf("%s\n", str);
#endif

#if 0
	char str[] = "Dimitrios";
	removeDuplicatesNoStorage1(str);
	printf("%s\n", str);
#endif
	//int arr[] = { 1 , 8, 2 , 3 , 7 , 4 };
	//bubblesort(arr, 6);
	//selectionsort(arr, 6);
	//insertionSort(arr, 6);
	//for(unsigned int i=0; i< 6; ++i)
		//		printf("%d ",arr[i]);
		//printf("\n");
	//char arr[] = "Dimitrios Symonidis\0          ";
	//replaceSpaceWithPercent20(arr);

#if 0
	stack myStack;
	unsigned data;

	createStack(&myStack, 10);
	push(&myStack, 1);
	push(&myStack, 2);
	push(&myStack, 3);
	pop(&myStack, &data);
	printStack(&myStack);
#endif

#if 0
	int x = 123;
	reverseInt(&x);
#endif

	//reverseSentence("Hello World Dimitrios");
	//reverseSentence2("Hello        He is THE  ENENMY \n\n HELP GOD");
	//find_longest_non_repeative_str("abcdafdqwert");

	int arr[] = { 1, 2, 3, 4, 5};
	knapsack(arr, sizeof(arr)/sizeof(arr[0]), 7);
}



