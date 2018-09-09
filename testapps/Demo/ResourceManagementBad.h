/*
 * ResourceManagementBad.h
 *
 *  Created on: 5 Aug 2018
 *      Author: mitso23
 */

#ifndef RESOURCEMANAGEMENTBAD_H_
#define RESOURCEMANAGEMENTBAD_H_


#include <iostream>

class ResourceManagementBad
{
	ResourceManagementBad(size_t size)
		: m_ptr(new int[m_size])
		, m_size(size) { }

	~ResourceManagementBad()
	{
		delete m_ptr;
	}

private:
	size_t m_size;
	int* m_ptr;
};


#endif /* RESOURCEMANAGEMENTBAD_H_ */
