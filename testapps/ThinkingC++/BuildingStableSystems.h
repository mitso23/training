#ifndef BUILDINGSTABLESYSTEMS_H_
#define BUILDINGSTABLESYSTEMS_H_

#include<vector>


//Reference counted memory leak checker
class LeakChecker
{
	int count;
public:
	LeakChecker() :
			count(0)
	{
	}

	void print()
	{
		std::cout << count << std::endl;
	}

	~LeakChecker()
	{
		print();
	}

	void operator++(int)
	{
		count++;
	}

	void operator--(int)
	{
		count--;
	}
};

class BicyclePart
{
	static LeakChecker lc;

public:
	BicyclePart()
	{
		lc++;
	}

	BicyclePart(const BicyclePart&)
	{
		lc++;
	}

	BicyclePart operator =(const BicyclePart& rhs)
	{
		lc++;
		return rhs;
	}

	virtual BicyclePart* clone() = 0;

	virtual ~BicyclePart()
	{
		lc--;
	}

	friend std::ostream& operator<<(std::ostream& os, BicyclePart* bp)
	{
		return os << typeid(*bp).name();
	}

	friend class Bicycle;
};

enum BPart
{
	Frame, Wheel, Seat, HandleBar, Sprocket, Deraileur,
};

//Factory class for creating bicycles
template<BPart id>
class Part: public BicyclePart
{
public:
	BicyclePart* clone()
	{
		return new Part<id> ;
	}
};


class Bicycle
{
public:
	Bicycle()
	{

	}

	Bicycle(const Bicycle& old)
	{

	}

	Bicycle& operator =(const Bicycle& old)
	{
		return old;
	}

private:
	typedef std::vector<BicyclePart* > parts;
};

struct BicycleGenerator
{
	Bicycle* operator ()()
	{
		return new Bicycle();
	}
};

#endif /* BUILDINGSTABLESYSTEMS_H_ */
