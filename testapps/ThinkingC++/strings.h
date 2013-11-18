#ifndef STRINGS_H_
#define STRINGS_H_

#include<string>
using namespace std;

void stringRefCount()
{
	string temp;
	temp= "Hello World";

	string::iterator it= temp.begin();
	string temp2(temp.begin(), temp.end());

	//This will affect only the first string as it uses deep copy
	*it='M';

	cout << "string1: " << temp << endl;
	cout << "string2: " << temp2 << endl;
}


#endif /* STRINGS_H_ */
