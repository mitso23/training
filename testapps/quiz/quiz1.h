#ifndef QUIZ1_H_
#define QUIZ1_H_

#include <utils/Noisy.h>
#include <iostream>

void referenceToRValue()
{
	// a reference to a temporary will persist till the end of function scope
	const Noisy& n= Noisy();
}

//This is equivalent of doing n % 7. will return 0,1,2,3,4,5,6,7
unsigned int fun0(unsigned int n)
{
	return n & 7;
}

//This is equivalent of doing n % 7. will return 7,6,5,4,3,2,1
unsigned int fun1(unsigned int n)
{
	return -n & 7;
}

// number * 2^l / 2^r= number * 2^(l-r)
unsigned int foo2(int number, int l, int r)
{
	return (number << l) >> r;
}

unsigned int foo3(int number)
{
	switch(number)
	{
	default:
		std::cout << number << std::endl;
	case 4:
		std::cout << number << std::endl;
		break;
	case 3:
		std::cout << number << std::endl;
		break;
	//if number is 2 it execute all the statements below it as there is no break
	case 2:
		std::cout << number << std::endl;
	case 1:
		std::cout << number << std::endl;
	case 0:
		std::cout << number << std::endl;
	}

	return 0;
}

//std::make_shared is allocating ref counter and the object in one allocation
void constructTwoObjectsContiguesInMemory()
{
#if 0
	void* ptr= operator new (sizeof(int) + sizeof(Noisy));
	void* ptr2= (char*)ptr + sizeof(int);
	int* ns1= new(ptr)int();
	Noisy* ns2= new(ptr2)Noisy();
#endif

	//This is a better way of allocating a memory contiguously for an int and a Noisy
	typedef struct
	{
		int value;
		Noisy noisy;
	}items;

	items* item= new items();
	std::cout << "struct: " << sizeof(items) << " int " << sizeof(int) << " Noisy " << sizeof(Noisy) << std::endl;
}

class A
{
public:
	A()
	{
		std::cout << "A constructed " << std::endl;
	}

	virtual void foo()
	{
		std::cout << "A:FOO" << std::endl;
	}
private:
	Noisy ns;
	};

class B : public A
{
public:
	B()
	{
		std::cout << "B constructed " << std::endl;
	}

	virtual void foo()
	{
		//This will call first the parent and then the child
		//The chain of responsibility and the decorator pattern are based on this technique
		A::foo();
		std::cout << "B:FOO" << std::endl;
	}

private:
	Noisy ns;
};


#endif /* QUIZ1_H_ */
