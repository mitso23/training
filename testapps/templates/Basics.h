#include <vector>
#include <iostream>
#include <string>

template<typename T, unsigned int size>
class Array
{
public:
	T& operator[](unsigned int index)
	{
		return m_arr[index];
	}

private:
	T m_arr[size];
};

template <typename T, unsigned int VAL>
T addValue(const T& val)
{
	return val + VAL;
}


//In this case a temporary needs to be created so we can't return a reference
template <typename T1, typename T2>
inline T1 max (T1 const& a, T2 const& b)
{
    return a < b ? b : a;
}

//In this case a temporary needs to be created so we can't return a reference
template <typename T1, typename T2>
inline T1 max (T1 const a, T2 const b)
{
    return a < b ? b : a;
}

//In this case no temporary variable needs to be created so we can return const reference
template <typename T>
inline const T& max1(T const& a, T const& b)
{
	return a < b ? b : a;
}

//Return Values can't be determined by the compiler, but we can specify the first type and let the other to be auto determined
template <typename R, typename T>
inline const T& max2(T const& a, T const& b)
{
	return a < b ? b : a;
}

// maximum of two pointers
template <typename T>
inline T* const& max (T* const& a, T* const& b)
{
    return *a < *b ? b : a;
}


//template with a default argument
template<typename T, typename CONT=std::vector<T>>
class Stack
{
public:
	Stack()
	{
		std::cout << "Constructor" << std::endl;
	}

	void push(const T& value);

	unsigned int GetSize()
	{
		return m_vector.size();
	}

	Stack(const Stack<T>& s)
	{
		m_vector = s.m_vector;
	}

	//Even if we return by reference the client will always get it by value
	// as the = operator is called on existing objects
	Stack<T>& operator = (const Stack<T>& other)
	{
		//Stack temp(other);
		//std::swap(this, other);

		std::cout << "operator = is called " << std::endl;
	}

	//NOTE Stack<Y> is a different type from Stack<T> so only the public members are visible
	template<typename Y>
	Stack<T>& operator = (const Stack<Y>& other)
	{
		std::cout << "operator Y = is called with a size: " << other.GetSize() << std::endl;
		return *this;
	}

private:
	CONT m_vector;
};

//Total specialisation
template<>
class Stack<std::string>
{
public:
	Stack()
	{
		std::cout << "Constructor of std::string called" << std::endl;
	}

	void push(const std::string& value);

private:
	std::vector<std::string> m_vector;
};

#include <list>
//Total specialisation
template<>
class Stack<std::string, std::list<std::string>>
{
public:
	Stack()
	{
		std::cout << "Constructor of std::string called" << std::endl;
	}

	void push(const std::string& value);

private:
	std::vector<std::string> m_vector;
};



//Partial specialisation
template<typename T>
class Stack<T*>
{
	Stack()
	{
		std::cout << "Constructor of T* called" << std::endl;
	}

	void push(const T* value)
	{

	}

	std::vector<T*> m_vector;
};

using intStack = Stack<int>;

template<typename T1, typename T2=int>
class MyClass
{

};

template<typename T1>
class MyClass<T1, int>
{
public:
	MyClass()
	{
		std::cout << "MyClass<T1, int>" << std::endl;
	}
};

template<typename T>
class MyClass<T, T>
{
public:
	MyClass()
	{
		std::cout << "MyClass<T, T>" << std::endl;
	}
};

template<>
class MyClass<int, int>
{
public:
	MyClass()
	{
		std::cout << "MyClass<int, int>" << std::endl;
	}
};

template<typename T>
class MyClass<int, T>
{
public:
	MyClass()
	{
		std::cout << "MyClass<int, T>" << std::endl;
	}
};


// a template of a template
template <typename T,
          template <typename ELEM,
                    typename = std::allocator<ELEM>>
                    class CONT = std::vector>
class Stack2 {
  private:
    CONT<T> elems;        // elements
  public:
    void push(T const&);  // push element
    void pop();            // pop element
    T top() const;         // return top element
    bool empty() const {   // return whether the stack is empty
        return elems.empty();
    }
    // assign stack of elements of type T2
    template<typename T2,
             template<typename ELEM2,
                      typename = std::allocator<ELEM2>
                      >class CONT2>
    Stack2<T,CONT>& operator= (Stack2<T2,CONT2> const&);
};

// a template of a template
template <typename T, template<typename ELEM> class CONT>

class Stack3 {
  private:
    CONT<T> elems;        // elements
  public:
    void push(T const&);  // push element
    void pop();            // pop element
    T top() const;         // return top element
    bool empty() const {   // return whether the stack is empty
        return elems.empty();
    }

};


