#include "Sorting.h"
#include "various.h"
#include "strings.h"
#include "containers.h"

#include <vector>
#include <utils/utils.h>

int main(int argc, char* argv[])
{

#if 0
	const char str[]= "Hello World";
	char str2[sizeof(str) / sizeof(str[0])] = { '\0' };
	my_strcpy(str, str2);
	printf("%s", str2);
#endif

	std::vector<int> vec{ 1, 2 ,8, 4 , 5 , 6 , 3 };
	print_cont(vec);
	auto funct= [](int value)
	{	if (value < 3)
			return true;
		else
			return false;

	};

	my_remove_if(vec.begin(), vec.end(), funct);
	print_cont(vec);
}
