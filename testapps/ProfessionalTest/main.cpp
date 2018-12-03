/*
 * main.cpp
 *
 *  Created on: 29 Apr 2018
 *      Author: mitso23
 */

//#include "CorruptedFile.h"
//#include "WindowManager.h"
//#include "Autocorrection.h"
#include "MemoryAllocator.h"

#include <vector>
#include <string.h>
#include <memory>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <unordered_set>

FILE* fp = nullptr;

bool isLowerCase(const std::string& word)
{
	for(unsigned int i=0; i< word.size(); ++i)
	{
		if (word[i] < 'a' || word[i] > 'z')
		{
			return false;
		}
	}

	return true;
}

int main(int argc, char* argv[])
{

#if 0
	fp = fopen("/tmp/debug.txt", "w");
	if (!fp)
	{
		std::cout << "SHIT" << std::endl;
		return 0;
	}

	CreateTestData();
	FindMissingFileContentsOptimized();
	//FindMissingFileContents();
	std::cout << "numberOfReadsFromFile: " << numberOfReadsFromFile
			<< " numberOfReadsFromCurruptedFile: "
			<< numberOfReadsFromCurruptedFile << std::endl;
#endif

#if 0
	DrawCoordinateSystem(50, 50);
	Rectangle rec1(Coordinate(10, 20), 10, 5);
	DrawRectangle(rec1, 1);
	Rectangle rec2(Coordinate(30, 20), 5, 5);
	DrawRectangle(rec2, 2);
	Rectangle rec3(Coordinate(30, 40), 10, 8);
	DrawRectangle(rec3, 3);
	Rectangle rec4(Coordinate(2, 2), 50, 40);
	DrawRectangle(rec4, 4);
	Move(4, 2, 45);
	Move(3, 30, 30);
	Front(3)

	for(unsigned int i=0; i< 10000; ++i)
		Move(3, 30, 70 + i%20);
#endif

#if 0
	Trie trie;
	Hash hash;
	std::unordered_set<const char* > set;

	// Do a write
	{
		std::ifstream f("/usr/share/dict/british-english");

		while(f)
		{
			//static int i = 0;

			std::string word;
			f >> word;
			if (!isLowerCase(word))
			{
				continue;
			}
			//std::cout << "adding word: " << word <<  "count: " << i++ << std::endl;

			trie.AddWord(word.c_str());
			//hash.AddWord(word.c_str());
			//set.insert(word.c_str());
		}
	}

	// Do a read
	{
		std::ifstream f("/usr/share/dict/british-english");

		while(f)
		{
			//static int i = 0;

			std::string word;
			f >> word;
			if (!isLowerCase(word))
			{
				continue;
			}
			//std::cout << "adding word: " << word <<  "count: " << i++ << std::endl;
			if (!trie.CheckWordExists(word.c_str()))
			//if (!hash.CheckWordExists(word.c_str()))
			//if (set.find(word.c_str()) == set.end())
			{
				//std::cerr << "word doesn't exist: " << word << std::endl;
			}
			else
			{
				//std::cerr << "word exist: " << word << std::endl;
			}
		}
	}
#endif

Allocator allocator(100);
auto ptr1 = allocator.Allocate(7);
auto ptr2 = allocator.Allocate(9);
//auto ptr3 = allocator.Allocate(16);
//auto ptr4 = allocator.Allocate(8);
//auto ptr5 = allocator.Allocate(15);

allocator.Free(ptr1);
auto ptr6 = allocator.Allocate(7);

}
