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
	ObjectCreateOnlyOnHeap stack;
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

	remove_if_example();
}
