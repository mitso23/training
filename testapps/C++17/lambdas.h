#ifndef TRAINING_TESTAPPS_C_17_LAMBDAS_H_
#define TRAINING_TESTAPPS_C_17_LAMBDAS_H_

constexpr auto normalFunc(const char* str)
{
	unsigned hash = 5567;

	while(*str)
	{
		hash = hash << 2 ^*str++;
	}

	return hash;
}

auto strHasher = [](const char* str) constexpr
{
	unsigned int val = 0;
	while(*str)
	{
		val|= *str++;
		val<<= 5;
	}

	return val;
};

struct Message
{
	explicit constexpr Message(const char* name)
		:m_name(name)
	{

	}

 public:
	const char* m_name;
};

enum Hashed
{
	one = strHasher("one"),
	two [[maybe_unused]] = strHasher("two"),
	three [[maybe_unused]] = strHasher("three"),
};

#endif //TRAINING_TESTAPPS_C_17_LAMBDAS_H_
