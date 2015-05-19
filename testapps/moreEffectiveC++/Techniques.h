#include <memory>
#include <iostream>
/**
*
* Virtual Constructor technique
*/
class Component
{

public:

	virtual Component* clone()= 0;
	
	Component(const Component& rhs)
	{
		x= rhs.x;
		y= rhs.y;
	}


private:
	int x;
	int y;
};


class TextComponent : public Component
{

public:
	virtual Component* clone() override
	{
		return new TextComponent(*this);
	}

	TextComponent(const TextComponent& rhs) : Component(rhs)
	{
		z= rhs.z;			
	}

private:
	int z;
};


//Handy way of getting only one object at a time

// forward declaration
class PrintJob;

class Printer 
{
public:
	void submitJob(const PrintJob& job)
	{
	}
	
	void reset()
	{
		
	}

	void performSelfTest()
	{
	}

	friend Printer& getPrinter();

private:
	Printer()
	{
	}

	Printer(const Printer& rhs)
	{
	
	}
};

//THE major drawback is that we would have only one global printer
// we couldn't do something like that getPrinter(), deletePrinter, get new printer
Printer& getPrinter()
{
	static Printer p;
	return p;
}

template <typename T>
class Counter
{
protected:
	Counter()
	{
		if (s_counter >= 1)
		{
			std::cout << "Only one object can be created " << std::endl;
		}
		else
		{
			std::cout << "Constructing ...." << std::endl;
			++s_counter;
		}
	}

private:
	static int s_counter;

};
template<typename T>
int Counter<T>::s_counter = 0;

class FSA : private Counter<FSA>
{
public:
	static std::unique_ptr<FSA> makeFSA()
	{
		return std::unique_ptr<FSA>(new FSA());
	}

	static  void destroyFSA(std::unique_ptr<FSA> fsa)
	{
		fsa.reset();
	}

	~FSA(){ std::cout << "destructing FSA: " << std::endl;}

private:
	//Prevent Inheritance
	FSA(){}
	FSA(const FSA& rhs){}

};

class FSA2 : private Counter<FSA2>
{
public:
	static std::unique_ptr<FSA2> makeFSA2()
	{
		return std::unique_ptr<FSA2>(new FSA2());
	}

	~FSA2(){ std::cout << "destructing FSA2: " << std::endl;}

private:
	//Prevent Inheritance
	FSA2(){}
	FSA2(const FSA& rhs){}

};
