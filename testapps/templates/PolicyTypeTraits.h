template<typename T>
class AccumulationTraits;

template <>
struct AccumulationTraits<int>
{
	typedef long AccT;
	static AccT constexpr zero = 0;
};

template<>
struct AccumulationTraits<char>
{
	typedef int AccT;
	static AccT constexpr zero =0;
};

template<>
struct AccumulationTraits<float>
{
	typedef float AccT;
	static AccT constexpr zero =0.0;
};

template<typename T>
typename AccumulationTraits<T>::AccT accumulate(const T* begin, const T* end)
{
	typedef typename AccumulationTraits<T>::AccT AccT;
	AccT total = AccT::zero;

	while(begin != end)
	{
		total+=*begin;
		++begin;
	}

	return total;
}

template<typename T, typename AT = AccumulationTraits<T> >
class Accum
{
public:
	static typename AT::AccT accum(T const* beg, T const* end)
	{
		typename AT::AccT total = AT::zero();
		while (beg != end)
		{
			total += *beg;
			++beg;
		}
		return total;
	}
};

template <typename T1, typename T2>
class SumPolicy
{
public:
	static void accumulate(T1& result, const T2& input)
	{
		result+=input;
	}
};


template <typename T1, typename T2>
class MulPolicy
{
public:
	static void accumulate(T1& result, const T2& input)
	{
		result+=input;
	}
};

template<typename T, typename Traits = AccumulationTraits<T>,  typename Policy = SumPolicy<typename Traits::AccT, T>>
class Accum2
{
public:
	typedef typename Traits::AccT AccT;

	static AccT accum(T const* beg, T const* end)
	{
		AccT total = Traits::zero;
		while (beg != end)
		{
			Policy::accumulate(total, *beg);
			++beg;
		}
		return total;
	}
};

#include <iterator>

template<typename Iter>
typename std::iterator_traits<Iter>::value_type AccumulateWithIter(Iter start, Iter end)    ///< NOTE: We need to pass here by value
{
	auto total = typename std::iterator_traits<Iter>::value_type(); ///< Assuming this will be zero

	while(start != end)
	{
		total+= *start;
		std::advance(start, 1);
	}

	return total;
}

template<typename C>
typename C::value_type SumContainer(C& c)
{
	auto total = typename C::value_type();
	for(auto it = c.begin(); it != c.end(); ++it)
	{
		total+= *it;
	}

	return total;
}
