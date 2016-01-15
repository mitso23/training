#include <vector>
#include <iostream>

//While auto strips off all the specifiers
//decltype gives you the full type of an object
template<typename Container, typename Index>
auto getValue(Container c, Index i) -> decltype(c[i])
{
	decltype(c[i]) y = c[i];
	return y;
}

int main(int argc, char* argv[])
{
	std::vector<int> x = { 1, 2 };
	std::cout << getValue(x, 0) << std::endl;
}
