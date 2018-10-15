/*
 * ResourceManagementModern.h
 *
 *  Created on: 6 Aug 2018
 *      Author: mitso23
 */

#ifndef RESOURCEMANAGEMENTMODERN_H_
#define RESOURCEMANAGEMENTMODERN_H_

#include <memory>

class ResourceManagementModern
{
	ResourceManagementModern()
		: m_resource(std::make_shared<int>())
	{

	}
private:
	std::shared_ptr<int> m_resource;
};

#endif /* RESOURCEMANAGEMENTMODERN_H_ */
