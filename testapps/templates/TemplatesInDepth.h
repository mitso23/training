#include <type_traits>

template<int I>
class CupBoard {
public:
	void open();
	class Shelf;
	static double total_weight;
};

template<typename T>
class my_is_int {

public:
	static constexpr bool value = false;
};

template<>
class my_is_int<int> {

public:
	static constexpr bool value = true;
};

template<>
class my_is_int<unsigned int> {

public:
	static constexpr bool value = true;
};

//NOTE When defining outside of the class we need to use CupBoard<I>
template<int I>
void CupBoard<I>::open() {
	static_assert(my_is_int<int>::value == true, "I is not integral");
	std::cout << "opening" << std::endl;
}

template<typename T>
class Dynamic {
public:
	virtual ~Dynamic();  // OK: one destructor per instance of Dynamic<T>
#if 0
	template<typename T2>
	virtual void copy(T2 const&);
	// ERROR: unknown number of instances of copy()
	//        given an instance of Dynamic<T>
#endif
};

namespace XXX {
template<typename T> void f(T);
}
namespace N {
using namespace XXX;
enum E {
	e1
};
void f(E) {
	std::cout << "N::f(N::E) called\n";
}
}
void f(int) {
	std::cout << "::f(int) called\n";
}

template<typename T>
class C {
	friend void f() {

	}

	friend void f(C<T> const&) {

	}
};

// This is not compiling
#if 0
template<typename T>
class Shell {
public:
	template<int N>
	class In {
	public:
		template<int M>
		class Deep {
		public:
			virtual void f();
		};
	};
};
template<typename T, int N>
class Weird {
public:
	void case1(Shell<T>::template In<N>::template Deep<N>* p) {
		p->template Deep<N>::f();  // inhibit virtual call
	}
	void case2(Shell<T>::template In<T>::template Deep<T>& p) {
		p.template Deep<N>::f();   // inhibit virtual call
	}
};

#endif

template<typename T>
class BXT {
public:
	typedef T Mystery;
	template<typename U>		///< Forward declaration
	struct Magic;
};

template<typename T>
class DXTT: private BXT<T> {
public:
	using typename BXT<T>::Mystery;
	Mystery* p;  // would be a syntax error if not for the typename
	typename BXT<T>::template Magic<int>* x;///< Note: we need to use template after ::

};

template<typename X>
class Base {
public:
	int basefield;
	typedef int T;
};

template<>  // explicit specialization
class Base<bool> {
public:
	enum {
		basefield = 42
	};    // (2) tricky!
	void foo() {
		std::cout << "Base<bool> foo is called" << std::endl;
	}
};

template<typename T>
class DD: public Base<T> {							// dependent base
public:
	void f() {
		Base<T>::basefield = 35; // (1) problem, at this point we don't know which Base<T> we are going to use as this might be specialized
		std::cout << "basefield value is " << this->basefield << std::endl;
	}
};

template<typename T>
class B {
public:
	enum E {
		e1 = 6, e2 = 28, e3 = 496
	};

	virtual void zero(E e = e1);

	virtual void one(E&);

	virtual ~B() {

	}
};

template<typename T>
class D: public B<T> {
public:
	void f() {
		typename D<T>::E e;   // this->E would not be valid syntax

		this->zero();        // D<T>::zero() would inhibit virtuality

		one(e);              // one is dependent because its argument
	}                       // is dependent
};

/////////////////////////////////////////////////////INSTANTIATION//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
class Safe {
};

template<int N>
class Danger {
public:
	typedef char Block[N];  // would fail for N<=0
};

template<typename T, int N>
class Tricky {
public:
	virtual ~Tricky() {
	}

	void no_body_here(Safe<T> = 3);

	void inclass() {
		Danger<N> no_boom_yet;
	}

	void error() {
		Danger<0> boom;
	}
	// void unsafe(T (*p)[N]);
	T operator->();

	// virtual Safe<T> suspect();
	struct Nested {
		Danger<N> pfew;
	};

	union {
		// anonymous union
		int align;
		Safe<T> anonymous;
	};
};

