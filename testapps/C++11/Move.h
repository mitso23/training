#include <string>

template <class T>
void swap(T& a, T& b)
{
    T tmp(a);   // now we have two copies of a
    a = b;      // now we have two copies of b
    b = tmp;    // now we have two copies of tmp (aka a)
}

template <class T>
void swap2(T& a, T& b)
{
	T tmp(std::move(a));
	a= std::move(b);
	b= std::move(tmp);
}

//By default it will use the move operator to get the noisy
Noisy getNoisy()
{
	return Noisy();
}
