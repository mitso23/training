#include <iostream>
class Noisy
{
	static long create, assign, copycons, destroy;
	long id;
public:
	Noisy() :
			id(create++)
	{
		std::cout << "d[" << id << "]";
	}
	Noisy(const Noisy& rv) :
			id(rv.id)
	{
		std::cout << "c[" << id << "]";
		copycons++;
	}
	Noisy& operator=(const Noisy& rv)
	{
		std::cout << "(" << id << ")=[" << rv.id << "]";
		id = rv.id;
		assign++;
		return *this;
	}
	friend bool operator<(const Noisy& lv, const Noisy& rv)
	{
		return lv.id < rv.id;
	}
	friend bool operator==(const Noisy& lv, const Noisy& rv)
	{
		return lv.id == rv.id;
	}
	~Noisy()
	{
		std::cout << "~[" << id << "]";
		destroy++;
	}
	friend std::ostream&
	operator<<(std::ostream& os, const Noisy& n)
	{
		return os << n.id;
	}
	friend class NoisyReport;
};
struct NoisyGen
{
	Noisy operator()()
	{
		return Noisy();
	}
};

long Noisy::create= 0;
long Noisy::assign= 0;
long Noisy::copycons= 0;
long Noisy::destroy= 0;


// A singleton. Will automatically report the
// statistics as the program terminates:
class NoisyReport
{
	NoisyReport()
	{
	} // Private constructor

public:
	~NoisyReport()
	{
		std::cout << "\n-------------------\n" << "Noisy creations: "
				<< Noisy::create << "\nCopy-Constructions: " << Noisy::copycons
				<< "\nAssignments: " << Noisy::assign << "\nDestructions: "
				<< Noisy::destroy << std::endl;
	}

	static NoisyReport* getInstance()
	{
		if (nr == NULL)
		{
			nr= new NoisyReport();
			return nr;
		}
		else
		{
			return nr;
		}

	}
private:
	static NoisyReport* nr;
};

NoisyReport* NoisyReport::nr= NULL;
