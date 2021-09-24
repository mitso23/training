#include "AutomaticTypeDeduction.h"
#include "FoldExpressions.h"
#include "StructureBinding.h"
#include <iostream>
#include <type_traits>
#include "lambdas.h"

#ifndef FAMETA_COUNTER_HPP_
#define FAMETA_COUNTER_HPP_

namespace fameta {
	struct default_counter_tag{};

	template <int StartN, int StartValue = 0, int Step = 1, typename Tag = default_counter_tag>
	class counter;
}

template <int StartN, int StartValue, int Step, typename Tag>
class fameta::counter {
#if defined(__INTEL_COMPILER) || defined(_MSC_VER) || !defined(__cpp_decltype_auto)
	template <int N>
    struct slot {
        #if defined(__INTEL_COMPILER)
        #   pragma warning push
        #   pragma warning disable 1624
        #elif defined(__GNUC__) && !defined(__clang__)
        #   pragma GCC diagnostic push
        #   pragma GCC diagnostic ignored "-Wnon-template-friend"
        #endif
        friend constexpr int slot_value(slot<N>);
        #if defined(__INTEL_COMPILER)
        #   pragma warning pop
        #elif defined(__GNUC__) && !defined(__clang__)
        #   pragma GCC diagnostic pop
        #endif
    };

    template <int N, int I>
    struct writer {
        friend constexpr int slot_value(slot<N>) {
            return I;
        }

        static constexpr int value = I;
    };

    template <int N, int R = slot_value(slot<N>())>
    static constexpr int reader(int, slot<N>) {
        return R;
    };
#else
	template <int N>
	struct slot {
#if defined(__GNUC__) && !defined(__clang__)
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wnon-template-friend"
#endif
		friend constexpr auto slot_value(slot<N>);
#if defined(__GNUC__) && !defined(__clang__)
#   pragma GCC diagnostic pop
#endif
	};

	template <int N, int I>
	struct writer {
		friend constexpr auto slot_value(slot<N>) {
			return I;
		}

		static constexpr int value = I;
	};

	template <int N, typename = decltype(slot_value(slot<N>()))>
	static constexpr int reader(int, slot<N>, int R = slot_value(slot<N>())) {
		return R;
	}
#endif

	static_assert(sizeof(writer<StartN, StartValue-Step>), "Base case");

	template <int N>
	static constexpr int reader(float, slot<N>, int R = reader(0, slot<N-1>())) {
		return R;
	}

 public:

#if !defined(__clang_major__) || __clang_major__ > 7
	template <int N>
	static constexpr int next(int R = writer<N, reader(0, slot<N-1>())+Step>::value) {
		return R;
	}
#else
	template <int N>
    static constexpr int next(int R = writer<N, reader(0, slot<N>())+Step>::value) {
        return R;
    }
#endif
};

#endif

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

int main(int argc, char* argv[])
{
#if 1
	// the answer to life, the universe, etc. in...
	auto a1 = 42;        // ... decimal
	auto a2 = 0x2A;      // ... hexadecimal
	auto a3 = 0b101010;  // ... binary

	std::cout << "a3: " << a3 << std::endl;

	std::cout << "foo result: " << foo(1, 2) << std::endl;
	std::cout << "foo result: " << foo(1.0, 2.2) << std::endl;

	auto v = make_vector<int>(1,2,3,4);
	printer(1,2,3,4);
#endif

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

	std::cout << decodedText << std::endl;
}

