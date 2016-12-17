#ifndef SMARTPOINTERS_H_
#define SMARTPOINTERS_H_

#include <memory>
#include <iostream>


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

void MoveSharedPtr()
{
	std::shared_ptr<int> x(new int(1));
	std::shared_ptr<int> y= std::move(x);
	std::shared_ptr<int> z(std::move(y));

	std::cout << "y:" << *y << std::endl;


}




#endif /* SMARTPOINTERS_H_ */
