#ifndef TEMPLATES_H_
#define TEMPLATES_H_

#include<typeinfo>

template<typename IterT>
void workWithIterator(IterT iter)
{
	//iterator traits hold information about the iterator type
	typedef typename std::iterator_traits<IterT>::value_type valueType;

	valueType temp(*iter);
}

class CompanyA
{
public:

	void sendCleartext(const std::string& msg)
	{

	}
	void sendEncrypted(const std::string& msg);

};

class CompanyB
{
public:

	void sendCleartext(const std::string& msg);
	void sendEncrypted(const std::string& msg);

};

class CompanyZ
{
public:
	void sendEncrypted(const std::string& msg)
	{

	}
};


class MsgInfo
{
};

template<typename Company>
class MsgSender
{
public:

	void sendClear(const MsgInfo& info)
	{
		std::string msg;

		Company c;
		c.sendCleartext(msg);
	}
};

//THIS IS TOTAL SPECIALISATION
template<>
class MsgSender<CompanyZ>
{
	void sendSecret()
	{

	}
};

template<class Company>
class LoggMsgSender: public MsgSender<Company>
{
public:
	void sendClearMsg()
	{

		MsgInfo info;
		//COMPILERES REFUSE TO LOOK TO BASE CLASS UNLESS TOLD
		this->sendClear(info);
	}
};

					//THIS WILL RESULT IN CODE BLOAD BUT IS FAST AS IT IS CONSTANT
template<typename T /*, size_t n*/>
class MatrixBase
{
protected:

	MatrixBase(size_t size) :
		m_size(size)
	{

	}

	void invert()
	{

	}

private:
	size_t m_size;
};

template<typename T, size_t n>
class Matrix : private MatrixBase<T>      //PRIVATE INHERITANCE AS THIS IS NOT IS-A RELATIONSHIP
{
public:
	//AVOID NAME HIDING
	using MatrixBase<T>::invert;

	Matrix() : MatrixBase<T>(n)
	{

	}

	//THIS FUNCTION WILL BE INLINED
	void invert()
	{
		this->invert();
	}

};

class Parent
{
private:
	int x;
};

class Child : public Parent
{

};

template<typename T>
class SmartPointer
{
public:
	explicit SmartPointer(T* ptr) :
		m_ptr(ptr)
	{

	}

	//COPY CONSTRUCTOR
	SmartPointer(const SmartPointer& other) :
		m_ptr(NULL)
	{

	}

	//GENERALISED COPY CONSTRUCTOR
	template<typename U>
	SmartPointer(const SmartPointer<U>& other)
	{
		m_ptr=(U*)other.get();
	}

	T* get() const
	{
		return m_ptr;
	}

private:
	T* m_ptr;
};

struct input_iterator_tag {};

struct output_iterator_tag {};

struct forward_iterator_tag: public input_iterator_tag {};

struct bidirectional_iterator_tag: public forward_iterator_tag {};

struct random_access_iterator_tag: public bidirectional_iterator_tag {};


template<typename Iter>
struct iterator_trait
{
	// the iterator_category for type IterT is whatever IterT says it is;
	typedef typename Iter::iterator_category iterator_category;
};

template<typename IterT>               // partial template specialization
struct iterator_trait<IterT*>         // for built-in pointer types

{
  typedef random_access_iterator_tag iterator_category;

};

struct MyIterator
{
	typedef input_iterator_tag iterator_category;
};

void doAdvance(input_iterator_tag inputIter)
{
	std::cout << "advancing input iterator" << std::endl;
}

void doAdvance(output_iterator_tag outputIter)
{
	std::cout << "advancing output iterator" << std::endl;
}

template<typename IterT, typename DistT>
void advance(IterT& iter, DistT d)
{
	typename iterator_trait<IterT>::iterator_category iterCategory;
	doAdvance(iterCategory);

#if 0
  //BAD WAY OF DOING IT :)
  if (typeid(typename iterator_trait<IterT>::iterator_category) ==
     typeid(input_iterator_tag))
  {
	  std::cout << "Input iterator" << std::endl;
  }
  else
  {

  }
#endif

}

template <unsigned n>
struct Factorial
{
	enum { value= n * Factorial<n-1>::value };
};

template<>
struct Factorial<0>
{
	enum { value=1 };
};

#endif /* TEMPLATES_H_ */
