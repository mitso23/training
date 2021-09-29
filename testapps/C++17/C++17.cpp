#include "AutomaticTypeDeduction.h"
#include "FoldExpressions.h"
#include <iostream>
#include <sstream>
#include <atomic>
#include <array>
#include <vector>
#include <list>
#include "StructureBinding.h"
#include <iostream>
#include <type_traits>
#include "lambdas.h"
#include <utils/Noisy.h>
#include <utils/counted.h>
#include <vector>
#include "templates.h"


class skata2
{
public:
	friend std::ostream& operator<<(std::ostream& str, skata2& s)
	{
		return str << " skata2";
	}

	skata2()
	{
		std::cout << "constructor called " << std::endl;
	}

	skata2(skata2&& s)
	{
		std::cout << "rvalue method has been called" << std::endl;
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

void dummy(int x, int y, std::vector<int>&& z, const std::list<int>& w,
		skata2&& sk, std::array<int, 2> a, const std::string s,
		std::array<int, 3> arr, float ff, char c1, char c2, ObjCounter<int>&& o)
{
	std::cout << "size of the vector is " << z.size() <<  " is rvlaue: " << std::is_rvalue_reference<decltype(z)>::value << std::endl;
	z.push_back(10);
}

class MyClass
{
 public:
// no copy/move constructor defined:
	MyClass(const MyClass&) = delete;
	MyClass(MyClass&&) = delete;
};


MyClass CopyElision(MyClass x)
{
	//return x --> is not compiling
	return MyClass{};
}

//BENCHMARK_MAIN();

auto ProcessMessage(const Message& m, Counted<std::string>& s)
{
	Hashed h = static_cast<Hashed>(strHasher(m.m_name));

	switch(h)
	{
		case Hashed::one:
		{
			std::cout << "this is one " << std::endl;
		}
		break;

		case Hashed::two:
		{
			std::cout << "this is two " << std::endl;
		}
		break;

	default:
		std::cout << "SHIT" << std::endl;
	}

	s+= "1";

	return std::move(s);
}

int main(int argc, char* argv[])
{

#if 0
	//iterateMap();
	//ManipulateCustomers();
	std::map<std::string, int> coll;

	if (auto [pos, ok] = coll.insert({"Hello", 42}); ok)
	{
		std::cout << Header::s_name << std::endl;
	}

	CopyElision(MyClass{});

	auto v2 = Hashed::one;

	switch (v2)
	{
		case normalFunc("one") :
		{
			std::cout << "Holly cow" << std::endl;
		}
		break;
	}

	std::string clearText("Dimitrios");
	std::string encodedText;
	std::string decodedText;
	encodedText.reserve(9);
	decodedText.reserve(9);
	auto key = 'a';

	for(auto& c : clearText)
	{
		encodedText.push_back(c ^ key);
	}

	for(auto& c : encodedText)
	{
		decodedText.push_back(c ^ key);
	}

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

	my_is_same<std::string, std::string> m;

	int x = 1;
	int y = 2;
	std::vector<int> z = {4, 5, 6};
	std::list<int> w = {7, 8, 9};
	std::array<int, 2> a = { 10, 11 };
	std::string s = "Dimitrios";
	std::array<int, 3> arr = {9, 9, 9};
	float ff = 10.23456;
	char c1 = 1;
	char c2 = 'a';
	ObjCounter<int> objCounter;
	auto yy = std::move(skata{});

	//printArguments(x, y, z, w, skata2{}, a, s, arr, ff, c1, c2);
	//CALL(dummy, x, y, std::move(z), w, skata2{}, a, s, arr, ff, c1, c2, std::move(objCounter));

	//dummy(x, y, std::move(z), w, std::move(skata2{}), a, s, arr, ff, c1, c2, std::move(objCounter));
	//dummy(x, y, std::move(z), w, skata2{}, a, s, arr, ff, c1, c2, std::move(objCounter));

	Noisy n;
	processAndLog(n);

	std::cout << "original vector size is " << z.size() << std::endl;
	std::cout << "created: " << objCounter.counter.created << " copy constructed: "
			  << objCounter.counter.copyConstructed << " move constructed: "
			  << objCounter.counter.moveConstructed << " move assigned: "
			  << objCounter.counter.moveAssigned << std::endl;
#endif

#if 0
	Counted<std::string> str{"Hello"};
	std::vector v {1, 2, 3, 4};
	ProcessMessage(Message{"one"}, str);
	CountCalls cs {[](auto a, auto b) { return a < b;}};
	std::sort(v.begin(), v.end(), std::ref(cs));
#endif

	S h("hello");
	std::cout << asString(1.33333333344) << std::endl;
}

