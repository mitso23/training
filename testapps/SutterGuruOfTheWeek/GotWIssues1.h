#include <list>
#include <string>
#include <vector>
#include <algorithm>
#include <complex>
#include <utils/Noisy.h>

using namespace std;

// FIND THE COPPIES
string FindId(list<Noisy> l, string name)
{
	for (list<Noisy>::iterator i = l.begin(); i != l.end();
			/*pass by reference ++it is faster as no temporary is created*/i++)
	{
		//the compiler will call ctor to create a Noisy from string
		//make the constructor explicit if you want to disable it and implement
		//operator == (const Noisy& lhs, const std::string& str)
		if (*i == name)
		{
			return "equal";
			//return (*i).getId();
		}
	}

	//another explicit copy , should return std::string;
	return "";
}

//A WAY MORE OPTIMISED VERSION
string FindIdOptimised(const list<Noisy>& l, const string& name)
{
	//this enables compiler return value optimisation as there is only one path (copy directly to the user address)
	std::string str;

	for (list<Noisy>::const_iterator i = l.begin(); i != l.end();
			/*pass by reference ++it is faster as no temporary is created*/++i)
	{
		//Implemented operator == (const Noisy& lhs, const std::string& str) to avoid copying
		if (*i == name)
		{
			str= "equal";
			//return (*i).getId();
		}
	}

	//fixed explicit ctor
	return std::string();
}


//The most correct version
//A WAY MORE OPTIMISED VERSION
string FindIdStl(list<Noisy>& l, const string& name)
{
	//this enables compiler return value optimisation as there is only one path (copy directly to the user address)
	std::string str;
	list<Noisy>::const_iterator iter= find(l.begin(), l.end(), name);

	//return (iter != l.end()) ? (*iter).addr : std::string();

	//fixed explicit ctor
	return std::string();
}

///FIND THE ERRORS
#if 0
class Complex
{
public:
	Complex( double real, double imaginary = 0 )
	: _real(real), _imaginary(imaginary)
	{};

	void operator+ ( Complex other )
	{
		_real = _real + other._real;
		_imaginary = _imaginary + other._imaginary;
	}

	void operator<<( ostream os )
	{
		os << "(" << _real << "," << _imaginary << ")";
	}

	Complex operator++()
	{
		++_real;
		return *this;
	}

	Complex operator++( int )
	{
		Complex temp = *this;
		++_real;
		return temp;
	}

private:
	double _real, _imaginary;
};
#endif

class Complex
{
public:
	Complex(double real, double imaginary = 0) :
			_real(real), _imaginary(imaginary)
	{

	};

	Complex operator += (const Complex& other)
	{
		return Complex(_real + other._real, _imaginary + other._imaginary);
	}

	Complex& operator++()
	{
		++_real;
		return *this;
	}

	//Avoid using a++++
	const Complex operator++(int)
	{
		Complex temp = *this;
		++(*this);
		return temp;
	}

	ostream& print(ostream& os) const
	{
		os << "(" << _real << "," << _imaginary << ")";
		return os;
	}

private:
	double _real, _imaginary;
};

const Complex operator + (const Complex& lhs, const Complex& rhs)
{
	Complex temp(lhs);
	temp += rhs;
	return temp;
}

ostream& operator << (ostream& os, const Complex& complex)
{
	os << complex.print(os);
	return os;
}

class Base
{
public:
	virtual void f(int)
	{
		cout << "Base::f(int)" << endl;
	}

	virtual void f(double)
	{
		cout << "Base::f(double)" << endl;
	}

	virtual void g(int i = 10)
	{
		cout << i << endl;
	}
};

class Derived: public Base
{
public:
	void f(complex<double>)
	{
		cout << "Derived::f(complex)" << endl;
	}

	void g(int i = 20)
	{
		cout << "Derived::g() " << i << endl;
	}
};

#if 0
class Polygon
{
public:
	Polygon() : area_(-1)
	{}

	//this needs const reference
	void AddPoint( const Point pt )
	{
		InvalidateArea();
		points_.push_back(pt);
	}

	//we can return a const reference
	//if we return a value we still need to return it as constl
	Point GetPoint( const int i )
	{
		return points_[i];
	}

	//this can be a const function but return should not be const
	int GetNumPoints()
	{
		return points_.size();
	}

	//there is no reason for this function to return const as primitive types are rvalue
	//This function should be const even if it modifies internal state. area_ should be marked as mutable
	//as this function is conseptually const.
	double GetArea()
	{
		if( area_ < 0 ) // if not yet calculated and cached
		CalcArea();// calculate now
		return area_;
	}

private:
	void InvalidateArea()
	{	area_ = -1;}

	//This function should be marked as const and the iterator const
	void CalcArea()
	{
		area_ = 0;
		vector<Point>::iterator i;
		//for( i = points_.begin(); i != points_.end(); ++i )
		//area_ += /* some work */;
	}

	vector<Point> points_;
	double area_;	//mark it as mutable
};

//return value and parameters should be const
Polygon operator+( Polygon& lhs, Polygon& rhs )
{
	Polygon ret = lhs;
	int last = rhs.GetNumPoints();		//this should be const as well
	for( int i = 0; i < last; ++i )// concatenate
	ret.AddPoint( rhs.GetPoint(i) );
	return ret;
}

//WTF ??
void f( const Polygon& poly )
{
	const_cast<Polygon&>(poly).AddPoint( Point(0,0) );
}

// const is useless here as you can't change the reference
void g(Polygon& const rPoly )
{
	//rPoly.AddPoint( Point(1,1) );
}

//Again const is useless as the pointer is passed by value (copied to the stack)
void h( Polygon* const pPoly )
{
	pPoly->AddPoint( Point(2,2) );
}
#endif

void testVirtualOverride()
{
	Base b;
	Derived d;
	Base* pb = new Derived;

	//b.f(1.0);
	//d.f(1.0);
	//pb->f(1.0);

	b.g();
	d.g();
	pb->g();

	//delete pb;
}

