/*
 * ResourceManagement.h
 *
 *  Created on: Oct 25, 2013
 *      Author: dimitrios
 */

#ifndef RESOURCEMANAGEMENT_H_
#define RESOURCEMANAGEMENT_H_

#include<iostream>
#include<stdio.h>
#include<string.h>
#include<vector>


class Investment
{
public:
	Investment(int x) :
	m_x(x),
	m_stock(NULL)
	{

	}

	int getX() const
	{
		return m_x;
	}

private:
	int m_x;
	int* m_stock;
};

class Factory
{

public:

	Factory()
	{

	}

	virtual Investment* createInvestment()= 0;
};


class InvestmentFactory : public Factory
{

public:
	Investment* createInvestment()
	{
		return new Investment(0);
	}
};


template<typename T>

class SmartPtr
{
public:
	explicit SmartPtr(T resource) :
		m_resource(resource),
		m_refCount(0)
	{

	}

	SmartPtr():
		m_resource(NULL),
		m_refCount(0)
	{

	}

	~SmartPtr()
	{
		if (m_refCount == 0)
		{
			std::cout << "Deleting Resource" << std::endl;

			if (m_resource)
				delete m_resource;
		}
		else
		{
			m_refCount--;
		}

	}

	SmartPtr<T>& operator=(const SmartPtr<T>& rhs)
	{
		m_resource= rhs.m_resource;
		m_refCount= rhs.m_refCount;

		m_refCount++;

		return *this;
	}

	SmartPtr(const SmartPtr<T>& rhs)
	{
		m_resource = rhs.m_resource;
		m_refCount = rhs.m_refCount;

		m_refCount++;
	}

	T operator->()
	{
		return m_resource;
	}

	//HOW TO DO IT
	T operator*()
	{
		return m_resource;
	}

private:
	T m_resource;
	int m_refCount;
};




#endif /* RESOURCEMANAGEMENT_H_ */
