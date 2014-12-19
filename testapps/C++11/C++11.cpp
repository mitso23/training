#include <utils/Noisy.h>
#include <utility>
#include "SmartPointers.h"

int main(int argc, char* argv[])
{
#if 0
	Noisy n1;
	n1.setData(1);
	Noisy n2;
	n2.setData(2);
	swap(n1, n2);
	std::cout << "N1 is " << n1 << " N2 is " << n2 << std::endl;
#endif

	testUniquePointer();

}

