#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include "RCObjects.h"

class RefCount
{
public:
	RefCount() : m_refCount(0)
	{

	}

	inline void incRefCount()
	{
		//this could be an atomic increment
		++m_refCount;
	}

	inline unsigned long long decRefCount()
	{
		//this could atomic as well
		return --m_refCount;
	}

private:
	unsigned long long m_refCount;
};

template<class T>
class SmartPtr
{
public:

	SmartPtr(T* realPtr = 0) : m_pointee(realPtr)
	{
		if (m_pointee)
		{
			m_rcObject= new RefCount();
			m_rcObject->incRefCount();
		}
	}

	SmartPtr(const SmartPtr& rhs) : m_pointee(nullptr), m_rcObject(nullptr)
	{
		if(rhs.m_pointee)
		{
			copy(rhs);
		}
	};

	void free()
	{
		if (m_rcObject && (m_rcObject->decRefCount() == 0))
		{
			delete m_pointee;
		}
	}

	void copy(const SmartPtr& rhs)
	{
		m_pointee = rhs.m_pointee;
		m_rcObject = rhs.m_rcObject;
		m_rcObject->incRefCount();
	}

	~SmartPtr()
	{
		free();
	};

	SmartPtr& operator = (const SmartPtr& rhs)
	{
		// They both point to the same thing
		if (rhs.m_pointee == m_pointee)
		{

		}
		else if (!m_pointee)
		{
			copy(rhs);
		}
		else
		{
			free();
			copy(rhs);
		}

		return *this;
	}

	T* operator->() const
	{
		return m_pointee;
	}

	T& operator*() const
	{
		return *m_pointee;
	}

private:
	T* m_pointee;
	RefCount* m_rcObject;
};

#endif /* SMARTPOINTER_H_ */
