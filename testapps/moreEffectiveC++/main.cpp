#include "Techniques.h"

#include <iostream>

class Base
{
public:
	virtual ~Base()= 0;

	virtual void getData()
	{
		std::cout << "Base class " << std::endl;
	}
};

Base::~Base()
{
	std::cout << "Deleting Base " << std::endl;
}

class Derived: public Base
{

public:

	~Derived()
	{
		std::cout << "Deleting Derive " << std::endl;
	}

	void getData() override
	{
		std::cout << "Derive class " << std::endl;
	}
};

int main(int argc, char* argv[])
{
#if 0
	auto fsa= FSA::makeFSA();
	auto fsa2= FSA2::makeFSA2();
#endif
#if 0
	//NOTE: this is not possible as destructor is protected
	//ObjectCreateOnlyOnHeap stack;
	UPNumber* number= new UPNumber(1);
	if (number->isOnHeap())
		std::cout << "On the heap" << std::endl;
#endif
#if 0
	auto_ptr<Base> ptr1(new Derived);
	if (!(ptr1 == nullptr))
		(*ptr1).getData();
	return 0;
#endif

#if 0
	std::string s1("Hello");
	char* ptr= &s1[0];
	std::string s2= s1;
	*ptr='F';
	std::cout << s1 << std::endl;
	std::cout << s2 << std::endl;
#endif

// A reference counting string implementation
#if 0
	ReferenceCountingString a("Hello");
	ReferenceCountingString b = a;
	char* ptr= &a[0];
	*ptr= 'S';

	std::cout << a << std::endl;
	std::cout << b << std::endl;
	const ReferenceCountingString d= std::string("Skata");
	ReferenceCountingString e= d;
	std::cout << d[0] << std::endl;
	std::cout << e[0] << std::endl;
#endif

#if 0
	//allocated2dArray(10, 20);
	//array1D<int, 10> arr;
	//std::cout << arr[0] << std::endl;
#endif

#if 0
	array2D<int, 2, 3> arr;
	arr[0][0]= 9;
	std::cout << arr[0][0] << std::endl;
#endif

#if 0
	MyString hese("skata");
	hese[0]= 'S';
	std::cout << hese[0] << std::endl;

	if (hese[0] == 'S')
		std::cout << "Yupii" << std::endl;

	foo(hese[0]);
#endif
}
