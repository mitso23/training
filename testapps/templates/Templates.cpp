#include "Basics.h"
#include "TemplatesInDepth.h"
#include "PolicyTypeTraits.h"
#include "TypeFunctions.h"
#include "TemplatesInheritance.h"
#include "Metaprograms.h"
#include "TypeErasure.h"
#include "simple_function.h"
#include "TypeClassification.h"
#include "SmartPointers.h"
#include "Tuples.h"
#include "Expected.h"

#include <iostream>
#include <algorithm>
#include <functional>
#include <list>
#include <string.h>
#include <tuple>
#include <type_traits>


struct X
{
	int x;
	int y;
};

/**Separate the header from implementationl */
template<typename T,
		template<typename ELEM, typename = std::allocator<ELEM>>
		class CONT>

void Stack2<T, CONT>::push(const T&)
{

}

struct MyType
{
    int foo(int x, int y)
    {
        return x + y;
    }
};

void foo(int x)
{
	std::cout << "calling foo: " << std::endl;
}

void foo1(const int& x)
{

}

template<typename T, T v>
struct my_integral_constant
{
	static constexpr T value = v;
	typedef T value_type;
	typedef my_integral_constant type;
	constexpr operator value_type() const noexcept {return value;};
};

template<typename T>
struct HasContiguousStorage: public std::false_type{};

template<typename T>
struct HasContiguousStorage<std::vector<T>>: public std::true_type{};
// Specialize others

struct TestFuture
{
	TestFuture(int& _x) : x(_x)
	{

	}
	int& x;
};

template<typename T, typename U>
struct my_is_same
{
	static bool constexpr result = false;
};

template<typename T>
struct my_is_same<T,T>
{
	static bool constexpr result = true;
};

template<typename T>
struct my_is_same<T,const T>
{
	static bool constexpr result = true;
};

