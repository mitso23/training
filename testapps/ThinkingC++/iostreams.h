#ifndef IOSTREAMS_H_
#define IOSTREAMS_H_

#include <iostream>
#include <fstream>
#include <errno.h>
#include <string.h>
#include <sstream>
#include <iomanip>


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
	std::stringstream str("1 1.781 Hello ");

	int i=0;
	float j=0.0;
	std::string strin;

	str >> i;
	str >> j;
	str >> strin;
	std::cout << "i: " << i << " j: " << j << " str: " << strin << std::endl;

	str.seekg(0, ios::beg);

	std::cout << str.str() << std::endl;

	stringstream str2;

}

#define D(A) T << #A << endl;
ofstream T("/home/dimitrios/training/resources/format.out");

ostream& nl(ostream& stream)
{
	return stream << "\n";
}

/*
123
100 + 20 + 3 */

int myitoa(unsigned char* ptr)
{
	int sum= 0;
	ptr= ptr + std::string((char*)ptr).length() - 1;

	for(int j=0, i=1; j <= 2; j++, ptr--)
	{
		sum= sum + (*ptr - (int)'0') * i;
		i*= 10;
	}

	return sum;
}

void swap(char* a, char* b)
{
	char temp= *a;
	*a= *b;
	*b= temp;
}

void reverse(char* str)
{
	int length=  std::string(str).length();

	for(int i=0; i < length / 2; i++)
	{
		swap(str, (str + length - 1) - i);
	}
}

char* myatoi(int number)
{
	char* buffer= new char[10];
	int offset= 0;

	int remainder= number;

	while (remainder)
	{
		buffer[offset++]= (remainder % 10) + '0';
		remainder= remainder / 10;
	}

	buffer[offset]= '\0';
	reverse(buffer);
	return buffer;
}

void formatString()
{
	int i= 10;
	std::cout << 1 << std::setw(10) << nl;
}

#endif
