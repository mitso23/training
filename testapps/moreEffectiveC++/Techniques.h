#include<utils/RCObjects.h>

#include <memory>
#include <iostream>
#include <set>
#include <string>
#include <map>

////////////////////////////////////////////////REF COUNTING OBJECTS/////////////////////////////////////////////////////////////////////

#define ASSIGN \
	m_string= rhs.m_string; \
	m_refCount= rhs.m_refCount; \


//A very naive implementation
class ReferenceCountingString
{

public:
	ReferenceCountingString() :
		m_string(nullptr)
	{

	}

	ReferenceCountingString(std::string&& str) :  m_string (new std::string(str)), m_refCount(new RefCount())
	{
		incRefCount();
	}

	ReferenceCountingString(const ReferenceCountingString& rhs)
	{
		ASSIGN;
		incRefCount();
	}

	ReferenceCountingString& operator=(const ReferenceCountingString& rhs)
	{
		if (this == &rhs )
		{
			return *this;
		}

		decRefCount();

		ASSIGN;

		incRefCount();

		return *this;
	}

	friend std::ostream& operator << (std::ostream& stream, const ReferenceCountingString& str)
	{
		return stream << "value: " << ((str.m_string) ? *str.m_string : "null") << " id " << str.m_refCount->m_refCount;
	}

	~ReferenceCountingString()
	{
		decRefCount();
	}


	char& operator[](int index)
	{
		if (getRefCount() > 1)
		{
			//We need to perform a deep copy of the string before returning it
			std::string newString(*m_string);
			decRefCount();

			m_string= new std::string(std::move(newString));
			m_refCount= new RefCount();
			incRefCount();
		}

		return getCharacter(index);
	}

	const char& operator[](int index) const
	{
		return (const_cast<ReferenceCountingString&>(*this)).getCharacter(index);

	}

private:

	char& getCharacter(int index)
	{
		return (*m_string)[index];
	}

	void incRefCount()
	{
		++m_refCount->m_refCount;
	}

	size_t getRefCount() const
	{
		return m_refCount->m_refCount;
	}

	void decRefCount()
	{
		if (m_refCount == 0)
			return;

		if(--m_refCount->m_refCount == 0)
		{
			std::cout << "destroying " << *this << std::endl;
			delete m_string;
			delete m_refCount;
		}
	}

	std::string* m_string;
	struct RefCount
	{
		RefCount() : m_refCount(0)
		{

		}

		size_t m_refCount;
	};

	RefCount* m_refCount;

};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 *
 * Virtual Constructor technique
 */
class Component {

public:

	virtual Component* clone()= 0;

	Component(const Component& rhs) {
		x = rhs.x;
		y = rhs.y;
	}

private:
	int x;
	int y;
};

class TextComponent: public Component {

public:
	virtual Component* clone()override
	{
		return new TextComponent(*this);
	}

	TextComponent(const TextComponent& rhs) :
		Component(rhs) {
		z = rhs.z;
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
	void submitJob(const PrintJob& job) {
	}

	void reset() {

	}

	void performSelfTest()
	{
	}

	friend Printer& getPrinter(const std::string& name)
	{
		static Printer p(name);
		return p;
	}

private:
	Printer(const std::string& name)
	{
		std::cout << "Printer constructor called ";
	}
};

//Base class for ensuring that only one object can be created at a time
template<typename T>
class Counter {
protected:
	Counter() {
		if (s_counter >= 1) {
			std::cout << "Only one object can be created " << std::endl;
		} else {
			std::cout << "Constructing ...." << std::endl;
			++s_counter;
		}
	}

private:
	static int s_counter;

};
template<typename T>
int Counter<T>::s_counter = 0;

class FSA: private Counter<FSA> {
public:
	static std::unique_ptr<FSA> makeFSA() {
		return std::unique_ptr<FSA>(new FSA());
	}

	static void destroyFSA(std::unique_ptr<FSA> fsa) {
		fsa.reset();
	}

	~FSA() {
		std::cout << "destructing FSA: " << std::endl;
	}

private:
	//Prevent Inheritance
	FSA() {
	}
	FSA(const FSA& rhs) {
	}

};

class FSA2: private Counter<FSA2> {
public:
	static std::unique_ptr<FSA2> makeFSA2() {
		return std::unique_ptr<FSA2>(new FSA2());
	}

