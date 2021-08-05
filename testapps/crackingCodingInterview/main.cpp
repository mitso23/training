#include "AutomaticTypeDeduction.h"
#include "FoldExpressions.h"
#include <iostream>


int main(int argc, char* argv[])
{
	// the answer to life, the universe, etc. in...
	auto a1 = 42;        // ... decimal
	auto a2 = 0x2A;      // ... hexadecimal
	auto a3 = 0b101010;  // ... binary

	std::cout << "a3: " << a3 << std::endl;

	std::cout << "foo result: " << foo(1, 2) << std::endl;
	std::cout << "foo result: " << foo(1.0, 2.2) << std::endl;

	auto v = make_vector<int>(1,2,3,4);
	printer(1,2,3,4);
}

