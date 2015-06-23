#include <memory>
#include <iostream>
#include <set>

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


//OBJECT COUNTING METHODS//////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

//Base class for ensuring that only one object can be created at a time
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

	~FSA() { std::cout << "destructing FSA: " << std::endl; }

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
/////////////////////HEAP TRACKING METHODS//////////////////////////////////////////////////////////////////////////////////////////////
class ObjectCreateOnlyOnHeap
{
public:
	ObjectCreateOnlyOnHeap() { };

protected:
	//THis means that this object can be created only on the heap
	~ObjectCreateOnlyOnHeap() { };
};


//NOTE: THIS WILL NOT WORK for arrays and expressions like this Obj* obj= new Obj(*new Obj());
class HeapTracker
{
public:

	virtual ~HeapTracker()= 0;

	//size is probably passed in by the compiler and it represents the size of the object
	static void* operator new(size_t size)
	{
		std::cout << "my operator has been called with size " << size
				<< std::endl;

		void* addr= ::operator new(size);
		m_addresses.insert(addr);
		return addr;
	}

	bool isOnHeap()
	{
		void* ptr= dynamic_cast<void*>(this);
		if (m_addresses.find(ptr) != m_addresses.end())
		{
			std::cout << "Pointer is on the heap " << std::endl;
			return true;
		}
		else
		{
			std::cout << "Not on the heap: " << std::endl;
		}

		return false;
	}

private:
	//Don't allow clients to create an array of pointers
	static void* operator new[](size_t size);

public:
	static std::set<void*> m_addresses;
protected:
	HeapTracker()
	{
	};
};

HeapTracker::~HeapTracker()
{

}

std::set<void*> HeapTracker::m_addresses;

class UPNumber : public HeapTracker
{
public:

	UPNumber() { std::cout << "Default constructor called " << std::endl; };

	UPNumber(int data) : m_data(data) { std::cout << "Non default constructor called " << std::endl; };

	~UPNumber()
	{

	}

private:
	int m_data;
};

class UPNumberContainer
{
private:
	//IF the container class is allocated on the heap there is no way of preventing the number class
	//to be allocated on the heap
	UPNumber m_number;
};

//////SMART POINTERS/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
class auto_ptr
{
public:
	auto_ptr(T* ptr = 0) :
		m_ptr(ptr)
	{

	};

	auto_ptr(auto_ptr& rhs)
	{
		movePtr(rhs.m_ptr);
	}

	~auto_ptr()
	{
		//NOTE: Auto ptr always owns the pointer
		freeResource(m_ptr);
	}

	auto_ptr<T> operator=(auto_ptr<T>& rhs)
	{
		freeResource(m_ptr);
		movePtr(rhs.m_ptr);
		return *this;
	}

	T* operator->() const
	{
		return m_ptr;
	}

	bool operator == (void* rhs)
	{
		return rhs == m_ptr;
	}

	bool operator !()
	{
		return m_ptr == nullptr;
	}

	T& operator*()
	{
		if (!m_ptr)
			throw (nullptr);
		return *m_ptr;
	}

	inline bool isValidPtr(const T* ptr) const
	{
		return ptr != nullptr;
	}

	void movePtr(T* ptr)
	{
		m_ptr = ptr;
		resetPtr(ptr);
	}

	void resetPtr(T*& ptr)
	{
		ptr= nullptr;
	}

	void freeResource(T*& ptr)
	{
		delete ptr;
		ptr= nullptr;
	}
private:
	T* m_ptr;
};
