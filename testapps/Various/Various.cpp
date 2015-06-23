#include <iostream>
#include <functional>

template <typename T>
void changeValue(T a)
{
	++a;
}
class Proxy
{

public:
	Test operator () (int x)
	{
		return Test(x);
	}	
};

class Status
{

public:
	Status& operator ()(int x)
	{
		status|= x;
		return *this;
	}

private:
	int status;
};

int main(int argc, char* argv[])
{

	int x= 1;
	changeValue(x);
	std::cout << "value of x is " << x << std::endl;
	changeValue(std::ref(x));
	std::cout << "value of x is " << x << std::endl;
}
