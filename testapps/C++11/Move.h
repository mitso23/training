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

//By default it will use the move operator to get the noisy (or use compiler return value optimisation)
Noisy getNoisy()
{
	Noisy tmp;
	if (getchar() != 0)
	{
		tmp.setData(1);
		return tmp;
	}
	else
	{
		tmp.setData(2);
		return tmp;
	}
}

//This will force the move constructor to kick in
Noisy getNoisyMove()
{
	Noisy tmp;
	if (getchar() != 0)
	{
		tmp.setData(1);
		return std::move(tmp);
	}
	else
	{
		tmp.setData(2);
		return std::move(tmp);
	}
}

void assignmentFromTemporary()
{
	Noisy n;
	n.setData(9);
	//Such an assignment from a temporary will use move semantics
	n= Noisy();
	std::cout << n << std::endl;
}

class NoisyWrapper
{
private:
	Noisy ns;
};

void testNoisyWrapper()
{
#if 0
	//this will move Noisy as well
	NoisyWrapper ns;
	auto ns2= std::move(NoisyWrapper());
#endif
	//this will not move noisy, instead it will use a copy
	NoisyWrapper ns;
	auto ns2= NoisyWrapper();
}
