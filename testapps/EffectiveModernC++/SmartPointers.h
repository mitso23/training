#ifndef SMARTPOINTERS_H_
#define SMARTPOINTERS_H_

#include <memory>


class Investment
{
public:
	Investment(int x)
	{

	}
};

class Stock : public Investment
{
public:
	template <typename... Ts>
	static std::unique_ptr<Investment> makeInvestment(Ts&&... arguments)
	{
		return std::unique_ptr<Investment>(new Stock(std::forward<Ts>(arguments)...));
	}

private:
	Stock(int x) : Investment(x)
	{

	}
};




#endif /* SMARTPOINTERS_H_ */
