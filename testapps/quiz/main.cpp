#include "quiz1.h"

int main(int argc, char* argv[])
{
<<<<<<< HEAD
	//referenceToRValue();
	//std::cout << "After RValue to reference " << std::endl;
	//const Noisy& n2= returnReferenceToTemp();
	//std::cout << "Got a reference to Rvalue" << std::endl;

	postincrementTest();
=======
#if 0
	referenceToRValue();
	std::cout << "After RValue to reference " << std::endl;
#endif

#if 0
	for(unsigned int i=0; i< 255; ++i)
	{
		int x= fun0(i);

		if (x)
			std::cout << x << std::endl;
	}
#endif

#if 0
	for (unsigned int i = 0; i < 255; ++i)
	{
		int x = fun1(i);
		std::cout << x << std::endl;
	}
#endif

	//constructTwoObjectsContiguesInMemory();

#if 0
	//Both objects will have a vtable +4bytes increase in size
	A* aa= new A();
	A* a= new B();
	a->foo();
	std::cout << "aa: " << sizeof(*aa) << " a: " << sizeof(*a) << std::endl;
#endif

>>>>>>> 2726e206283f4280df70166911d3511b74d08db2
}
