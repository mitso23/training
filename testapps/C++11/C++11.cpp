#include <utils/Noisy.h>
#include <utility>
#include <ostream>
#include "Cpp11Notes.h"
#include "SmartPointers.h"
#include <vector>
#include <set>
#include "Move.h"
#include "enums.h"

int main(int argc, char* argv[])
{
	if (Opcode(100) == GetDevId())
	{
		std::cout << "Hurray" << std::endl;
	}

	std::set<Opcode> set;
	set.insert(Opcode(100));
	set.insert(Opcode(200));
	//DO a swap without copying data
#if 0
	Noisy n1;
	n1.setData(1);
	Noisy n2;
	n2.setData(2);
	swap(n1, n2);
	std::cout << "N1 is " << n1 << " N2 is " << n2 << std::endl;

	//&& is a new way of getting a reference to an rvalue
	Noisy&& name= getNoisy();
	name.setData(2);
#endif

	//Unique pointer
#if 0
	//testUniquePointer();
#endif

	//some C++11 features
#if 0
	auto result= getWords("/home/mitso23/training/resources/testFiles.txt");
	std::cout << result;
#endif


}

