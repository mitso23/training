#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_


void testException() throw(int)
{
	throw(1);
}

class WrapPtr
{
public:
	WrapPtr()
	{
		ptr= new int[3];
	}

	~WrapPtr()
	{
		std::cout << "Freeing ptr" << std::endl;
		delete [] ptr;
	}

private:
	int* ptr;
};

class ArrayTest
{
public:
	static int i;
	WrapPtr ptr;

	//IF an exception is thrown during array creation destructors for the successfully created objects will be called
	ArrayTest() throw(int)
	{
		std::cout << "constructing " << i++ << std::endl;

		if (i == 3)
		{
			throw(1);
		}
	}

	~ArrayTest()
	{
		std::cout << "destructing " << i << std::endl;
	}
};

int ArrayTest::i = 0;

class X
{
public:
	class Trouble { } ;

	class Small : public Trouble { };

	class Big : public Small { };

	void f() { throw Big(); };
};


#endif /* EXCEPTIONS_H_ */
