/*
 * Various.cpp
 *
 *  Created on: 19 Jan 2015
 *      Author: dimka231
 */


#include <libeconomics/interestcalc.h>
#include <utils/generic_handles.h>
#include <utils/Noisy.h>

#include <iostream>
#include <string>
#include <vector>
#include <iterator>

using namespace std;

int main(int argc, char* argv[])
{
	//std::cout << "Total number of years " << calculateNumYearsUntilRepaiment(215000, 0.04, 1200*12) << std::endl;
	std::cout << "monthly payment " << caclulateYearlyRepaiments(215000, 0.0234, 25) / 12 << std::endl;

	std::cout << pow(8,1.0/3.0) << std::endl;
}



