#ifndef RCOBJECTS_H
#define RCOBJECTS_H

class RCObject
{
public:
	//It will be the responsibility of the application code to increment the refCount
	RCObject() : m_refCount(0), m_shareable(true)
	{

	};

	//It will be the responsibility of the application code to increment the refCount
	RCObject(const RCObject& rhs) : m_refCount(0), m_shareable(true)
	{

	}

	/**
	 * Imagine a situation where we have StringValue n1
	 * and StringValue n2 there are a number of strings pointing to n1 and a
	 * number of strings pointing to n2 if we do n1=n2  then we don't want to change the
	 * refCount numbers of n1 and n2
	 */
	RCObject& operator=(const RCObject& rhs)
	{
		return *this;
	}

	/**
	 * pure virtual destructor means that the object is an interface class
	 * and will be force to be created on the heap
	 */
	virtual ~RCObject() = 0;

	void addReference()
	{
		++m_refCount;
	}

	/**
	 * We know that the object will be created on the heap only
	 * so it is safe here to call delete this
	 */
	void removeReference()
	{
		if (((m_refCount > 0) && (--m_refCount == 0)) || m_refCount == 0)
		{
			delete this;
		}
	}

	void markUnshareable()
	{
		m_shareable= false;
	}

	bool isShareable() const
	{
		return m_shareable;
	}

	bool isShared() const
	{
		return (m_refCount > 1);
	}
private:
	int m_refCount;
	bool m_shareable;
};

RCObject::~RCObject()
{

}

template<class T>
class RCPtr
{
public:
	RCPtr(T* realPtr = 0) : m_pointee(realPtr)
	{
		if(m_pointee)
			m_pointee->addReference();
	}

	RCPtr(const RCPtr& rhs) : m_pointee(nullptr)
	{
		if(rhs.m_pointee && rhs.m_pointee->isShareable())
		{
			m_pointee= rhs.m_pointee;
			m_pointee->addReference();
		}
		else if (rhs.m_pointee)
		{
			//We need to perform a deep copy in this case
			m_pointee= new T();

			//NOTE: by default the new pointee will be sharable
			*m_pointee= *rhs.m_pointee;

			//increment the reference count showing that we point to a valid object
			m_pointee->addReference();
		}
	}

	~RCPtr()
	{
		m_pointee->removeReference();
	}

	RCPtr& operator = (const RCPtr& rhs)
	{
		if (&rhs == this)
		{
			return *this;
		}

		if (rhs.m_pointee && rhs.m_pointee->isShareable())
		{
			m_pointee= rhs.m_pointee;
			m_pointee->addReference();
		}
		else if (rhs.m_pointee)
		{
			//We need to perform a deep copy in this case
			m_pointee = new T(*rhs.m_pointee);

			//increment the reference count showing that we point to a valid object
			m_pointee->addReference();
		}
		else
		{
			m_pointee= nullptr;
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

	void init();
};


#endif /* RCOBJECTS_H_ */
