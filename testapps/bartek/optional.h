#ifndef OPTIONAL_H_
#define OPTIONAL_H_

//required for uint8_t
#include <stdint.h>

template< class T > struct remove_reference      {typedef T type;};
template< class T > struct remove_reference<T&>  {typedef T type;};
template< class T > struct remove_reference<T&&> {typedef T type;};

template< class T >
T&& forward( typename remove_reference<T>::type& t )
{
	return static_cast<T&&>(t)

;
}

template< class T >
T&& forward( typename remove_reference<T>::type&& t )
{
	return static_cast<T&&>(t);
}

struct nullopt_t
{

};

constexpr struct nullopt_t nullopt = nullopt_t();

template<typename T>
class optional
{
public:
	constexpr optional()
	{

	}

	constexpr optional(nullopt_t)
	{

	}

	template <typename... Ts>
	optional(Ts&&... args )
	{
		obj = new(storage)T(forward<Ts>(args)...);
	}

	optional(optional& rhs)
	{
		if (rhs.obj)
		{
			obj = new(storage)T(*rhs.obj);
		}
	}

	optional(optional&& rhs)
	{
		if (rhs.obj)
		{
			obj = new(storage)T(*rhs.obj);
			rhs = nullopt;
		}
	}

	optional& operator = (const optional& rhs)
	{
		if (rhs.obj)
		{
			obj = new(storage)T(*rhs.obj);
		}
		else
		{
			obj = nullptr;
		}

		return *this;
	}

	optional& operator = (optional&& rhs)
	{
		if (rhs.obj)
		{
			obj = new(storage)T(*rhs.obj);
			rhs = nullopt;
		}
		else
		{
			obj = nullptr;
		}

		return *this;
	}

	optional& operator = (T& t)
	{
		if (!obj)
		{
			obj = new(storage)T(t);
		}

		return *this;
	}

	optional& operator = (T&& t)
	{
		if (!obj)
		{
			obj = new(storage)T(t);
		}

		t.~T();

		return *this;
	}

	constexpr explicit operator bool() const
	{
		return obj != nullptr;
	}

	constexpr bool operator!() const
	{
		return !this->operator bool();
	}

	T& operator*()
	{
		return *obj;
	}

	const T& operator*() const
	{
		return *obj;
	}

	T* operator->()
	{
		return obj;
	}

	const T* operator->() const
	{
		return obj;
	}

private:
	uint8_t storage[sizeof(T)];
	T* obj = nullptr;
};

//relational operators
template <class T> constexpr bool operator==(const optional<T>& lhs, const optional<T>& rhs)
{
	//C++11 requirement for single return (C++14 doesn't require this)
	return bool(lhs) != bool(rhs) ? false :
									(bool(lhs) == false ? true :
														  *lhs == *rhs);
}

template <class T> constexpr bool operator<(const optional<T>& lhs, const optional<T>& rhs)
{
	return bool(rhs) == false ? true :
								(bool(lhs) == false ? true :
													  (*lhs < *rhs));
}

// Comparison with nullopt
template <class T> constexpr bool operator==(const optional<T>& lhs, nullopt_t rhs)
{
	return (!lhs);
}

template <class T> constexpr bool operator==(nullopt_t lhs, const optional<T>& rhs)
{
	return operator==<T>(rhs, lhs);
}

template <class T>  constexpr bool operator < (const optional<T>& rhs, nullopt_t)
{
	return false;
}

template <class T>  bool constexpr operator < (nullopt_t, const optional<T>& rhs)
{
	return bool(rhs);
}

//Comparison with T
template <class T>  bool constexpr operator == (const optional<T>&lhs , const T& rhs)
{
	//C++11 requirement for single return (C++14 doesn't require this)
	return bool(lhs) ? (*lhs == rhs) : false;
}

template <class T> constexpr bool operator == (const T& lhs, const optional<T>& rhs)
{
	//C++11 requirement for single return (C++14 doesn't require this)
	return bool(rhs) ? (*rhs == lhs) : false;
}

template <class T> bool constexpr operator < (const optional<T>& lhs, const T& rhs)
{
	//C++11 requirement for single return (C++14 doesn't require this)
	return bool(lhs) ? *lhs < rhs : false;
}

template <class T> constexpr bool operator < (const T& lhs, const optional<T>& rhs)
{
	//C++11 requirement for single return (C++14 doesn't require this)
	return bool(rhs) ? *rhs == lhs : false;
}


#endif /* OPTIONAL_H_ */
