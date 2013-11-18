/*
 * ipctest.cpp
 *
 *  Created on: Aug 4, 2013
 *      Author: dimitrios
 */

#include "Constructors.h"
#include "ResourceManagement.h"
#include "Designs.h"
#include "Person.h"
#include "Inheritance.h"
#include "Templates.h"

int calculate()
{
	return 0;
}

int calcStock(SmartPtr<Investment*> ptr, int x)
{
	std::cout << "Stock is " << ptr->getX() << std::endl;

	return 0;
}

class Temporary
{
public:
	Temporary(int data) :
		m_data(data)
	{
		std::cout << "constructor of temp called " << std::endl;
	}

	~Temporary()
	{
		std::cout << "destructor of temo called" << std::endl;
	}

	const int* getData()
	{
		return &m_data;
	}

private:
	int m_data;
};

void testStack()
{
	int x[100]= { 0xFF };

	std::cout << x[99] << std::endl;
}

void processMatrix(Matrix<double, 5>& mat)
{

}

int main(int argc, char* argv[])
{
	std::string tmp1("ariadni");
	TextBlock block1(tmp1);

	Factory* factory= new InvestmentFactory();

	SmartPtr<Investment*> ptr1(factory->createInvestment());
	SmartPtr<Investment*> ptr2;
	ptr2= ptr1;

	std::cout << "Stock is " << ptr1->getX() << std::endl;

	//NOTE: We first need to create the shared pointer and then call
	//calcStock as calculate can throw exception and we can leak memory
	calcStock(ptr1, calculate());
	std::cout << "Stock is " << ptr2->getX() << std::endl;

	{
		//AVOID RETURN HANLDE TO OBJECT INTERNAL EVEN IF CONST
		//IN THIS CASE WE GET DANGLE POINTER
		const int* ptr= Temporary(1).getData();
		testStack();
		std::cout << *ptr << std::endl;
	}

	try
	{
		Widgets wid;

	}catch(int e)
	{
		std::cout << "exception being caught" << std::endl;
	}

	//in order to create p we need to know the size of Person
	Person p;

	//this will call the derived version because the base one is hidden
	Derived d;
	d.mf1(1);

	IOFile file;

	LoggMsgSender<CompanyA> msgSender;
	msgSender.sendClearMsg();

	Matrix<double, 5> matFive;
	processMatrix(matFive);
	Matrix<double, 10> matTen;

	SmartPointer<Parent> pt1(new Parent());
	SmartPointer<Parent> pt2= SmartPointer<Parent>(new Child());


	MyIterator iter;
	advance<MyIterator,int>(iter, 4);

}
