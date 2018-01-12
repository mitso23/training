#include <iostream>
#include <limits>

int main(int argc, char* argv[])
{

#if 0
	unsigned char x;
	unsigned char y = 190;
	unsigned char z = 3;

	x = y + z;
	if (std::numeric_limits<unsigned char>::max() - y < z)
	{
		std::cout << "overflow " << std::endl;
	}

	std::cout << (unsigned)x << std::endl;
#endif

#if 0
	//This is slow as the compiler need to do two if (a == 0) and if(b==0)
	bool a, b;
	bool z = a && b;
	return 0;
#endif

	unsigned int a = 0;
	unsigned int b = 0;
	auto z = a & b;

}
