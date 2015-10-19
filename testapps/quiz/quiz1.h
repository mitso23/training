#ifndef QUIZ1_H_
#define QUIZ1_H_

#include <utils/Noisy.h>
#include <iostream>

void referenceToRValue()
{
	// a reference to a temporary will persist till the end of function scope
	const Noisy& n= Noisy();
}

Noisy returnReferenceToTemp()
{
	int x=1;

	if (x)
	{
		return Noisy();
	}
	else
	{
		Noisy n;
		n.setData(1);
		return n;
	}
}

void postincrementTest()
{
	int x=0;

	//this is undefined behaviour
	auto y= ++x + ++x;
	std::cout << "value of y is " << y << std::endl;
}

#if 0
//This is not allowed as there would be an infinite amount of entries in a vtable for a given class
class A
{
	  template<class T>
	  	  void describe(T) { std::cout << sizeof(T) << std::endl; }
};
#endif

//this is legal as there is one vtable per class A<int>, A<float>
template<typename T>
class A
{
	 void describe(T) { std::cout << sizeof(T) << std::endl; }
};


#endif /* QUIZ1_H_ */
