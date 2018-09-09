/*
 * ResourceManagementGreat.h
 *
 *  Created on: 5 Aug 2018
 *      Author: mitso23
 */

#ifndef RESOURCEMANAGEMENTGREAT_H_
#define RESOURCEMANAGEMENTGREAT_H_

class ResourceManagementGreat
{
public:

	// exception safe swap
	friend void swap(ResourceManagementGreat& rhs, ResourceManagementGreat& lhs)
	{
		std::swap(rhs.m_ptr, lhs.m_ptr);
		std::swap(rhs.m_size, lhs.m_size);
	}

	//constructor
	explicit ResourceManagementGreat(unsigned int size)
		: m_size(size),
		  m_ptr(new int[m_size])
	{

	}

	//copy constructor
	ResourceManagementGreat(const ResourceManagementGreat& rhs)
		: m_size(rhs.m_size),
		  m_ptr(nullptr)
	{
		ResourceManagementGreat temp(m_size);
		swap(temp, *this);
	}

	//Move constructor
	ResourceManagementGreat(ResourceManagementGreat&& rhs)
		: m_size(rhs.m_size)
		, m_ptr(rhs.m_ptr)
	{
		rhs.m_size = 0;
		rhs.m_ptr = nullptr;
	}


	//assignment operator
	ResourceManagementGreat& operator = (const ResourceManagementGreat& rhs)
	{
		ResourceManagementGreat temp(rhs);
		swap(temp, *this);

		return *this;
	}

	~ResourceManagementGreat()
	{
		delete[] m_ptr;
		m_size= 0;
	}

private:
	unsigned int m_size;
	int* m_ptr;
};


#endif /* RESOURCEMANAGEMENTGREAT_H_ */
