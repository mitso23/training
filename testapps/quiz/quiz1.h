#ifndef QUIZ1_H_
#define QUIZ1_H_

#include <utils/Noisy.h>
#include <iostream>

void referenceToRValue()
{
	// a reference to a temporary will persist till the end of function scope
	const Noisy& n= Noisy();
}

#endif /* QUIZ1_H_ */
