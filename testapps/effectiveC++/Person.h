#include "DateFwd.h"
#include "PersonImpl.h"


class Person
{

	std::string getPersonName();

	//For some reason this work  (COMPLILER DOESN"T NEED TO KNOW THE SIZE HERE)
	Date getDate();
	void setDate(Date d);

private:
	Date* date;				//For some reason Date date doesn't work, as C++ need to know the size
							//of the structure
	PersonImpl* impl;		//Use Pimpl idiom to minimize compilation dependencies

	//Date date2;			//THIS WILL NOT WORK AS COMPILER NEED TO KNOW THE SIZE
};

