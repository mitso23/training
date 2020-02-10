/*
 * TypeTraits.h
 *
 *  Created on: Feb 5, 2020
 *      Author: mitso23
 */

#ifndef TESTAPPS_MODERNC__DESIGN_TYPETRAITS_H_
#define TESTAPPS_MODERNC__DESIGN_TYPETRAITS_H_

#include <tuple>
#include <type_traits>

struct NullType
{

};

template<typename T>
class TypeTraits
{
private:
	template<class U>
	struct PointerTraits
	{
		enum
		{
			result = false
		};
		typedef NullType PointeeType;
	};

	template<class U>
	struct PointerTraits<U*>
	{
		enum
		{
			result = true
		};
		typedef U PointeeType;
	};
public:
	enum
	{
		isPointer = PointerTraits<T>::result
	};

	typedef typename PointerTraits<T>::PointeeType PointeeType;
};

template <typename T, typename Tuple>
struct has_type;

template <typename T> struct has_type<T, std::tuple<>> : public std::false_type {};

template <typename T, typename U, typename... Ts>
struct has_type<T, std::tuple<U, Ts...>> : has_type<T, std::tuple<Ts...>>{};

template<typename T, typename... Ts>
struct has_type<T, std::tuple<T, Ts...>> : public std::true_type {};

template<typename... Ts>
struct Factory
{
	template<typename T>
	T Get()
	{
		static_assert(has_type<T, std::tuple<Ts...>>{}, "there is no such type in the container");
		return T();
	}

	std::tuple<Ts...> products;
};





#endif /* TESTAPPS_MODERNC__DESIGN_TYPETRAITS_H_ */
