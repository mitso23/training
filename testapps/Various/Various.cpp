#include <iostram>

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
	Proxy()(1);
	Status()(1)(2)(3);
}



