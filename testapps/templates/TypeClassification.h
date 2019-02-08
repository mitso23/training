template <typename T>
class IsFundaT
{
public:
	enum
	{
		YES = 0,
		NO =  1,
	};
};


// macro to specialize for fundamental types
#define MK_FUNDA_TYPE(T)                           \
    template<> class IsFundaT<T> {                 \
      public:                                      \
        enum { Yes = 1, No = 0 };                  \
    };

MK_FUNDA_TYPE(void)
MK_FUNDA_TYPE(bool)
MK_FUNDA_TYPE(char)
MK_FUNDA_TYPE(signed char)
MK_FUNDA_TYPE(unsigned char)
MK_FUNDA_TYPE(wchar_t)
MK_FUNDA_TYPE(signed short)
MK_FUNDA_TYPE(unsigned short)
MK_FUNDA_TYPE(signed int)
MK_FUNDA_TYPE(unsigned int)
MK_FUNDA_TYPE(signed long)
MK_FUNDA_TYPE(unsigned long)
MK_FUNDA_TYPE(signed long long)
MK_FUNDA_TYPE(unsigned long long)
MK_FUNDA_TYPE(float)
MK_FUNDA_TYPE(double)
MK_FUNDA_TYPE(long double)

#undef MK_FUNDA_TYPE

template<typename T>
class CompoundT
{           // primary template
public:
	enum
	{
		IsPtrT = 0, IsRefT = 0, IsArrayT = 0, IsFuncT = 0, IsPtrMemT = 0
	};
	typedef T BaseT;
	typedef T BottomT;
	typedef CompoundT<void> ClassT;
};

template<typename T>
class CompoundT<T&>
{       // partial specialization for references
public:
	enum
	{
		IsPtrT = 0, IsRefT = 1, IsArrayT = 0, IsFuncT = 0, IsPtrMemT = 0
	};
	typedef T BaseT;
	typedef typename CompoundT<T>::BottomT BottomT;
	typedef CompoundT<void> ClassT;
};
template<typename T>
class CompoundT<T*>
{       // partial specialization for pointers
public:
	enum
	{
		IsPtrT = 1, IsRefT = 0, IsArrayT = 0, IsFuncT = 0, IsPtrMemT = 0
	};
	typedef T BaseT;
	typedef typename CompoundT<T>::BottomT BottomT;
	typedef CompoundT<void> ClassT;
};

//Arrays and pointers to members can be treated using the same technique, but it may come as a surprise that the partial specializations involve more template parameters than the primary template:
// types/type4.hpp
#include <stddef.h>
template<typename T, size_t N>
class CompoundT<T[N]>
{    // partial specialization for arrays
public:
	enum
	{
		IsPtrT = 0, IsRefT = 0, IsArrayT = 1, IsFuncT = 0, IsPtrMemT = 0
	};
	typedef T BaseT;
	typedef typename CompoundT<T>::BottomT BottomT;
	typedef CompoundT<void> ClassT;
};
template<typename T>
class CompoundT<T[]>
{    // partial specialization for empty arrays
public:
	enum
	{
		IsPtrT = 0, IsRefT = 0, IsArrayT = 1, IsFuncT = 0, IsPtrMemT = 0
	};
	typedef T BaseT;
	typedef typename CompoundT<T>::BottomT BottomT;
	typedef CompoundT<void> ClassT;
};

template<typename T, typename C>
class CompoundT<T C::*>
{  // partial specialization for pointer-to-members
public:
	enum
	{
		IsPtrT = 0, IsRefT = 0, IsArrayT = 0, IsFuncT = 0, IsPtrMemT = 1
	};
	typedef T BaseT;
	typedef typename CompoundT<T>::BottomT BottomT;
	typedef C ClassT;
};

template<typename R>
class CompoundT<R()>
{
public:
	enum
	{
		IsPtrT = 0, IsRefT = 0, IsArrayT = 0, IsFuncT = 1, IsPtrMemT = 0
	};
	typedef R BaseT();
	typedef R BottomT();
	typedef CompoundT<void> ClassT;
};

template<typename R, typename P1>
class CompoundT<R(P1)>
{
public:
	enum
	{
		IsPtrT = 0, IsRefT = 0, IsArrayT = 0, IsFuncT = 1, IsPtrMemT = 0
	};
	typedef R BaseT(P1);
	typedef R BottomT(P1);
	typedef CompoundT<void> ClassT;
};

template<typename R, typename P1>
class CompoundT<R(P1, ...)>
{
public:
	enum
	{
		IsPtrT = 0, IsRefT = 0, IsArrayT = 0, IsFuncT = 1, IsPtrMemT = 0
	};
	typedef R BaseT(P1);
	typedef R BottomT(P1);
	typedef CompoundT<void> ClassT;
};

struct SizeOverOne
{
	char x[2];
};

template<typename T, bool convert_possible = !CompoundT<T>::IsFuncT &&
											 !CompoundT<T>::IsArrayT>
class ConsumeUDC
{
public:
	operator T() const;
};

template<typename T>
class ConsumeUDC<T, false>
{

};

// conversion to void type is not possible
template<bool convert_possible>
class ConsumeUDC<void, convert_possible>
{

};

char enum_check(bool);
char enum_check(char);
char enum_check(signed char);
char enum_check(unsigned char);
char enum_check(wchar_t);
char enum_check(signed short);
char enum_check(unsigned short);
char enum_check(signed int);
char enum_check(unsigned int);
char enum_check(signed long);
char enum_check(unsigned long);
char enum_check(signed long long);
char enum_check(unsigned long long);

// avoid accidental conversions from float to int
char enum_check(float);
char enum_check(double);
char enum_check(long double);

SizeOverOne enum_check(...);

template<typename T>
class IsEnumT
{
public:
	enum
	{
		Yes = 	IsFundaT<T>::NO &&
				!CompoundT<T>::IsRefT &&
				!CompoundT<T>::IsPtrT &&
				!CompoundT<T>::IsPtrMemT &&
				sizeof(enum_check(ConsumeUDC<T>())) == 1
	};

	enum
	{
		No = !Yes
	};
};

template<typename T>
class IsClassT
{
public:
	enum
	{
		Yes = IsFundaT<T>::No && IsEnumT<T>::No && !CompoundT<T>::IsPtrT
				&& !CompoundT<T>::IsRefT && !CompoundT<T>::IsArrayT
				&& !CompoundT<T>::IsPtrMemT && !CompoundT<T>::IsFuncT
	};
	enum
	{
		No = !Yes
	};
};
