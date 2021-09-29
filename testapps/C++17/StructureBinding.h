#ifndef TRAINING_TESTAPPS_C_17_STRUCTUREBINDING_H_
#define TRAINING_TESTAPPS_C_17_STRUCTUREBINDING_H_
#include <map>
class Customer
{
 private:
	std::string first;
	std::string last;
	long val;
 public:
	Customer(std::string f, std::string l, long v)
		: first{ std::move(f) }, last{ std::move(l) }, val{ v }
	{

	}

	std::string getFirst() const
	{
		return first;
	}

	std::string getLast() const
	{
		return last;
	}

	long getValue() const
	{
		return val;
	}
};

template<>
struct std::tuple_size<Customer>
{
	static constexpr int value = 3;
	// we have 3 attributes
};

template<>
struct std::tuple_element<2, Customer>
{
	using type = long;
// last attribute is a long
};
template<std::size_t Idx>
struct std::tuple_element<Idx, Customer>
{
	using type = std::string;
// the other attributes are strings
};

template<std::size_t I>
auto get(const Customer& c)
{
	static_assert(I < 3);

	if constexpr (I == 0)
	{
		return c.getFirst();
	}
	else if constexpr (I == 1)
	{
		return c.getLast();
	}
	else
	{
		return c.getValue();
	}
}

void ManipulateCustomers()
{
	Customer c{"Tim", "Starr", 42};
	auto& [f, l, v] = c;
	std::cout << "f/l/v: " << f << ' ' << l << ' ' << v << std::endl;
}

void iterateMap()
{
	std::map<int, int> m { std::make_pair(1,1), std::make_pair(2,2)};
	for(auto const& [key, value] : m)
	{
		std::cout << "key: " << key << " value: " << value << std::endl;
	}
}

#endif //TRAINING_TESTAPPS_C_17_STRUCTUREBINDING_H_
