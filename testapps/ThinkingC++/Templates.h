#ifndef TEMPLATES_H_
#define TEMPLATES_H_
#include <sstream>
#include <iostream>
#include <vector>

class Print
{
public:
	void copy(int dest, int source)
	{
		std::cout << "copying" << std::endl;
	}

	void execute(int dest, int source)
	{
		std::cout << "executing" << std::endl;
	}

	void print()
	{

	}

	friend ostream& operator <<(ostream& os, Print* pr)
	{
		os << "Hello I am a Print function" << endl;
		return os;
	}
};

//pointer to a member function
typedef void(Print::*memPtr)(int, int);

template<typename T>
std::string convertToString(T t)
{
	std::stringstream sstream;
	sstream << t;
	if(sstream.good())
	{
		return sstream.str();
	}
	else
	{
		return "ERROR";
	}
}

template<typename T, int size>
int asz(T(&)[size])
{
	return size;
}

template <typename T> void f(T*)
{
}

void h(void (*pf)(int*))
{

}

template <class T>
  void g(void (*pf)(T*))
{
}

template<class Seq, class T, class R>
void apply(Seq& sq, R (T::*f)()) {
  typename Seq::iterator it = sq.begin();
  while(it != sq.end()) {
    ((*it)->*f)();
    it++;
  }
}

template<class Seq, class T, class R, class A1, class A2>
void apply(Seq& sq, R (T::*f)(A1, A2), A1 a1, A2 a2) {
  typename Seq::iterator it = sq.begin();
  while(it != sq.end()) {
    ((*it)->*f)(a1, a2);
    it++;
  }
}

template<typename C>
void print(C c)
{
	typename C::iterator it;

	for(it= c.begin(); it != c.end(); ++it)
	{
		std::cout << *it;
	}
}

template<typename T, template<typename> class C >
void print2(C<T> c)
{
	//copy(c.begin(), c.end(), ostream_iterator<T>(cout, " "));
}


template<class T, template<typename, typename> class Seq>
class Mysequence : protected Seq<T*, std::allocator<T*> >
{
public:
	using Seq<T*, std::allocator<T*> >::push_back;
	using Seq<T*, std::allocator<T*> >::iterator;
	using Seq<T*, std::allocator<T*> >::begin;
	using Seq<T*, std::allocator<T*> >::end;

	template<typename R>
	void apply(R (T::*f)())
	{
		typename Seq<T*, std::allocator<T*> >::iterator it= begin();

		while(it != end())
		{
			((*it)->*f)();
			++it;
		}
	}

};

template<class T>
class Sorted: public std::vector<T>
{
	void sort()
	{
		for (int i = this->size(); i > 0; i--)
		{
			for (int j = 1; j < i; j++)
			{
				if (this->at(j - 1) > this->at(j))
				{
					T temp = this->at(j);
					this->at(j - 1) = this->at(j);
					this->at(j) = temp;
				}
			}
		}
	}
};

//partial specialization
template<class T>
class Sorted<T*>: public std::vector<T*>
{
	void sort()
	{
		for (int i = this->size(); i > 0; i--)
		{
			for (int j = 1; j < i; j++)
			{
				if (*(this->at(j - 1)) > *(this->at(j)))
				{
					T* temp = this->at(j);
					this->at(j - 1)= this->at(j);
					this->at(j)= temp;
				}
			}
		}
	}
};

//total specialization
template<>
class Sorted<char*>: public std::vector<char*>
{
	void sort()
	{
		for (int i = this->size(); i > 0; i--)
		{
			for (int j = 1; j < i; j++)
			{
				if (*(this->at(j - 1)) > *(this->at(j)))
				{
					char* temp = this->at(j);
					this->at(j - 1)= this->at(j);
					this->at(j)= temp;
				}
			}
		}
	}
};


#endif /* TEMPLATES_H_ */
