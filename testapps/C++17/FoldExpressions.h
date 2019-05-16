#include <type_traits>
#include <sstream>
#include <ctype.h>
#include <array>
#include <string.h>

template<typename T, typename _ = void>
struct is_stl_container : std::false_type {};

template<typename... Ts>
struct is_container_helper {};

template<typename T>
struct is_stl_container<
        T,
        std::conditional_t<
            false,
            is_container_helper<
                typename T::value_type,
                typename T::size_type,
                typename T::allocator_type,
                typename T::iterator,
                typename T::const_iterator,
                decltype(std::declval<T>().size()),
                decltype(std::declval<T>().begin()),
                decltype(std::declval<T>().end()),
                decltype(std::declval<T>().cbegin()),
                decltype(std::declval<T>().cend())
                >,
            void
            >
        > : public std::true_type
{

};

template<typename T, typename _ = void>
struct is_stream_insertable : std::false_type {};

template<typename ...T>
struct is_stream_insertable_helper {};

template<typename T>
struct is_stream_insertable<
						T,
						std::conditional_t<
											false,
											is_stream_insertable_helper<decltype(std::declval<std::ostream&>() << std::declval<T&>()),
																		std::enable_if_t<
																						std::is_convertible<decltype(std::declval<std::ostream&>() << std::declval<T&>()),
																											std::ostream&>::value,
																						T
																						>
																	   >,
											void
										>
							>  : std::true_type

{

};

template<typename T>
struct is_stl_array :  std::false_type {};

template<typename T, size_t N>
struct is_stl_array<std::array<T,N>> : std::true_type {};


template<typename T, size_t N>
inline void printSingleArgument(T&& arg, char(&buffer)[N], unsigned int& pos)
{
	//NOTE: We are not using stringstream for performance reasons
	// they are significantly slower than raw C function + they use heap allocation
	if (pos >= N)
	{
		return;
	}

	if constexpr((std::is_enum<T>::value || std::is_class<T>::value) && is_stream_insertable<T>{})
	{
		std::stringstream stream;
		stream << arg;

		pos+= snprintf(buffer + pos, N - pos, "%s ", stream.str().c_str());
	}
	else if constexpr (std::is_enum<T>::value)
	{
		//If enum hasn't implemented the << operator then we can print it as an unsigned int

		pos+= snprintf(buffer + pos, N-pos, "%u", static_cast<unsigned int>(arg));
	}
	//NOTE even thought string is an STL container, we prefer to log it via the c.str() for convenience
	else if constexpr(std::is_same<std::decay_t<T>, std::string>::value)
	{
		pos+= snprintf(buffer + pos, N-pos, "%s ", arg.c_str());
	}
	else if constexpr (is_stl_container<std::decay_t<T>>{} || is_stl_array<std::decay_t<T>>{})
	{
		pos+= snprintf(buffer + pos, N-pos, "%s", "{ ");

		for(const auto& item : arg)
		{
			printSingleArgument(item, buffer, pos);
		}

		pos+= snprintf(buffer + pos, N-pos, "%s", " } ");
	}
	else if constexpr(std::is_integral<std::decay_t<T>>::value)
	{
		if constexpr(std::is_signed<std::decay_t<T>>::value)
		{
			if constexpr(std::is_same<std::decay_t<T>, char>::value)
			{
				if (!isprint(arg))
				{
					pos+= snprintf(buffer + pos, N - pos, "%hhi ", arg);
				}
				else
				{
					pos+= snprintf(buffer + pos, N - pos, "%c ", arg);
				}
			}
			else if constexpr(std::is_same<std::decay_t<T>, short>::value)
			{
				pos+= snprintf(buffer + pos, N - pos, "%hi ", arg);
			}
			else if constexpr(std::is_same<std::decay_t<T>, int>::value)
			{
				pos+= snprintf(buffer + pos, N - pos, "%i ", arg);
			}
			else if constexpr(std::is_same<std::decay_t<T>, long>::value)
			{
				pos+= snprintf(buffer + pos, N - pos, "%li ", arg);
			}
			else if constexpr(std::is_same<std::decay_t<T>, long long>::value)
			{
				pos+= snprintf(buffer + pos, N - pos, "%lli ", arg);
			}
		}
		//TODO: Add support for multi byte character printing (will have to use wsnprinf)
		else if constexpr(std::is_unsigned<std::decay_t<T>>::value)
		{
			if constexpr(std::is_same<std::decay_t<T>, unsigned char>::value)
			{
				if (!isprint(arg))
				{
					pos+= snprintf(buffer + pos, N - pos, "%c ", arg);
				}
				else
				{
					//print this as a number
					pos+= snprintf(buffer + pos, N - pos, "%hhu ", arg);
				}
			}
			else if constexpr(std::is_same<std::decay_t<T>, unsigned short>::value)
			{
				pos+= snprintf(buffer + pos, N - pos, "%hu ", arg);
			}
			else if constexpr(std::is_same<std::decay_t<T>, unsigned int>::value)
			{
				pos+= snprintf(buffer + pos, N - pos, "%u ", arg);
			}
			else if constexpr(std::is_same<std::decay_t<T>, unsigned long>::value)
			{
				pos+= snprintf(buffer + pos, N - pos, "%lu ", arg);
			}
			else if constexpr(std::is_same<std::decay_t<T>, unsigned long long>::value)
			{
				pos+= snprintf(buffer + pos, N - pos, "%llu ", arg);
			}
		}
		else if constexpr(std::is_same<std::decay_t<T>, bool>::value)
		{
			pos+= snprintf(buffer + pos, N - pos, "%s ", arg == true ? "true" : "false");
		}

	}
	else if constexpr(std::is_same<std::decay_t<T>, float>::value)
	{
		pos+= snprintf(buffer + pos, N - pos, "%f ", arg);
	}
	else if constexpr(std::is_same<std::decay_t<T>, double>::value)
	{
		pos+= snprintf(buffer + pos, N - pos, "%lf ", arg);
	}
	else if constexpr(std::is_same<std::decay_t<T>, long double>::value)
	{
		pos+= snprintf(buffer + pos, N - pos, "%Lf ", arg);
	}
	else if constexpr(std::is_pointer<T>::value)
	{
		pos+= snprintf(buffer + pos, N - pos, "%p ", arg);
	}
}


template<typename ...Args>
void printArguments(Args&&... args)
{
	char buffer[1024];
	unsigned int pos = 0;

	(printSingleArgument(std::forward<Args>(args), buffer, pos),...);

	std::cout << buffer << " )" << std::endl;
}

template<typename F, typename ...Args>
void CallFuncPrintArgs(const char* filename,  int line, const char* function, F& f, Args&&... args)
{
	std::cout << filename << ":" << " line: " << line << " function: " << function << " (";
	f(std::forward<Args>(args)...);
	printArguments(std::forward<Args>(args)...);
}

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define CALL(f, args...) CallFuncPrintArgs(__FILENAME__, __LINE__, __FUNCTION__, f, ##args)

