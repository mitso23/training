template<typename T1, typename T2>
class Duo
{
public:
	typedef T1 Type1;  // type of first field
	typedef T2 Type2;  // type of second field
	enum
	{
		N = 2
	};    // number of fields
private:
	T1 value1;         // value of first field
	T2 value2;         // value of second field
public:
	// constructors
	Duo() :
			value1(), value2()
	{

	}

	Duo(T1 const & a, T2 const & b) :
			value1(a), value2(b)
	{
		std::cout << "Duo is constructed " << std::endl;
	}

	// for implicit type conversion during construction
	template<typename U1, typename U2>
	Duo(Duo<U1, U2> const & d) :
			value1(d.v1()), value2(d.v2())
	{

	}

	// for implicit type conversion during assignments
	template<typename U1, typename U2>
	Duo<T1, T2>& operator =(Duo<U1, U2> const & d)
	{
		value1 = d.value1;
		value2 = d.value2;
		return *this;
	}

	// field access
	T1& v1()
	{
		return value1;
	}

	T1 const& v1() const
	{
		return value1;
	}

	T2& v2()
	{
		return value2;
	}

	T2 const& v2() const
	{
		return value2;
	}
};

template<int N, typename T>
class DuoT
{
public:
	typedef void ResultT;    // in general, the result type is void
};

// specialization for 1st field of a plain duo
template<typename A, typename B>
class DuoT<1, Duo<A, B> >
{
public:
	typedef A ResultT;
};

// primary template for value of Nth field of (duo) T
template<int N, typename T>
class DuoValue
{
public:
	static void get(T&)
	{        // in general, we have no value
	}
	static void get(T const&)
	{
	}
};

// specialization for 1st field of a plain duo
template<typename A, typename B>
class DuoValue<1, Duo<A, B> >
{
public:
	static A& get(Duo<A, B> &d)
	{
		return d.v1();
	}
	static A const& get(Duo<A, B> const &d)
	{
		return d.v1();
	}
};

// specialization for 2nd field of a plain duo
template<typename A, typename B>
class DuoValue<2, Duo<A, B> >
{
public:
	static B& get(Duo<A, B> &d)
	{
		return d.v2();
	}
	static B const& get(Duo<A, B> const &d)
	{
		return d.v2();
	}
};

// return Nth value of variable duo
// as this is a function template deduction happens automatically so we can write val<1>
template <int N, typename A, typename B>
inline
typename TypeOp<typename DuoT<N, Duo<A, B> >::ResultT>::RefT
val(Duo<A, B>& d)
{
    return DuoValue<N, Duo<A, B> >::get(d);
}

// return Nth value of constant duo
template <int N, typename A, typename B>
inline
typename TypeOp<typename DuoT<N, Duo<A, B> >::ResultT>::RefConstT
val(Duo<A, B> const& d)
{
    return DuoValue<N, Duo<A, B> >::get(d);
}

// comparison operators (allow mixed types):
template<typename T1, typename T2, typename U1, typename U2>
inline
bool operator ==(Duo<T1, T2> const& d1, Duo<U1, U2> const& d2)
{
	return d1.v1() == d2.v1() && d1.v2() == d2.v2();
}
template<typename T1, typename T2, typename U1, typename U2>
inline
bool operator !=(Duo<T1, T2> const& d1, Duo<U1, U2> const& d2)
{
	return !(d1 == d2);
}
// convenience function for creation and initialization
template<typename T1, typename T2>
inline Duo<T1, T2> make_duo(T1 const & a, T2 const & b)
{
	return Duo<T1, T2>(a, b);
}


#if 0
// type that represents unused type parameters
class NullT
{

};

// Tuple<> in general derives from Tuple<> with one more NullT
template<typename P1,
         typename P2 = NullT,
         typename P3 = NullT,
         typename P4 = NullT,
         typename P5 = NullT>
class Tuple: public Duo<P1, typename Tuple<P2, P3, P4, P5, NullT>::BaseT>
{
public:
	typedef Duo<P1, typename Tuple<P2, P3, P4, P5, NullT>::BaseT> BaseT;
	// constructors:
    Tuple() {}
    Tuple(TypeOp<P1>::RefConstT a1,
          TypeOp<P2>::RefConstT a2,
          TypeOp<P3>::RefConstT a3 = NullT(),
          TypeOp<P4>::RefConstT a4 = NullT(),
          TypeOp<P5>::RefConstT a5 = NullT())
     : BaseT(a1, Tuple<P2,P3,P4,P5,NullT>(a2,a3,a4,a5)) {
    }
};

// specialization to end deriving recursion
template <typename P1, typename P2>
class Tuple<P1,P2,NullT,NullT,NullT> : public Duo<P1,P2>
{
  public:
    typedef Duo<P1,P2> BaseT;
    Tuple() {}
    Tuple(TypeOp<P1>::RefConstT a1,
          TypeOp<P2>::RefConstT a2,
          TypeOp<NullT>::RefConstT = NullT(),
          TypeOp<NullT>::RefConstT = NullT(),
          TypeOp<NullT>::RefConstT = NullT())
     : BaseT(a1, a2) {
    }
};
#endif

template<int...> struct seq
{

};

// gens<5> : 	   gens<4,4>
// gens<4,4> : 	   gens<3,3, 4>
// gens<3,3,4> :   gens<2,2,3,4>
// gens<2,2,3,4> : gens<1, 1, 2, 3, 4>
// gens<1,2,3,4> : gens<0, 0, 1, 2, 3, 4>
template<int N, int ...S> struct gens : gens<N - 1, N - 1, S...>
{
};

template<int ...S> struct gens<0, S...>
{
	typedef seq<S...> type;
};

double foo(int x, float y, double z)
{
	return x + y + z;
}

template<typename ...Args>
struct save_it_for_later
{
	std::tuple<Args...> params;
	double (*func)(Args...);

	double delayed_dispatch()
	{
		return callFunc(typename gens<sizeof...(Args)>::type());
	}

	template<int ...S>
	double callFunc(seq<S...>)
	{
		return func(std::get<S>(params) ...);
	}
};


