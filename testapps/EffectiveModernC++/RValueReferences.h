/*
 * RValueReferences.h
 *
 *  Created on: 23 Jun 2017
 *      Author: mitso23
 */

#ifndef RVALUEREFERENCES_H_
#define RVALUEREFERENCES_H_

#include <type_traits>

template <class T>
struct my_remove_reference
{
	typedef T type;
};

template <class T>
struct my_remove_reference<T&>
{
	typedef T type;
};

template <class T>
struct my_remove_reference<T&&>
{
	typedef T type;
};

template <class T, class U>
struct my_is_same
{
	bool operator()()
	{
		return false;
	}

};

template <class T>
struct my_is_same<T, T>
{
	bool operator()()
	{
		return true;
	}
};

template< class T >
typename my_remove_reference<T>::type&& my_move(T&& t )
{
	return static_cast<typename my_remove_reference<T>::type&&>(t);
}

Noisy process2()
{
	Noisy n;
	return n;
}

void process(Noisy& n)
{
	std::cout << "lvalue version called " << std::endl;
}

void process(Noisy&& n)
{
	std::cout << "rvalue version called " << std::endl;
}

template<typename T>
class my_forward
{
    typedef std::remove_reference<T>::type& type;
}

template<typename T>
class my_forward<T&&>
{
    typedef std::remove_reference<T>::type&& type;
}

template<typename T>
my_forward<T>::type forward(T&& t)
{
    return static_cast<typename my_forward<T>::type>(t);
}

template<typename T>
void logAndProcess(T&& param)
{
	process(forward<T>(param));
}

class Matrix
{

public:
	Matrix(int x, int y) : m_x(x), m_y(y)
	{
		std::cout << "constr" << std::endl;
	}

	Matrix(Matrix&& rhs) : m_x(std::move(rhs.m_x)), m_y(std::move(rhs.m_y))
	{
		std::cout << "move" << std::endl;
	}

	friend std::ostream& operator << (std::ostream& s, const Matrix& rhs)
	{
		s << "x: " << rhs.m_x << " y: " << rhs.m_y;
		return s;
	}

	Matrix& operator +=(Matrix& rhs)
	{
		std::cout << "+=" << std::endl;
		rhs.m_x = rhs.m_x + m_x;
		rhs.m_y = rhs.m_y + m_y;
		return rhs;
	}

	Matrix operator + (Matrix& rhs)
	{
		std::cout << "operator + " << std::endl;
		Matrix temp(rhs.m_x + m_x, rhs.m_y + m_y);
		return temp;
	}

	Matrix operator +=(Matrix&&rhs)
	{
		std::cout << "move: operator+=" << std::endl;
		rhs.m_x = rhs.m_x + m_x;
		rhs.m_y = rhs.m_y + m_y;
		return std::move(rhs);
	}

	Matrix operator + (Matrix&&rhs)
	{
		return std::move(rhs+=*this);
	}

private:
	int m_x;
	int m_y;
};

void testUniversalRefence()
{
	//this is universal reference
	auto&& var = process2();

	//This is rvalue reference
	Noisy&& var2 = process2();

	//This is lvalue reference
	const Noisy& var3 = process2();

	//Access the temporary
	process2().getData();
}


template<typename T>
void testTemplReference(T t)
{

}

void test_my_move()
{
	Noisy n;

	process(my_move(n));
}

/**
 * @brief default deleter class for resources that have been allocated using new
 */
template<typename T>
struct DefaultNewDeleter
{
    void operator ()(T* ptr)
    {
        if (ptr)
        {
            delete ptr;
        }
    }
};

/**
 * @brief a simple resource managing class similar to unique_ptr but without the ability of moving the resource
 */
template<typename T, typename F=DefaultNewDeleter<T> >
class ScopedPtr
{
public:
    /**
     * @brief default constructor
     */
    explicit ScopedPtr() : m_ptr(NULL)
    {

    }

    /**
     * @brief Constructor
     * @param [in] ptr the raw resource that this class is going to own and manage
     */
    explicit ScopedPtr(T* ptr) : m_ptr(ptr)
    {

    }

    /**
     * @brief Constructor
     * @param [in] ptr the raw resource that this class is going to own and manage
     * @param [in] f a custom deleter function
     */
    explicit ScopedPtr(T* ptr, F f) : m_ptr(ptr), m_callback(f)
    {

    }

    /**
     * @brief operator! implementation
     * @return true if the underlying pointer is not NULL or false if not
     */
    bool operator !() const
    {
        return !m_ptr;
    }

