#include <list>
#include <string>
#include <utils/Noisy.h>

using namespace std;

// FIND THE COPPIES
string FindId(list<Noisy> l, string name)
{
	for (list<Noisy>::iterator i = l.begin(); i != l.end();
			/*pass by reference ++it is faster as no temporary is created*/i++)
	{
		//the compiler will call ctor to create a Noisy from string
		//make the constructor explicit if you want to disable it and implement
		//operator == (const Noisy& lhs, const std::string& str)
		if (*i == name)
		{
			return "equal";
			//return (*i).getId();
		}
	}

	//another explicit copy , should return std::string;
	return "";
}

//A WAY MORE OPTIMISED VERSION
string FindIdOptimised(const list<Noisy>& l, const string& name)
{
	//this enables compiler return value optimisation as there is only one path (copy directly to the user address)
	std::string str;

	for (list<Noisy>::const_iterator i = l.begin(); i != l.end();
			/*pass by reference ++it is faster as no temporary is created*/++i)
	{
		//Implemented operator == (const Noisy& lhs, const std::string& str) to avoid copying
		if (*i == name)
		{
			str= "equal";
			//return (*i).getId();
		}
	}

	//fixed explicit ctor
	return std::string();
}
