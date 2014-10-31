#include <iostream>
#include <utility>
#include <string>
#include <boost/lexical_cast.hpp>


class Noisy
{
	static long create, assign, copycons, destroy;
	long id;
public:
	Noisy() :
			id(create++)
	{
		std::cout << "construct[" << id << "]" << std::endl;
	}
	Noisy(const Noisy& rv) :
			id(rv.id)
	{
		std::cout << "copy[" << id << "]";
		copycons++;
	}

	long getId() const
	{
		return id;
	}

	Noisy(const std::string& str) : id(create++)
	{
		std::cout << "d[" << id << "]";
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

	friend bool operator==(const Noisy& lhs, const std::string& rhs)
	{
		try
		{
			return (lhs.getId() == boost::lexical_cast<long int>(rhs)) ? true : false;
		}
		catch(...)
		{
			return false;
		}

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

	void operator()()
	{
		std::cout << "Running Thread" << std::endl;
		usleep(1);
		std::cout << "Terminating Thread" << std::endl;
	}
};
struct NoisyGen
{
	Noisy operator()()
	{
		return Noisy();
	}
};

long Noisy::create = 0;
long Noisy::assign = 0;
long Noisy::copycons = 0;
long Noisy::destroy = 0;

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
			nr = new NoisyReport();
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

template<class T>
class IncGen
{
public:
	IncGen() :
			m_value(0)
	{

	}
	T operator()()
	{
		return m_value++;
	}

private:
	T m_value;
};

template<class T, class Y>
class PairGen
{
	PairGen() :
			m_key(0), m_value(0)
	{

	}

	std::pair<T, Y> operator()()
	{
		std::pair<T, Y> pair(m_key++, m_value++);
		return pair;
	}

	friend std::ostream& operator <<(std::ostream& stream, PairGen& gen)
	{
		stream << "first: " << gen.m_key << " second: " << gen.m_value;
		return stream;
	}
private:
	T m_key;
	Y m_value;
};

NoisyReport* NoisyReport::nr = NULL;
