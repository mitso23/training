#include <stddef.h>


//This is naive implementation

template<typename T>
class SArray
{
public:
	// create array with initial size
	explicit SArray(size_t s) :
			storage(new T[s]), storage_size(s)
	{
		init();
	}
	// copy constructor
	SArray(SArray<T> const& orig) :
			storage(new T[orig.size()]), storage_size(orig.size())
	{
		copy(orig);
	}
	// destructor: free memory
	~SArray()
	{
		delete[] storage;
	}
	// assignment operator
	SArray<T>& operator=(SArray<T> const& orig)
	{
		if (&orig != this)
		{
			copy(orig);
		}
		return *this;
	}
	// return size
	size_t size() const
	{
		return storage_size;
	}
	// index operator for constants and variables
	T operator[](size_t idx) const
	{
		return storage[idx];
	}
	T& operator[](size_t idx)
	{
		return storage[idx];
	}
protected:
	// init values with default constructor
	void init()
	{
		for (size_t idx = 0; idx < size(); ++idx)
		{
			storage[idx] = T();
		}
	}
	// copy values of another array
	void copy(SArray<T> const& orig)
	{
		assert(size() == orig.size());
		for (size_t idx = 0; idx < size(); ++idx)
		{
			storage[idx] = orig.storage[idx];
		}
	}
private:
	T* storage;       // storage of the elements
	size_t storage_size;  // number of elements
};

// exprtmpl/sarrayops1.hpp
// addition of two SArrays
template<typename T>
SArray<T> operator+(SArray<T> const& a, SArray<T> const& b)
{
	SArray<T> result(a.size());
	for (size_t k = 0; k < a.size(); ++k)
	{
		result[k] = a[k] + b[k];
	}
	return result;
}

// multiplication of two SArrays
template<typename T>
SArray<T> operator*(SArray<T> const& a, SArray<T> const& b)
{
	SArray<T> result(a.size());
	for (size_t k = 0; k < a.size(); ++k)
	{
		result[k] = a[k] * b[k];
	}
	return result;
}

// multiplication of scalar and SArray
template<typename T>
SArray<T> operator*(T const& s, SArray<T> const& a)
{
	SArray<T> result(a.size());
	for (size_t k = 0; k < a.size(); ++k)
	{
		result[k] = s * a[k];
	}
	return result;
}

#if 0
// additive assignment of SArray
template<class T>
SArray<T>& SArray<T>::operator+= (SArray<T> const& b)
{
    for (size_t k = 0; k<size(); ++k) {
        (*this)[k] += b[k];
    }
    return *this;
}
// multiplicative assignment of SArray
template<class T>
SArray<T>& SArray<T>::operator*= (SArray<T> const& b)
{
    for (size_t k = 0; k<size(); ++k) {
        (*this)[k] *= b[k];
    }
    return *this;
}
// multiplicative assignment of scalar
template<class T>
SArray<T>& SArray<T>::operator*= (T const& s)
{
    for (size_t k = 0; k<size(); ++k) {
        (*this)[k] *= s;
    }
    return *this;
}
#endif
