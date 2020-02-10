/*
 * PolicyBasedDesign.h
 *
 *  Created on: Feb 3, 2020
 *      Author: mitso23
 */

#ifndef TESTAPPS_MODERNC__DESIGN_POLICYBASEDDESIGN_H_
#define TESTAPPS_MODERNC__DESIGN_POLICYBASEDDESIGN_H_

#include <stdlib.h>
#include <iostream>

template <typename T>
struct NewCreator
{
	T* Create()
	{
		return new T();
	}

protected:
	/**
	 * This will not allow clients calling the destructor of the class manually
	 * since the policy class will be inherited
	 */
	~NewCreator()
	{

	}
};

template<>
struct NewCreator<int>
{
	int* Create()
	{
		std::cout << "Calling the override method" << std::endl;
		return new int;
	}
};


template <typename T>
struct MallocCreator
{
	T* Create()
	{
		char* memory = malloc(sizeof(T));
		return new(memory)T();
	}
};


template <class CreationPolicy>
struct WidgetManager : private CreationPolicy
{
	WidgetManager()
	{
		auto ptr = this->Create();
		std::cout << "value: " << *ptr << std::endl;
	}
};

class Widget;

template < template <typename Object> class CreationPolicy>
struct ImprovedWidgetManager : private CreationPolicy<Widget>
{

};

template <class T>
class DefaultSmartPtrStorage
{
public:
	typedef T* PointerType;
	typedef T& ReferenceType;

protected:
	PointerType GetPointer() const { return m_ptr; }
	void SetPointerType(PointerType ptr) { m_ptr = ptr; }

private:
	PointerType* m_ptr;
};

template
< typename T,
  template <class> class CheckingPolicy,
  template <class> class ThreadingModel,
  template <class> class Storage = DefaultSmartPtrStorage
 >
class SmartPtr
{

};




#endif /* TESTAPPS_MODERNC__DESIGN_POLICYBASEDDESIGN_H_ */
