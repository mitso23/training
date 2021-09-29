#pragma once

#include <string>
#include <functional>
#include <type_traits>

template<typename T, int SZ>
class Array
{
	explicit Array(T(&arr)[SZ])
		: m_arr(arr)
	{

	}

private:
	T m_arr[SZ];
};

template<typename CB>
class CountCalls
{
 private:
	CB callback;
	long calls = 0;
 public:
	CountCalls(CB cb) : callback(cb)
	{
	}

	template<typename... Args>
	decltype(auto) operator()(Args&& ... args)
	{
		++calls;
		return callback(std::forward<Args>(args)...);
	}

	long count() const
	{
		return calls;
	}
};

template<typename T>
struct S
{
    S(const T& val_)
        : val(val_)
    {

    }

    T val;
};

explicit S(const char*) -> S<std::string>;

template<typename T>
struct Ptr
{
    Ptr(T)
    {
        std::cout << "Ptr(T)\n";
    }

    template<typename U>
    Ptr(U)
    {
        std::cout << "Ptr(U)\n";
    }
};

template<typename T>
explicit Ptr(T) -> Ptr<T*>;

template<typename T>
std::string asString(T x)
{
    if constexpr(std::is_same_v<T,std::string>)
    {
        return x; // statement invalid if no conversion to string
    }
    else if constexpr(std::is_arithmetic_v < T >)
    {
        return std::to_string(x); // statement invalid if x is not numeric
    }
    else
    {
        return std::string(x); // statement invalid if no conversion to string
    }
}

auto MultipleReturns()
{
    if constexpr (sizeof(int) >= 4)
    {
        return 42;
    }
    else
    {
        return 42u;
    }
}

template<typename T>
constexpr auto TestIntegral(const T& val)
{
    if constexpr (std::is_integral<T>::value)
    {
        if constexpr (T{} < 10)
        {
            return val * 2;
        }
    }
    return val;
}

template<typename Callable, typename... Args>
decltype(auto) Call(Callable op, Args&& ... args)
{
    if constexpr(std::is_void_v < std::invoke_result_t < Callable, Args...>>)
    {
        // return type is void:
        op(std::forward<Args>(args)...);
        // do something before we return
        return;
    }
    else
    {
        // return type is not void:
        decltype(auto) ret{ op(std::forward<Args>(args)...) };

        // do something (with ret) before we return
        return ret;
    }
}