#include <iostream>
#include <utility>
#include <string>
#include <boost/lexical_cast.hpp>
#include <string.h>

class Noisy
{
	static long create, assign, copycons, destroy, move;
	long id;
	long int* data;
public:
	Noisy() :
			id(create++),
			data(nullptr)
	{
		std::cout << "construct[" << id << "]" << std::endl;
	}

	Noisy(const Noisy& rv) :
			id(rv.id),
			data(nullptr)
	{
		std::cout << "copy[" << id << "]";
		copycons++;
	}

	Noisy(Noisy&& rv) : id(create), data(rv.data)
	{
		rv.data= nullptr;
		rv.id= 0;
		std::cout << "mov[" << id << "]" << std::endl;
		move++;
	}

	long getId() const
	{
		return id;
	}

	void setData(int _data)
	{
		if (data)
		{
			delete data;
		}

		data= new long int();
		*data= _data;
	}

	int getData() const
	{
		if (data)
		{
			return *data;
		}

		return -1;
	}

	Noisy(const std::string& str) : id(create++), data(nullptr)
	{
		std::cout << "d[" << id << "]";
	}

	Noisy& operator=(const Noisy& rv)
	{
		if (&rv != this)
		{
			long int* newData= nullptr;
			try
			{
				newData= new long int();

			}catch(std::exception& e)
			{
				//if we fail make sure the state of the object doesn't change
				return *this;
			}

			if (data)
			{
				//delete the old data
				delete data;
			}

			std::cout << "(" << id << ")=[" << rv.id << "]";
			id = rv.id;
			memcpy(newData, rv.data, sizeof(long int));
			data= newData;
			assign++;
		}

		return *this;
	}

	Noisy& operator=(Noisy&& rv)
	{
		std::cout << "mov: (" << id << ")=[" << rv.id << "]";
		id = rv.id;
		data= rv.data;
		rv.id= 0;
		rv.data= nullptr;
		move++;
		return *this;
	}

	friend const Noisy& operator + (const Noisy&& lhs, const Noisy&& rhs)
	{
		return lhs;
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
		return os << "id: " << n.id << " data: " << n.getData();
	}

	friend class NoisyReport;

	void operator()()
	{
		std::cout << "Function operator called (doing some work) id " <<  id << std::endl;
		usleep(1);
		std::cout << "Thread execution is being terminated" << std::endl;
	}
};

void swap(Noisy& lhs, Noisy& rhs)
{
	Noisy tmp= std::move(lhs);
	lhs= std::move(rhs);
	rhs= std::move(tmp);
}

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
long Noisy::move= 0;


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
				<< Noisy::destroy << " Move opeartions: " << Noisy::move <<  std::endl;
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
