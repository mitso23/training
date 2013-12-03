#ifndef TEMPLATES_H_
#define TEMPLATES_H_
#include <sstream>

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




#endif /* TEMPLATES_H_ */
