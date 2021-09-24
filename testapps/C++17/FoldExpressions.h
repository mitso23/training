#include <vector>
#include <tuple>

template<typename T, typename... Args>
constexpr std::vector<T> make_vector(Args&&... args)
{
	static_assert((std::is_constructible_v<T, Args&&> && ...));
	std::vector<T> v;
	(...,v.emplace_back(args));
	return v;
}

template<typename ...Args>
void printer(Args&& ... args)
{
	(std::cout << ... << args) << '\n';
}

struct Header
{
	inline static std::string s_name = {"Hello"};
};