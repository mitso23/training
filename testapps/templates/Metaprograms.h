// primary template to compute 3 to the Nth
template<int N>
class Pow3
{
public:
	enum
	{
		result = 3 * Pow3<N - 1>::result
	};
};

template<>
class Pow3 <0>
{

public:
	enum
	{
		result = 1
	};

};

// primary template to compute sqrt(N)
template<int N, int LO = 1, int HI = N>
class Sqrt
{
public:
	// compute the midpoint, rounded up
	enum
	{
		mid = (LO + HI + 1) / 2
	};

	// search a not too large value in a halved interval
	enum
	{
		result = (N < mid * mid) ? Sqrt<N, LO, mid - 1>::result : Sqrt<N, mid, HI>::result
	};
};
// partial specialization for the case when LO equals HI
template<int N, int M>
class Sqrt<N, M, M>
{
public:
	enum
	{
		result = M
	};
};


// primary template for main recursive step
template<int N, int LO = 1, int HI = N>
class Sqrt2
{
public:
	// compute the midpoint, rounded up
	enum
	{
		mid = (LO + HI + 1) / 2
	};
	// search a not too large value in a halved interval
	typedef typename IfThenElse<(N < mid * mid), Sqrt<N, LO, mid - 1>,
			Sqrt<N, mid, HI> >::ResultT SubT;
	enum
	{
		result = SubT::result
	};
};

// partial specialization for end of recursion criterion
template<int N, int S>
class Sqrt2<N, S, S>
{
public:
	enum
	{
		result = S
	};
};

// primary template to compute sqrt(N) via iteration
template<int N, int I = 1>
class Sqrt3
{
public:
	enum
	{
		result = (I * I < N) ? Sqrt<N, I + 1>::result : I
	};
};

// partial specialization to end the iteration
template<int N>
class Sqrt3<N, N>
{
public:
	enum
	{
		result = N
	};
};

template<unsigned int DIM, typename T>
class DoTProduct
{
public:
	static unsigned Result(T* a, T* b)
	{
		return a[DIM-1]*b[DIM-1] + DoTProduct<DIM-1,T>::Result(a, b);
	}
};

template<typename T>
class DoTProduct<1, T>
{
public:
	static unsigned Result(T* a, T* b)
	{
		return *a * *b;
	}
};



