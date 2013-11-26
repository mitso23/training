#ifndef IOSTREAMS_H_
#define IOSTREAMS_H_

#include <iostream>
#include <fstream>
#include <errno.h>
#include <string.h>
#include <sstream>


typedef struct
{
	int x;
	int y;
} Coordinates;

std::ostream& operator<<(std::ostream& stream, Coordinates coord)
{
	stream << "X: " << coord.x << " Y: " << coord.y ;

	return stream;
}


void openReadFile()
{
	ifstream istream("/home/dimitrios/training/resources/testFile.txt");

	if (istream)
	{
		std::cout << "Successfully opened file" << std::endl;
	}
	else
	{
		std::cout << "Failed to open the file: " << strerror(errno) << std::endl;
		return;
	}

	char buffer[10];

#if 0


	//First way of reading
	memset((void*)&buffer, 1, 10);
	istream.get(buffer, 100);


	char c= istream.get();
	unsigned offset= 0;

	while(!istream.eof())
	{
		buffer[offset++]= c;
		c= istream.get();
	}

	buffer[offset]= 0;

	//Second way of reading
	int offset= 0;
	while(!istream.eof())
	{
		istream.read(buffer+offset, 2);

		std::cout << "exctracted " << istream.gcount() << " characters" << std::endl;

		offset+= istream.gcount();
	}
	buffer[offset]= 0;

	//third way of reading bytes (not working)
	std::cout << istream.rdbuf() << std::endl;

#endif

	//fourth way of reading bytes
	while(istream.get(*cout.rdbuf())) { };

}

void seekFile()
{
	ifstream istream("/home/dimitrios/training/resources/testFile.txt");

	if (istream)
	{
		std::cout << "Successfully opened file" << std::endl;
	}
	else
	{
		std::cout << "Failed to open the file: " << strerror(errno)
				<< std::endl;
		return;
	}

	istream.seekg(0, ios::end);
	streampos filesize= istream.tellg();

	std::cout << "file size is " << filesize << std::endl;
	istream.seekg(-filesize/2, ios::end);
	while(istream.get(*cout.rdbuf())) { };


}

void stringStream()
{
	std::istringstream str("1 1.0 Hello");

	int i=0;
	float j=0.0;
	std::string strin;

	str >> i;
	str >> j;
	str >> strin;

	std::cout << "i: " << i << " j: " << j << " str: " << strin << std::endl;
}

#endif