	~FSA2() {
		std::cout << "destructing FSA2: " << std::endl;
	}

private:
	//Prevent Inheritance
	FSA2() {
	}
	FSA2(const FSA& rhs) {
	}

};
/////////////////////HEAP TRACKING METHODS//////////////////////////////////////////////////////////////////////////////////////////////
class ObjectCreateOnlyOnHeap {
public:
	ObjectCreateOnlyOnHeap() {
	}
	;

protected:
	//THis means that this object can be created only on the heap
	~ObjectCreateOnlyOnHeap() {
	}
	;
};

//NOTE: THIS WILL NOT WORK for arrays and expressions like this Obj* obj= new Obj(*new Obj());
class HeapTracker {
public:

	virtual ~HeapTracker()= 0;

	//size is probably passed in by the compiler and it represents the size of the object
	static void* operator new(size_t size) {
		std::cout << "my operator has been called with size " << size
				<< std::endl;

		void* addr = ::operator new(size);
		m_addresses.insert(addr);
		return addr;
	}

	bool isOnHeap() {
		void* ptr = dynamic_cast<void*> (this);
		if (m_addresses.find(ptr) != m_addresses.end()) {
			std::cout << "Pointer is on the heap " << std::endl;
			return true;
		} else {
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
	HeapTracker() {
	}
	;
};

HeapTracker::~HeapTracker() {

}

std::set<void*> HeapTracker::m_addresses;

class UPNumber: public HeapTracker {
public:

	UPNumber() {
		std::cout << "Default constructor called " << std::endl;
	}
	;

	UPNumber(int data) :
		m_data(data) {
		std::cout << "Non default constructor called " << std::endl;
	}
	;

	~UPNumber() {

	}

private:
	int m_data;
};

class UPNumberContainer {
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

	}
	;

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

	bool operator ! ()
	{
		return m_ptr == nullptr;
	}

	T& operator*()
	{
		if (!m_ptr)
			throw(nullptr);
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
		ptr = nullptr;
	}

	void freeResource(T*& ptr)
	{
		delete ptr;
		ptr = nullptr;
	}
private:
	T* m_ptr;
};

////////////////////////////////////////////PROXY CLASSES/////////////////////////////////////////////////////////////////////////

//NOTE: Array1D acts like a proxy class in this case
template<typename T, size_t size>
class array1D
{

public:
	array1D()
	{
		m_data= new T[size];
	}

	T& operator [](unsigned int index)
	{
		//assert(index < size);
		return m_data[index];
	}

	template <typename T>
	array1D_VIEW<T>& operator+=(array1D<T, size>& as, ::size_t increment)
	{
	   as.ptr += increment;
	   as.len -= increment;
	   // We can now log if len < increment
	   return array1D_VIEW;
	}

private:
	T* m_data;
};

template<typename T, size_t xSize, size_t ySize>
class array2D
{
public:
	array2D()
	{
		m_array2D= new array1D<T, xSize>[ySize];
	}

	array1D<T, xSize>& operator [](unsigned int index)
	{
		return m_array2D[index];
	}

private:
	array1D<T, xSize>* m_array2D;
};

void allocated2dArray(unsigned int xSize, unsigned int ySize)
{
	int** ptr= new int*[xSize];

	for(unsigned i=0; i< xSize; ++i)
	{
		ptr[i]= new int[ySize];
	}

	ptr[0][0]= 1;
	std::cout << " &ptr " << &ptr << " ptr " << ptr << " *ptr " << *ptr << " **ptr " << **ptr << std::endl;
	//ptr[0][0]= 1;
}

void foo(char& c)
{

}

class MyStringProxy
{
public:
	MyStringProxy(std::string& str, const int index) : m_str(str), m_index(index)
	{

	}

	//read only operations
	operator char() const
	{
		return m_str[m_index];
	}

#if 0
	//this is already problematic as we can no longer distinguish reads/from writes so it should be
	// prohibited
	operator char&()
	{
		return m_str[m_index];
	}
#endif

	//write only
	MyStringProxy& operator = (char c)
	{
		m_str[m_index]= c;
		return *this;
	}


private:
	std::string& m_str;
	const int m_index;
};

class MyString
{
public:

	MyString(const std::string& str) : m_string(str) { };

	MyStringProxy operator[](int index)
	{
		//for the time being lets leak the memory
		return MyStringProxy(m_string, index);
	}

	friend std::ostream& operator << (std::ostream& stream, const MyString& str)
	{
		return stream << str.m_string;
	}

private:
	std::string m_string;
};


