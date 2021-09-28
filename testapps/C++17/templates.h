#pragma once

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