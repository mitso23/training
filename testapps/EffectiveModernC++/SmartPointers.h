#ifndef SMARTPOINTERS_H_
#define SMARTPOINTERS_H_

#include "utils/Noisy.h"

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

//This makes this code exception safe in this scenario
// processWidget(std::shared_ptr<Widget>(new Widget), computePriority());
template<typename T,typename ...Ts>
std::unique_ptr<T> make_unique(Ts&&... arguments)
{
	return std::unique_ptr<T>(new T(std::forward<Ts>(arguments)...));
}

void MoveSharedPtr()
{
	// This will create a control block
	std::shared_ptr<Noisy> x(new Noisy());

	// This will move the control block from X->Y
	std::shared_ptr<Noisy> y= std::move(x);

	if (!x)
	{
		std::cout << "x is null: " << std::endl;
	}

	// This will move the control block for y -> z
	std::shared_ptr<Noisy> z(std::move(y));

	// this will destroy old contents of z and replace it with a new Noisy client
	z= std::shared_ptr<Noisy>(new Noisy);
}

// NOTE: This will work only if Noisy is created using std::make_shared or shared_ptr<Noisy2>
class Noisy2 : public Noisy, public std::enable_shared_from_this<Noisy2>
{
public:
	void CreateAnotherBlock()
	{
		std::shared_ptr<Noisy2> n(shared_from_this());
	}

	template<typename... Ts>
	static std::shared_ptr<Noisy2> create(Ts&&... params)
	{
		return std::shared_ptr<Noisy2>(new Noisy2());
	}

private:
	Noisy2() = default;
};

class IListener
{

public:
	virtual void notify() const = 0;
};

class CListener : public IListener
{

public:
	void notify() const
	{
		std::cout << "notifying" << std::endl;
	}

	static std::shared_ptr<IListener> create()
	{
		return std::shared_ptr<IListener>(new CListener());
	}

private:
	CListener() = default;
};

class Observer
{
public:
	void AddListener(const std::shared_ptr<const IListener>& listener)
	{
		// NOTE: Use a weak ptr in order not to extend the lifetime of the object
		// Once the object goes out of scope
		m_listeners.push_back(std::weak_ptr<const IListener>(listener));
	}

	void Notify()
	{
		auto listener = m_listeners.front();
		if (auto l = listener.lock())
		{
			l->notify();
		}
		else
		{
			m_listeners.pop_back();
		}
	}

private:
	std::vector<std::weak_ptr<const IListener>> m_listeners;
	Observer(const Observer&) = delete;
	Observer& operator = (const Observer& ) = delete;
};

void testSharedFromThis()
{
	std::shared_ptr<Noisy2> p(Noisy2::create());
	p->CreateAnotherBlock();
}

void testMakeUniquePtr()
{
	auto ptr = make_unique<Noisy>();
}

void testInitializerListMakeSharedPtr()
{
	auto initList = { 1, 2 };
	auto sharedPtr = std::make_shared<std::vector<int>>(initList);
}

void MoveAutoPtrInContainer()
{
	std::vector<std::unique_ptr<int>> vec;

	vec.push_back(make_unique<int>(1));
	vec.push_back(make_unique<int>(2));

	auto x = std::move(vec.front());
	auto& y = vec.front();

	std::cout << "vector size is " << vec.size() << std::endl;
}


#endif /* SMARTPOINTERS_H_ */
