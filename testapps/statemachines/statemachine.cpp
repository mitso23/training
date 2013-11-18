/*
 * ipctest.cpp
 *
 *  Created on: Aug 4, 2013
 *      Author: dimitrios
 */

#include<libstatemachine/basicStateMachine.h>
#include <list>

using namespace std;
int main(int argc, char* argv[])
{

	int x= 1;
	list<int> skata;
	list<int>::iterator it;
	skata.push_back(1);
	skata.push_back(2);
	skata.push_back(3);
	skata.push_back(4);
	list<int>::iterator previous= skata.begin();

	for(it=skata.begin(); it!= skata.end();)
	{

		if (x++ == 1)
		{
			x= 1000;
			previous= --it;
			skata.remove(*it);
			it= previous++;
		}
		else
		{
			it++;
		}
	}

}
