#include <iostream>


unsigned int my_atoi(const char* input)
{
	unsigned int result = 0;

	while(input && *input)
	{
		result = result*10 + (*input++ - '0');
	}

	return result;
}

int main()
{
    std::cout << sizeof(B);
    return 0;
}
