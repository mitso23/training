#include "AutomaticTypeDeduction.h"
#include "FoldExpressions.h"
#include <iostream>
#include <sstream>
#include <atomic>
#include <array>
#include <vector>
#include <list>

class skata2
{
public:
	friend std::ostream& operator<<(std::ostream& str, skata2& s)
	{
		return str << " skata2";
	}

};

class skata3
{
public:
	friend std::ostream& operator<<(std::ostream& str, const skata3& s)
	{

	}

};

class skata4
{
public:
	friend std::ostream& operator<<(const std::ostream& str, const skata4& s)
	{

	}

};


template<typename T>
void bar2(T&& t)
{
    std::cout << __PRETTY_FUNCTION__ << ' '
               << std::is_rvalue_reference<decltype(t)>::value << '\n';
}

void foo(int x, int y, int z)
{
	std::cout << __PRETTY_FUNCTION__ << ' '
	               << std::is_rvalue_reference<decltype(x)>::value << '\n';
}



void writeThread()
{

}

struct Foo
{
	int x;
	int y;
};

template<typename T, typename U>
struct my_is_same
{
	my_is_same()
	{
		bool same = std::is_same<T, U>::value;
	}
};

int main(int argc, char* argv[])
{

#if 0
	// the answer to life, the universe, etc. in...l
	auto a1 = 42;        // ... decimal
	auto a2 = 0x2A;      // ... hexadecimal
	auto a3 = 0b101010;  // ... binary

	std::cout << "a3: " << a3 << std::endl;

	std::cout << "foo result: " << foo(1, 2);
	std::cout << "foo result: " << foo(1.0, 2.2);
#endif

	class skata
	{

	};

	std::cout << "is stream insertable skata" << is_stream_insertable<skata>() << std::endl;
	std::cout << "is stream insertable skata2" << is_stream_insertable<skata2>() << std::endl;
	std::cout << "is stream insertable skata3" << is_stream_insertable<skata3>() << std::endl;
	std::cout << "is stream insertable skata4" << is_stream_insertable<skata4>() << std::endl;
	std::cout << "is stream insertable Foo" << is_stream_insertable<Foo>() << std::endl;
	std::cout << "is stl container: " << is_stl_container<std::array<int, 3>>{} << std::endl;
	std::cout << "is stl container: " << is_stl_container<std::vector<int>>{} << std::endl;
	std::cout << "is integral: " << std::is_integral<std::decay_t<int&&>>::value << std::endl;
	std::cout << "is same: " << std::is_same<uint16_t, unsigned short>::value << std::endl;
	//std::cout << "is stl array: " << is_stl_array<std::array<int, 3>> {} << std::endl;
	my_is_same<int, int> m;

	int x = 1;
	int y = 2;
	std::vector<int> z = {4, 5, 6};
	std::list<int> w = {7, 8, 9};
	std::array<int, 2> a = { 10, 11 };
	std::string s = "Dimitrios";
	printArguments(x, y, z, w, skata2{}, a, s);
}

