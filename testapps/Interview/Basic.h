#ifndef INTERVIEW_H
#define INTERVIEW_H

#include <utils/utils.h>
#include <list>

class A
{
public:
    A(int n = 2) : m_i(n) { std::cout << "A constructor called mi: " << m_i << std::endl;  }

    ~A() { std::cout << "A destructor called mi: " << m_i << std::endl; }

protected:
    int m_i;
};

class B : public A
{
public:
	//B will first call A() default constructor;
    B(int n) : m_a1(m_i + 1), m_a2(n)
    {
    	std::cout << "B is constructed mi: " << m_i << std::endl;
    }

public:
    B(const B& rhs)
    {
    	std::cout << "B copy constructor called: " << std::endl;
    }

    B(const B&& rhs)
    {
    	std::cout << "B move constructor called: " << std::endl;
    }

    ~B()
    {
        std::cout << "B destructor called: " << m_i << std::endl;
        --m_i;
    }

private:
    A m_a1;
    A m_a2;
};

class AA
{
public:

	//We need to provide our own version of swap as the std swap would do A1=A2 and would eventually call our assignemnt operator
	friend void swap(AA& rhs, AA& lhs)
	{
		std::cout << "AA swap has been called " << std::endl;
		std::swap(rhs.m_ptr, lhs.m_ptr);
		std::swap(rhs.m_size, lhs.m_size);
	}

	explicit AA(unsigned int size) : m_size(size), m_ptr(new int(m_size))
	{
		std::cout << "AA constructor called " << std::endl;
	}

	AA(const AA& rhs) : m_size(rhs.m_size), m_ptr(nullptr)
	{
		std::cout << "AA copy constructor called " << std::endl;

		AA temp(m_size);
		swap(temp, *this);
	}

	AA& operator = (const AA& rhs)
	{
		std::cout << "AA assignment operator called: " << std::endl;

		AA temp(rhs);
		swap(temp, *this);

		return *this;
	}

	~AA()
	{
		std::cout << "AA destructor called" << std::endl;
		if (m_ptr)
			delete m_ptr;

		m_size= 0;
	}

private:
	unsigned int m_size;
	int* m_ptr;

};

class BB : public AA
{

public:
	explicit BB(unsigned int size) : AA(size)
	{
		std::cout << "BB constructor called " << std::endl;
	}

	BB(const BB& rhs) : AA(rhs), m_i(0)
	{
		std::cout << "BB copy constructor called " << std::endl;
	}

	BB& operator = (const BB& rhs)
	{
		AA::operator =(rhs);
		return *this;
	}

private:
	int m_i;
};


class Base1
{

public:
	virtual void foo()= 0;

	void g(int x)
	{
		std::cout << "Base 1 g " << std::endl;
	}

public:
	int m_base1;
};

class Base2: public Base1
{
public:
	virtual void foo()
	{
		std::cout << "Base 2 foo " << std::endl;
	}

	void g(float x)
	{
		std::cout << "Base 2 g " << std::endl;
	}
public:
	int m_base2;
};

// Base 3 will inherit the vtable from Base2;
class Base3 : public Base2
{
public:
	int m_base3;
};

class EmptyClass
{

};

class EmptyClass2 : public EmptyClass
{

};


//First: A constructor is called
//Second: m_a1 is instantiated
//Third:  m_a2 is constructed
//Finally:  B constructor is instantiated
void testConstructionDestructionOrder()
{
	//This will first create a temporary using explicit constructor conversion(B(5))
	B b= 5;
}

void testCopyAssignementOperators()
{
	BB b(5);
	BB c(10);
	c=b;
}

void testPolymorphism()
{
	Base1* b= new Base3();
	b->foo();

	std::cout << "Address of Base1 is " << &b->m_base1 << std::endl;
	std::cout << "Address of Base2 is " << &dynamic_cast<Base2*>(b)->m_base2 << std::endl;
	std::cout << "Address of Base3 is " << &dynamic_cast<Base3*>(b)->m_base3 << std::endl;

	std::cout << "sizeof Base 1: " << sizeof(Base1) << std::endl;
	std::cout << "sizeof Base 2: " << sizeof(Base2) << std::endl;
	std::cout << "sizeof Base 3: " << sizeof(Base3) << std::endl;
	std::cout << "sizeof Base 3 object is: " << sizeof(*dynamic_cast<Base3*>(b)) << std::endl;

	std::cout << "size of Empty class is " << sizeof(EmptyClass) << std::endl;
	std::cout << "size of Empty2 class is " << sizeof(EmptyClass) << std::endl;
}

#endif /* INTERVIEW_H_ */
