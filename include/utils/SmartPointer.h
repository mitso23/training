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
	SmartPtr(T* realPtr = 0)
	{
		m_pointee= realPtr;
		m_rcObject= new RefCount();
		m_rcObject->incRefCount();
	}

	SmartPtr(const SmartPtr& rhs) : m_pointee(nullptr), m_rcObject(nullptr)
	{
		if(rhs.m_pointee)
		{
			m_pointee= rhs.m_pointee;
			m_rcObject= rhs.m_rcObject;
			m_rcObject->incRefCount();
		}
	};

	void free()
	{
		if (m_rcObject && (m_rcObject->decRefCount() == 0))
		{
			delete m_pointee;
		}
	}

	~SmartPtr()
	{
		free();
	};

	// make an assignment to a smart ptr
	SmartPtr& operator = (const SmartPtr& rhs)
	{
		if (!rhs.m_pointee)
		{
			//nothing to do
		}
		else if (rhs.m_pointee != m_pointee)
		{
			//free the current resource
			free();
			m_pointee = rhs.m_pointee;
			m_rcObject = rhs.m_rcObject;
			m_rcObject->incRefCount();
		}
		else
		{
			m_rcObject->incRefCount();
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
