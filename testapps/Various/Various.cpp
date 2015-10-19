#include <iostream>
#include <functional>
#include <iterator>
#include <string>
#include <utils/Noisy.h>

int main(int argc, char* argv[])
{
	int **A= new int* [10];
	A[0]= new int[5];
	A[1]= new int[6];
	A[0][0]= 10;
	A[1][0]= 20;
	int *ptr= *(++A);
	std::cout << ptr[0] << std::endl;
}