int main(int argc, char* argv[])
{
	std::cout << my_is_same<int, const int>::result << std::endl;

#if 0
	int x = 1;
	TestFuture f1(x);
	TestFuture f2 = std::move(f1);
	TestFuture f3 = f2;

	x = 23;
	std::cout << "f1: " << f1.x << " f2: " << f2.x << " f3: " << f3.x << std::endl;
#endif

#if 0
	my_integral_constant<int, 1> i;
	my_integral_constant<unsigned, 1> u;

	std::cout << std::is_same<my_integral_constant<int, 1>::type, my_integral_constant<intl, 1>::type>::value << std::endl;
#endif

#if 0
	// They all generate the same code, so no code bloating
	Array<int, 3> arr;
	Array<int, 4> arr2;
	Array<char, 4> arr3;
	arr[0] = 1;
	arr[2] = 8;
	arr[3] = 5;

	std::cout << arr[0] << std::endl;
#endif

#if 0
	int* ptr1 = new int(2);
	int* ptr2 = new int(3);

	std::cout << ::max(ptr1, ptr2) << std::endl;
#endif

#if 0
	Stack<int> s1;
	s1.push(1);
	Stack<int> s2 = s1;
	std::cout << "s2: " << s2.GetSize() << "s1: " << s1.GetSize() << std::endl;
#endif

#if 0
	MyClass<int, int> m;
	MyClass<float> m2;
#endif

#if 0
	std::vector<int> src = { 1, 2, 3 };
	std::vector<int> dest;
	auto l = [](const int& val, const int adder)
	{
		return val + 5;
	};

	std::transform(src.begin(), src.end(), std::back_inserter(dest), std::bind(l, std::placeholders::_1, 5));
	//std::transform(src.begin(), src.end(), std::back_inserter(dest), addValue<int, 5>);
	for (auto& value : dest)
		std::cout << value << std::endl;
#endif

#if 0
	Stack<int> s1;
	Stack<int> f1;
	Stack<std::string, std::list<std::string>> str1;
	s1 = f1;
#endif

#if 0
	InitOfPodTypes<int> podType;
	std::cout << podType.t << std::endl;
#endif

#if 0
	ref("Hello");
	nonref("Hello non ref");
	std::string s("Hello world string");
	ref(s);
#endif

#if 0
	int arr[3] = { 1, 2, 3 };
	int arr2[4] = { 3, 5, 6, 7 };

	if (max(arr, arr2))
	{
		std::cout << "arr is greater" << std::endl;
	}
#endif

#if 0
	CupBoard<2> clipboard;
	clipboard.open();
#endif

#if 0
	//ADL This uses argument dependent [that works on function that use specific types)
	f(N::e1);
#endif
	//DXTT<int> dxtt;
#if 0
	DD<int> dd;
	dd.f();
#endif
#if 0
	Tricky<int, -1> tricky;
	tricky.error();
#endif

#if 0
	//size of the array and const is preserver because of T&
	const int x[20] = { 0 };
	gByReference(x);
	std::cout << x[0] << std::entemplate<typename T>
	struct HasContiguousStorage: public std::false_type{};

	template<typename T>
	struct HasContiguousStorage<std::vector<T>>: public std::true_type{};
	// Specialize othersdl;
#endif

#if 0
	int*** x;
	f1(x);
#endif

#if 0
	int x[20];
	f2(x);
#endif
#if 0
	ff<int>(0);
	ff<int*>(nullptr);
#endif

#if 0
	List<int> iList;
	int x;
	iList.append(x);
#endif

#if 0
	float x[] = { 1.0, 2.0, 3.0, 4.3 };
	std::cout << accumulate(x, x+ 4) << std::endl;
#endif

#if 0
	int x[] = { 1, 2, 3, 4 };
	std::cout << AccumulateWithIter(&x[0], &x[4]) << std::endl;
#endif

#if 0
	std::vector<int> c = { 1, 2, 3, 4, 5, 6 };
	std::cout << SumContainer(c) << std::endl;
#endif

#if 0
	struct Foo
	{

	};

	enum class Foo2 : int
	{

	};

	union skata
	{
		int x;
		float y;
	};

	auto l = []() {};
	std::function<void(int)> ll;

	if (__is_class(skata))
	{
		std::cout << "Is class" << std::endl;
	}
	else
	{
		std::cout << "Is not a class " << std::endl;
	}
#endif

#if 0
	const int& x = int();

	apply<const int&>(x, foo);
#endif

#if 0
	std::cout << "Empty" << sizeof(Empty) << " EmptyToo: " << sizeof(EmptyToo) << " Non Empty: " << sizeof(NonEmpty) << std::endl;
#endif

#if 0
	SingleObject object;
	SingleObject object2;
#endif

#if 0
	BBase<NotVirtual>* p1 = new Derived<NotVirtual>;
	p1->foo();  // calls Base::foo()

	BBase<Virtual>* p2 = new Derived<Virtual>;
	p2->foo();  // calls Derived::foo()
#endif

#if 0
	std::cout << Pow3<7>::result << std::endl;
#endif

#if 0
	std::cout << "sqrt: " << Sqrt2<99999>::result << std::endl;
#endif

#if 0
	int a[600];
	memset(a, 1, 600);
	int b[600];
	memset(b, 2, 600);
	std::cout << DoTProduct<sizeof(a)/sizeof(a[0]), int>::Result(a, b) << std::endl;
#endif

#if 0
	std::vector<Object> backpack;
	backpack.push_back( Object( Weapon() ) );
	backpack.push_back( Object( Armor() ) );
	backpack.push_back( Object( Potion() ) );


#endif

#if 0
	function<void, int> f;
	f(1);
#endif



#if 0
	my_function2<void(int)> ff {ffoo()};
	my_function2<void(int)> ff2 = std::move(ff);

	ff2 = my_function2<void(int)>{ffoo2()};

	std::cout << sizeof(ff2) << std::endl;

#endif

#if 0
	my_function<void(int)> ff(ffoo{});
	ff(1);
#endif

#if 0
	CompoundT<int**>::BaseT x;
	CompoundT<int**>::BottomT y;

	std::cout << "base is: " << typeid(x).name() <<  " bottom is: " << typeid(y).name() << std::endl;
#endif

#if 0
	enum foo
	{
		OK,
		NOT_OK
	};

	class skata
	{
		int x;
		int y;
	};

	//std::cout << CompoundT<decltype(foo1)>::IsFuncT << std::endl;
	//std::cout << IsEnumT<enum foo>::Yes;

	std::cout << "is class ? " << IsClassT<class skata>::Yes << std::endl;
#endif

#if 1
	ManagedType::Ptr p(new ManagedType());
	{
		ManagedType::Ptr p2 = ManagedType::Ptr (new ManagedType());
		ManagedType::Ptr p3 = p2;
		std::cout << p->x << std::endl;
	};

	auto x = std::make_shared<int>();
	std::weak_ptr<int> xx = x;

	std::cout << "sizeof smart ptr is " << sizeof(ManagedType::Ptr) << std::endl;
#endif

#if 0
	{
		gens<10> g;
		gens<10>::type s;
		std::tuple<int, float, double> t = std::make_tuple(1, 1.2, 5);
		save_it_for_later<int,float, double> saved = {t, foo};
		cout << saved.delayed_dispatch() << endl;
	}
#endif

#if 0
	Duo<int, float> f(1, 2);
	Duo<int, Duo<int, float>> g(1, f);

	std::cout << val<1>(f) << std::endl;
#endif

#if 0
	Expected<Noisy, int> e1;

	Expected<Noisy, int> e3 = Noisy();
	const Noisy* n = &*e3;
	std::cout << "e3 id is " << e3->getId() << std::endl;

	Expected<int, int> e4 = 1;
	std::cout << "e4 value is " << *e4 << std::endl;

	Expected<Noisy, int> e6 = UnExpected<int>(3);
#endif

#if 0
	MyType m;
	auto wrapper = mem_fn(&MyType::foo, m);
	function<int(int, int)> f(wrapper);
	std::cout << f(1,2) << std::endl;
#endif


}
