template<typename T>
class IsClassT
{
private:
	typedef char One;

	typedef struct
	{
		char a[2];
	}Two;

	template<typename C> static One test(int C::*);
	template<typename C> static Two test(...);

public:
	enum
	{
		Yes = sizeof(IsClassT<T>::test<T>(0)) == 1
	};

	enum
	{
		No = !Yes
	};
};

template <typename T>
class TypeOp	            // primary template
{
  public:
    typedef T         ArgT;
    typedef T         BareT;
    typedef T const   ConstT;
    typedef T &       RefT;
    typedef T &       RefBareT;
    typedef T const & RefConstT;
};

template <typename T>
class TypeOp <T const> 			// partial specialization for const types
{
  public:
    typedef T const   ArgT;
    typedef T         BareT;
    typedef T const   ConstT;
    typedef T const & RefT;
    typedef T &       RefBareT;
    typedef T const & RefConstT;
};


template <typename T>
class TypeOp <T&>
{       											// partial specialization for references
public:
	typedef T&                          ArgT;
	typedef typename TypeOp<T>::BareT   BareT;
	typedef T const                     ConstT;
	typedef T &                         RefT;
	typedef typename TypeOp<T>::BareT & RefBareT;
	typedef T const &                   RefConstT;
};

template <typename T>
class TypeOp<const T&>
{
public:
	typedef const T& 					ArgT;
	typedef typename TypeOp<T>::BareT   BareT;
	typedef T const						ConstT;
	typedef const T& 					RefT;
	typedef typename TypeOp<T>::BareT&  RefBareT;
	typedef T const& 					RefConstT;
};

template<>
class TypeOp <void>
{     										// full specialization for void
  public:
    typedef void       ArgT;
    typedef void       BareT;
    typedef void const ConstT;
    typedef void       RefT;
    typedef void       RefBareT;
    typedef void       RefConstT;
};

// primary template: yield second or third argument depending on first argument
template<bool C, typename Ta, typename Tb>
class IfThenElse;


// partial specialization: true yields second argument
template<typename Ta, typename Tb>
class IfThenElse<true, Ta, Tb>
{
public:
	typedef Ta ResultT;
};

// partial specialization: false yields third argument
template<typename Ta, typename Tb>
class IfThenElse<false, Ta, Tb>
{
public:
	typedef Tb ResultT;
};

// primary template for type promotion
template<typename T1, typename T2>
class Promotion
{
public:
	typedef typename IfThenElse<(sizeof(T1) > sizeof(T2)),
								T1,
								typename IfThenElse<(sizeof(T1) < sizeof(T2)),
													 T2,
													 void>::ResultT
					           >::ResultT ResultT;
};

//template deduction will not work in this case, we will need to pass the full argument
template <typename T>
void apply (typename TypeOp<T>::RefT arg, void (*func)(T))
{
    func(arg);
}