///////////////////////////TYPE DEDUCTION//////////////////////////////////////////////////////////////////

//NOTE: if we pass an array then there is no decay the size of the array is preserved
template<typename T> void gByReference(T& a) {
	std::cout << "sizeofT is " << sizeof(T) << std::endl;
	a[0] = 1;
}

template<typename T>
void f1(T* a)
{
	std::cout << typeid(a).name() << std::endl;
}

template<typename E, int N>
void f2(E (&a)[N])
{
	std::cout << typeid(a).name() << std::endl;
}

template<typename T1, typename T2, typename T3>
void f3(T1 (T2::*)(T3*));

class S
{
public:
	void f(double*);
};

template <typename T>
void foo(T* )
{

}

template<typename T>
void ff(T* )
{
	std::cout << "ff(T* )" << std::endl;
}

template<typename T>
void ff(T )
{
	std::cout << "ff(T)" << std::endl;
}


template<typename T>
void ff(const T* )
{
	std::cout << "ff(const T*)" << std::endl;
}

template<>
void ff(int& s)
{
	std::cout << "ff(int& sl)" << std::endl;
}

///////////////////////////SPECIALIZATION//////////////////////////////////////////////////////////////////
template<typename T>
class Types {
  public:
    typedef int I;
};

template<typename T, typename U = typename Types<T>::I>
class SS;                     // (1)

//Full speciallization
template<>
class SS<void>
{		                 // (2)
public:
	void f();
};

//Full speciallization
template<>
class SS<char**, int>
{		                 // (2)
public:
	void f();
};

template<> class SS<char, char>; //(3) // this is a declaration

template<>
class SS<char, char> // definition for (3)
{
};

//template<> class SS<char, 0>;    // ERROR: 0 cannot substitute U

template<typename T> class TT;

template<> class TT<char**> {
  public:
    void print() const;
};
// the following definition cannot be preceded by template<>
void TT<char**>::print() const
{
    std::cout << "pointer to pointer to char\n";
}

template<typename T>
class Outside
{
public:
	template<typename U>
	class Inside
	{

	};
};

template<>
class Outside<void>
{
   // there is no special connection between the following nested class
   // and the one defined in the generic template
   template<typename U>
   class Inside
   {
   private:
	   static int count;
   };
};

template<typename T>
class Outer
{                        			// (1)
public:

	template<typename U>
	class Inner
	{                    				// (2)
	private:
		static int count;            // (3)
	};

	static int code;                 // (4)
	void print() const
	{
		std::cout << "generic";			// (5)
	}
};
template<typename T>
int Outer<T>::code = 6;              // (6)
template<typename T> template<typename U>
int Outer<T>::Inner<U>::count = 7;   // (7)

////12.4 Partial Class Template Specialization///////////////////////////////////////////////////

template<typename Y>
class Node
{

public:
	Node(const Y& data_)
	   : data(data_)
	   , next(nullptr)
	{

	}

	Y data;
	Node* next;
};

class BaseList
{

public:
	inline size_t length() const
	{
		return size;
	}

protected:
	int size = 0;

};

template<typename T>
class List : protected BaseList
{

public:
   void append(T const& data)
   {
	   if (m_head)
	   {
		   m_head = new Node<T>(data);
		   ++size;
	   }
	   else
	   {
		   Node<T>* node = new Node<T>(data);
		   node->next = m_head;
		   m_head = node;
		   ++size;
	   }
   }

   Node<T>* m_head = nullptr;
};

template<>
class List<void*> : protected BaseList
{
public:
    void append (void* p)
    {
		if (m_head)
		{
			m_head = new Node<void*>(p);
			++size;
		}
		else
		{
			Node<void*>* node = new Node<void*>(p);
			node->next = m_head;
			m_head = node;
			++size;
		}
	}
private:
    Node<void*>* m_head = nullptr;
};

template<typename T>
class List<T*> : protected BaseList
{

private:
    List<void*> impl;

public:
	void append(T* p)
	{
		impl.append(p);
	}

	size_t length() const
	{
		return impl.length();
	}
};