    /**
     * @brief implicit convertion of this class to bool
     */
    operator bool() const
    {
        return (m_ptr != NULL);
    }

    /**
     * @brief free the current resource and reassign it with the newly provided one
     * @param [in] the new pointer that this class is going to manage
     */
    void Reset(T* ptr)
    {
        m_FreeResource();
        m_ptr = ptr;
    }

    /**
     * @return the underlying raw resource
     */
    T* Get() const
    {
        return m_ptr;
    }

    /**
     * @brief restore the ownership back to the caller
     * @return the underlying raw resource
     */
    T* Release()
    {
        T* temp = m_ptr;
        m_ptr = NULL;
        return temp;
    }

    /**
     * @return the custom deleter functor
     */
    F GetDeleter() const
    {
        return m_callback;
    }

    /**
     * @brief operator* implementation
     */
    T* operator->() const
    {
        return m_ptr;
    }

    /**
     * @brief operator* implementation
     */
    T& operator*() const
    {
        return *m_ptr;
    }

    /**
     * @brief destructor
     */
    ~ScopedPtr()
    {
        m_FreeResource();
    }

    ScopedPtr(ScopedPtr&& rhs)
    	: m_ptr(nullptr)
    {
		std::cout << "move constructing the scoped pointer " << std::endl;
		Reset(rhs.Release());
	}

    ScopedPtr& operator=(ScopedPtr&& rhs)
    {
    	std::cout << "move assigning the scoped pointer " << std::endl;

    	Reset(rhs.Release());
    	return *this;
    }

private:
    /**
     * @brief free the managed resource
     */
    void m_FreeResource()
    {
        if (m_ptr)
        {
            m_callback(m_ptr);
            m_ptr = NULL;
        }
    }
private:
    /**
     * @brief disable copying
     */
    ScopedPtr(const ScopedPtr& rhs);

   /**
     * @brief disable assignment operator
     */
    ScopedPtr& operator=(const ScopedPtr&rhs);
protected:
    T* m_ptr;               /**< The raw pointer that we are managing*/
    F m_callback;           /**< Callback function for releasing the resource*/
};


ScopedPtr<int> testScopedPtrFromFunction()
{
	ScopedPtr<int> p(new int(2));

	*p = 3;

	return p;
}

ScopedPtr<Noisy> testScopedPtrFromFunctionNoisy()
{
	ScopedPtr<Noisy> p(new Noisy(1));

	return p;
}

void testScopedPtrMove()
{

#if 0
	// test move construction
	{
		ScopedPtr<int> p(new int(2));
		ScopedPtr<int> f = my_move(p);

		if (p)
		{
			std::cout << "FUCK P is not NULL" << std::endl;
			std::cout << "P= " << *p << std::endl;
		}
		else
		{
			std::cerr << "Expected P to be NULL " << std::endl;
		}

		if (f)
		{
			std::cout << "EXPECTED F not to be NULL " << std::endl;
			std::cout << "f = " << *f << std::endl;
		}
		else
		{
			std::cerr << "FUCK F IS NULL " << std::endl;
		}

	}
#endif

	//test move assignment
	{
		ScopedPtr<int> p(new int(2));
		ScopedPtr<int> f(new int(3));
		f = my_move(p);

		if (p)
		{
			std::cout << "FUCK P is not NULL" << std::endl;
			std::cout << "P= " << *p << std::endl;
		}
		else
		{
			std::cerr << "Expected P to be NULL " << std::endl;
		}

		if (f)
		{
			std::cout << "EXPECTED F not to be NULL " << std::endl;
			std::cout << "f = " << *f << std::endl;
		}
		else
		{
			std::cerr << "FUCK F IS NULL " << std::endl;
		}
	}
}

void testRemoveReference()
{

#if 0
	//This will call the lvalue reference
	Noisy n;
	process(std::forward<Noisy&>(n));
#endif

#if 0
	Noisy n;
	//this will call the lvalue version
	process(n);
	//this will call the rvalue version
	process(std::forward<Noisy>(n));

	//this will do conditional cast
	logAndProcess(n);
#endif

	//int y = 1;
	//eventually what std::mvoe does is a simple cast
	//foo(reinterpret_cast<int&&>(y));


	//auto res = my_is_same<int, int&>()();
	//std::cout << res << std::endl;
	//std::cout << std::is_same<int, my_remove_reference<int&>::type>() << std::endl;
}

#endif /* RVALUEREFERENCES_H_ */
