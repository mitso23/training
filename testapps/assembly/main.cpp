#include "stdio.h"

int z =1;

int calculateSum(int x, int y)
{
	return x + y;
}

class A
{
public:
	A() = default;

public:
	int x;
	int y;
};

int main(int argc, char *argv[])
{
	A a;
	calculateSum(a.x, z);
	return 0;
}
