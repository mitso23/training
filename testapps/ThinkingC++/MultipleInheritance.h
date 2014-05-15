#ifndef MULTIPLEINHERITANCE_H_
#define MULTIPLEINHERITANCE_H_

#include <fstream>
using namespace std;

class B
{
public:
	virtual void who()= 0;

	B()
	{
		std::cout << "B constructor called " << std::endl;
	}

};

class D1 : virtual public B
{
public:
	virtual void who()
	{
		std::cout << "D1" << std::endl;
	}

	D1()
	{
		std::cout << "D1 constructor called " << std::endl;
	}
};

class D2 : virtual public B
{

public:
	virtual void who()
	{
		std::cout << "D2" << std::endl;
	}

	D2()
	{
		std::cout << "D2 constructor called " << std::endl;
	}
};

class MI: public D1, public D2
{
public:
	virtual void who()
	{
		std::cout << "D1 + D2" << std::endl;

	}

	MI() : B()
	{
		std::cout << "MI constructor" << std::endl;
	}
};

ofstream out("mithis.out");

class Base1
{
	char c[0x10];
public:
	void printthis1()
	{
		out << "Base1 this = " << this << endl;
	}
};
class Base2
{
	char c[0x10];
public:
	void printthis2()
	{
		out << "Base2 this = " << this << endl;
	}
};
class Member1
{
	char c[0x10];
public:
	void printthism1()
	{
		out << "Member1 this = " << this << endl;
	}
};

class Member2 {
   char c[0x10];
public:
   void printthism2() {
     out << "Member2 this = " << this << endl;
   }
};


class MI2 : public Base1, public Base2 {
  Member1 m1;
  Member2 m2;
public:
  void printthis() {
    out << "MI this = " << this << endl;
    printthis1();
    printthis2();
    m1.printthism1();
    m2.printthism2();
  }
};

//THIS IS THE DIAMOND PROBLEM,
//in IOFILE the class has two copies of FileName
//If we use virtual inheritance IO File will have only one copy
class File
{
public:
	std::string FileName;
public:
	~File()
	{
		std::cout << "File Destructor has been called " << std::endl;
	}
};

class InputFile : public File
{
public:
	~InputFile()
	{
		std::cout << "Input File Destructor has been called " << std::endl;
	}
};

class OutputFile : public File
{
public:
	~OutputFile()
	{
		std::cout << "Output File Destructor has been called " << std::endl;
	}
};


class IOFile : public InputFile , public OutputFile
{
public:
	IOFile()
	{
		InputFile::FileName= "InputFile";
		OutputFile::FileName= "OutputFile";

		std::cout << "Input: " << InputFile::FileName << std::endl;
		std::cout << "Ouput: " << OutputFile::FileName << std::endl;

		//WE CANT CALL THIS AS THIS IS AMBIGIUS
		//std::cout << "FIle " << File::FileName;
	}

	~IOFile()
	{
		std::cout << "IO File destructor has been called " << std::endl;
	}
};

//We will use multiple inheritance to fix the broken class
class Vendor
{
public:
	virtual void v() const;
	void f() const;
	virtual ~Vendor()
	{

	}
};

class Vendor1: public Vendor
{
public:
	void v() const
	{

	}
	void f() const
	{

	}
	~Vendor1()
	{

	}
};

class MyBase
{
public:
	//make both virtual
	virtual void v() const = 0;
	virtual void f() const= 0;

	virtual ~MyBase()
	{

	}
};

class Paste1 : public MyBase, public Vendor1
{

public:
	void v() const
	{
		Vendor1::v();
	}

	void f() const
	{
		Vendor1::f();
	}

	~Paste1()
	{

	}

};

void A(const Vendor& vendor)
{

}





#endif /* MULTIPLEINHERITANCE_H_ */
