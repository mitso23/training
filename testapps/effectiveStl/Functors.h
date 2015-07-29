#ifndef FUNCTORS_H
#define FUNCTORS_H


//NOTE: A class that wraps a reference and stores it as a pointer
template<typename T>
class RefWrapper
{

public:
	RefWrapper(T& ref) : m_ref(&ref) { };

	operator T& () { std::cout << "operator T& called " << std::endl; return *m_ref; };

	T* m_ref;
};

template <typename T>
RefWrapper<T> ref_wrapper(T ref)
{
	return RefWrapper<T>(ref);
}

void change(int& x)
{
	x= 10;
}


//A class that wraps member function pointers and functions to functions objects
// normal functions like void fun(a) use ptr_fun
// member functions for containers with pointers use mem_fun
// member functions for normal containers use mem_fun_ref
template <typename T>
class my_mem_fun
{
public:
	my_mem_fun(bool (T::*f)()) : m_funct(f)
	{

	}

	bool operator ()(T& obj)
	{
		return (obj.*m_funct)();
	}

private:
	bool (T::*m_funct)();
};

template<typename T>
void proxy(T x)
{
	change(x);
}

//A template class can have virtual functions
template<typename T>
class BPFC
{
public:
	virtual T test()
	{
		std::cout << "Testing" << std::endl;
		return -1;
	}
};

//The functor objects are passed always by value so the predicates need to be pure (don't rely on any state)
//The functor objects should be adaptable have typedefs for argument types, return types e.t.c normally inherit from unaray or binary_function
//never specialise stl containers like std::less<int> in the stl namespace std less should always use operator < for sorting

#endif
