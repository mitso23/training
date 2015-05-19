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
#include <algorithm>
#include <boost/format.hpp>
#include <sstream>
#include <functional>

using namespace std;
using boost::format;

void foo( std::function< void* (void*) > func )
{
    if( func ) // if the call-wrapper has wrapped a callable object
    {
        //typedef void* function_t( void* ) ;
    	typedef void* (*function_t)(void*);

        function_t* ptr_fun = func.target<function_t>() ;
        if( ptr_fun != nullptr )
        {
            // the call-wrapper has wrapped a free function
            // and ptr_fun is a pointer to that function
            // use ptr_fun
        }
        else
        {
            // the callable object wrapped by the call-wrapper is not a free function of this type
            // it is a closure, a function object, a bind expression, or a free function with a
            // different (though compatible) type - for example: int* function_type( const void* ) ;

        }
    }
}


int main(int argc, char* argv[])
{



}



