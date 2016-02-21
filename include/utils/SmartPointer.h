#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include "RCObjects.h"
#include <functional>

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
	typedef std::function<void (T*)> del_funct_t;
public:

	explicit SmartPtr() : m_pointee(nullptr), m_rcObject(nullptr)
	{

	}

	template <typename Y>
	explicit SmartPtr(Y* realPtr) : m_pointee(realPtr)
	{
		m_rcObject = new RefCount();
		m_rcObject->incRefCount();
	}

	template<typename Y>
	SmartPtr(const SmartPtr<Y>& rhs) : m_pointee(nullptr), m_rcObject(nullptr)
	{
		if(rhs.m_pointee)
		{
			copy(rhs);
		}
	};

	~SmartPtr()
	{
		free();
	};

	template <typename Y>
	SmartPtr& operator = (const SmartPtr<Y>& rhs)
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

	bool operator !() const
	{
		return !m_pointee;
	}

	operator bool() const
	{
		return m_pointee == nullptr;
	}

	void reset(T* pointee)
	{
		if (m_pointee)
		{

		}
	}

	template<typename K, class ... Args>
	friend SmartPtr<K> my_make_shared(Args&& ... args)
	{
		construct_once<K>* mem= new construct_once<K>(args...);
	}

	void free()
	{
		if (m_rcObject && (m_rcObject->decRefCount() == 0))
		{
			delete m_pointee;
			delete m_rcObject;

			m_pointee= nullptr;
			m_rcObject= nullptr;
		}
	}

	void copy(const SmartPtr& rhs)
	{
		m_pointee = rhs.m_pointee;
		m_rcObject = rhs.m_rcObject;
		m_rcObject->incRefCount();
	}

private:
	template<typename K>
	struct construct_once
	{
		K object;
		RefCount refCount;

		template<class ... Args>
		construct_once(Args&& ... args) :
				object(args...)
		{
		}
	};

	template<typename K>
	SmartPtr(struct construct_once<K>* mem) : m_pointee(nullptr), m_rcObject(nullptr)
	{
		m_pointee= &mem->object;
		m_rcObject= &mem->refCount;
	}

	T* m_pointee;
	RefCount* m_rcObject;
	del_funct_t* ptr;
};

#endif /* SMARTPOINTER_H_ */
