/*
 * main.cpp
 *
 *  Created on: 29 Apr 2018
 *      Author: mitso23
 */

//#include "CorruptedFile.h"
//#include "WindowManager.h"
#include "Autocorrection.h"
//#include "MemoryAllocator.h"
//#include "Autocomplete.h"
#include "Pipeline.h"
#include "Primitives.h"


#include <vector>
#include <string.h>
#include <memory>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::AtLeast;
using ::testing::Return;
using ::testing::_;


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

TEST(Performance, Skata)
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
    TernaryTree tree;


    tree.insert("acclimatisation");
    tree.insert("acclimatise");
    tree.insert("acclimatised");
        tree.insert("acclimatises");
    tree.insert("acclimatising");
    tree.insert("B");
    tree.insert("C");
    tree.insert("Z");

    tree.insert("Hello");
    tree.insert("Helz");
    tree.insert("Helmet");
    tree.insert("Helsinki");
    tree.insert("Helping");

    TernaryTree::FindResult result = tree.find("acclimatise");
    if (result.found)
    {
        std::cout << "Found it";
        tree.traverse(result.lastNode);
    }
    else
    {
        std::cout << "Shit: " << std::endl;
        tree.traverse(result.lastNode);
    }
#endif


#if 0
    Trie trie;
    //Hash hash;
    //std::unordered_set<const char* > set;
    //TernaryTree ternaryTree;


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
            //set.emplace(word.c_str());
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
                std::cerr << "word doesn't exist: " << word << std::endl;
            }
            else
            {
                //std::cerr << "word exist: " << word << std::endl;
            }
        }

        //hash.PrintAllWords();
        //trie.PrintAllWords();
    }
#endif

#if 0
    TestOneFullAllocation();
    TestTwoBackToBackAllocationsFreeInOrder();
    TestTwoBackToBackAllocationsFreeOutOfOrder();
    TestFourAllocationsFree2AllocateMore();
#endif
}

TEST(List, sortedOperations)
{
    pipeline::SimpleAllocator::Initialize();

    pipeline::List list;
    pipeline::Lot l1;
    l1.time = 5;
    l1.toolId = 0;

    pipeline::Lot l2;
    l2.time = 10;
    l2.toolId = 1;

    pipeline::Lot l3;
    l3.time = 7;
    l3.toolId = 1;

    pipeline::Lot l4;
    l4.time = 3;
    l4.toolId = 1;


    //first insertion
    list.AddSorted(l1);

    //insertion to the end
    list.AddSorted(l2);

    list.RemoveItem(list.head);

    //insertion to middle
    list.AddSorted(l3);

    list.RemoveItem(list.head->next);

    //insertion to beginning
    list.AddSorted(l4);

    list.RemoveItem(list.tail);
    list.Print();

    //list.Clear();
}

TEST(List, merge)
{
   pipeline::SimpleAllocator::Initialize();

   pipeline::List list1;
   pipeline::List list2;

   pipeline::Lot l1;
   l1.time = 5;
   l1.toolId = 0;

   pipeline::Lot l2;
   l2.time = 10;
   l2.toolId = 0;


   list2.AddSorted(l1);

   list2.MergeList(&list1);
   list2.AddEnd(l2);

   list2.Print();
}

TEST(Pipeline, oneStageTwoToolsOneItem)
{

    int stages[2] = { 0, 0 };
    int processingTime[] = { 5, 10 };
    int wip[1];

    pipeline::init(1);
    pipeline::setupTool(2, stages, processingTime);
    pipeline::AddLot(1);

    ASSERT_EQ(0, pipeline::Simulate(2, wip));
    ASSERT_EQ(1, wip[0]);

    ASSERT_EQ(1, pipeline::Simulate(5, wip));
    ASSERT_EQ(0, wip[0]);

}


TEST(Pipeline, twoStagesTwoToolsOneItem)
{

    int stages[4] = { 0, 0, 1, 1 };
    int processingTime[] = { 5, 10, 5, 5 };
    int wip[1];

    pipeline::init(2);
    pipeline::setupTool(4, stages, processingTime);
    pipeline::AddLot(1);

    ASSERT_EQ(0, pipeline::Simulate(5, wip));
    ASSERT_EQ(0, wip[0]);
    ASSERT_EQ(1, wip[1]);

    ASSERT_EQ(0, pipeline::Simulate(7, wip));
    ASSERT_EQ(0, wip[0]);
    ASSERT_EQ(1, wip[1]);

    ASSERT_EQ(1, pipeline::Simulate(10, wip));
    ASSERT_EQ(0, wip[0]);
    ASSERT_EQ(0, wip[1]);

}

TEST(Pipeline, twoStagesTwoToolsTwoItem)
{

    int stages[4] = { 0, 0, 1, 1 };
    int processingTime[] = { 5, 10, 5, 5 };
    int wip[1];

    pipeline::init(2);
    pipeline::setupTool(4, stages, processingTime);
    pipeline::AddLot(2);

    ASSERT_EQ(0, pipeline::Simulate(5, wip));
    ASSERT_EQ(1, wip[0]);
    ASSERT_EQ(1, wip[1]);

    ASSERT_EQ(1, pipeline::Simulate(10, wip));
    ASSERT_EQ(0, wip[0]);
    ASSERT_EQ(1, wip[1]);

    ASSERT_EQ(2, pipeline::Simulate(15, wip));
    ASSERT_EQ(0, wip[0]);
    ASSERT_EQ(0, wip[1]);
}

TEST(Pipeline, twoStagesTwoToolsThreeItems)
{

    int stages[4] = { 0, 0, 1, 1 };
    int processingTime[] = { 5, 10, 5, 5 };
    int wip[1];

    pipeline::init(2);
    pipeline::setupTool(4, stages, processingTime);
    pipeline::AddLot(3);

    ASSERT_EQ(0, pipeline::Simulate(5, wip));
    ASSERT_EQ(2, wip[0]);
    ASSERT_EQ(1, wip[1]);

    ASSERT_EQ(1, pipeline::Simulate(10, wip));
    ASSERT_EQ(0, wip[0]);
    ASSERT_EQ(2, wip[1]);

    ASSERT_EQ(3, pipeline::Simulate(15, wip));
    ASSERT_EQ(0, wip[0]);
    ASSERT_EQ(0, wip[1]);

}


TEST(Pipeline, threeStagesFiveTools)
{
    int stages[5] = { 0, 0,  1,   2, 2};
    int processingTime[5] = { 5, 10, 5, 5, 20 };
    int wip[2];

    pipeline::init(3);
    pipeline::setupTool(5, stages, processingTime);
    pipeline::AddLot(3);

    ASSERT_EQ(0, pipeline::Simulate(0, wip));
    ASSERT_EQ(2, wip[0]);
    ASSERT_EQ(0, wip[1]);
    ASSERT_EQ(0, wip[2]);

    ASSERT_EQ(0, pipeline::Simulate(5, wip));
    ASSERT_EQ(2, wip[0]);
    ASSERT_EQ(1, wip[1]);
    ASSERT_EQ(0, wip[2]);

    ASSERT_EQ(0, pipeline::Simulate(10, wip));
    ASSERT_EQ(0, wip[0]);
    ASSERT_EQ(1, wip[1]);
    ASSERT_EQ(1, wip[2]);

    ASSERT_EQ(0, pipeline::Simulate(10, wip));
    ASSERT_EQ(0, wip[0]);
    ASSERT_EQ(1, wip[1]);
    ASSERT_EQ(1, wip[2]);

    pipeline::AddLot(3);
    ASSERT_EQ(0, pipeline::Simulate(10, wip));
    ASSERT_EQ(2, wip[0]);
    ASSERT_EQ(1, wip[1]);
    ASSERT_EQ(1, wip[2]);

    ASSERT_EQ(1, pipeline::Simulate(15, wip));
    ASSERT_EQ(2, wip[0]);
    ASSERT_EQ(1, wip[1]);
    ASSERT_EQ(1, wip[2]);

    ASSERT_EQ(2, pipeline::Simulate(20, wip));
    ASSERT_EQ(0, wip[0]);
    ASSERT_EQ(1, wip[1]);
    ASSERT_EQ(1, wip[2]);

    ASSERT_EQ(3, pipeline::Simulate(25, wip));
    ASSERT_EQ(0, wip[0]);
    ASSERT_EQ(1, wip[1]);
    ASSERT_EQ(1, wip[2]);

    ASSERT_EQ(6, pipeline::Simulate(50, wip));
    ASSERT_EQ(0, wip[0]);
    ASSERT_EQ(0, wip[1]);
    ASSERT_EQ(0, wip[2]);

}

TEST(Primitives, RotateArrayFourByFour)
{
	int object[4][4] = {
							 { 1,  2,   3,  4   },
							 { 5,  6,   7,  8   },
							 { 9,  10,  11, 12  },
							 { 13, 14,  15, 16 },
					   };

	// Rotate 90 degrees
	{
		int object[4][4] = {     { 1,  2,   3,  4   },
								 { 5,  6,   7,  8   },
								 { 9,  10,  11, 12  },
								 { 13, 14,  15, 16 },
						   };
		rotate_cw(4, object, 1);

		EXPECT_EQ(13, object[0][0]);
		EXPECT_EQ(14, object[1][0]);
		EXPECT_EQ(15, object[2][0]);
		EXPECT_EQ(16, object[3][0]);

		EXPECT_EQ(9,  object[0][1]);
		EXPECT_EQ(10, object[1][1]);
		EXPECT_EQ(11, object[2][1]);
		EXPECT_EQ(12, object[3][1]);

		EXPECT_EQ(5,  object[0][2]);
		EXPECT_EQ(6, object[1][2]);
		EXPECT_EQ(7, object[2][2]);
		EXPECT_EQ(8, object[3][2]);

		EXPECT_EQ(5,  object[0][2]);
		EXPECT_EQ(6, object[1][2]);
		EXPECT_EQ(7, object[2][2]);
		EXPECT_EQ(8, object[3][2]);
	}


	//Rotate 180 degrees
	{
		std::cout << "4x4 180: " << std::endl;
		rotate_cw(4, object, 2);

		EXPECT_EQ(16, object[0][0]);
		EXPECT_EQ(15, object[0][1]);
		EXPECT_EQ(14, object[0][2]);
		EXPECT_EQ(13, object[0][3]);

		EXPECT_EQ(12, object[1][0]);
		EXPECT_EQ(11, object[1][1]);
		EXPECT_EQ(10, object[1][2]);
		EXPECT_EQ(9,  object[1][3]);

		EXPECT_EQ(8, object[2][0]);
		EXPECT_EQ(7, object[2][1]);
		EXPECT_EQ(6, object[2][2]);
		EXPECT_EQ(5,  object[2][3]);

		EXPECT_EQ(4, object[3][0]);
		EXPECT_EQ(3, object[3][1]);
		EXPECT_EQ(2, object[3][2]);
		EXPECT_EQ(1,  object[3][3]);
	}
}

TEST(Primitives, RotateArrayTwoTwo)
{
	// Rotate 90 degrees
	{
		int object[4][4] = {	 { 1,  2,   3,  4   },
								 { 5,  6,   7,  8   },
								 { 9,  10,  11, 12  },
								 { 13, 14,  15, 16 },
						   };


		rotate_cw(2, object, 1);

		EXPECT_EQ(5, object[0][0]);
		EXPECT_EQ(6, object[1][0]);

		EXPECT_EQ(1, object[0][1]);
		EXPECT_EQ(2, object[1][1]);
	}

	//Rotate 180 degrees
	{
		int object[4][4] = {	 { 1,  2,   3,  4   },
								 { 5,  6,   7,  8   },
								 { 9,  10,  11, 12  },
								 { 13, 14,  15, 16 },
							   };

		rotate_cw(2, object, 2);

		EXPECT_EQ(6, object[0][0]);
		EXPECT_EQ(5, object[0][1]);

		EXPECT_EQ(2, object[1][0]);
		EXPECT_EQ(1, object[1][1]);

	}

	//Rotate 270 degrees
	{
		int object[4][4] = {	 { 1,  2,   3,  4 },
								 { 4,  5,   6,  4 },
								 { 7,  8,   9,  4 },
								 { 4,  4,   4,  4 },
							};

		std::cout << "3x3: 270" << std::endl;
		rotate_cw(3, object, 3);

		EXPECT_EQ(3, object[0][0]);
		EXPECT_EQ(6, object[0][1]);
		EXPECT_EQ(9, object[0][2]);

		EXPECT_EQ(2, object[1][0]);
		EXPECT_EQ(5, object[1][1]);
		EXPECT_EQ(8, object[1][2]);

		EXPECT_EQ(1, object[2][0]);
		EXPECT_EQ(4, object[2][1]);
		EXPECT_EQ(7, object[2][2]);
	}
}

TEST(Primitives, ArrayFlipUp)
{
	int object[4][4] = { { 1, 1, 0 },
						 { 0, 1, 1 },
						 { 0, 0, 0 }
	};

	flip(3, object, 0);

	EXPECT_EQ(0, object[0][0]);
	EXPECT_EQ(0, object[0][1]);
	EXPECT_EQ(0, object[0][2]);

	EXPECT_EQ(0, object[1][0]);
	EXPECT_EQ(1, object[1][1]);
	EXPECT_EQ(1, object[1][2]);

	EXPECT_EQ(1, object[2][0]);
	EXPECT_EQ(1, object[2][1]);
	EXPECT_EQ(0, object[2][2]);
}

TEST(Primitives, ArrayFlipLeft)
{
	int object[4][4] = { { 1, 1, 0 },
						 { 0, 1, 1 },
						 { 0, 0, 0 }
	};

	flip(3, object, 1);

	EXPECT_EQ(0, object[0][0]);
	EXPECT_EQ(1, object[0][1]);
	EXPECT_EQ(1, object[0][2]);

	EXPECT_EQ(1, object[1][0]);
	EXPECT_EQ(1, object[1][1]);
	EXPECT_EQ(0, object[1][2]);

	EXPECT_EQ(0, object[2][0]);
	EXPECT_EQ(0, object[2][1]);
	EXPECT_EQ(0, object[2][2]);
}


//This test takes almost one second to complete
TEST(Pipeline, fiveStagesNineToolsOneHundredThousandsItems)
{
    int stages[9] = { 0, 0,  1,  2, 2,   3, 3,    4, 4};
    int processingTime[9] = { 5, 10,  5,  10, 20  , 10, 10 ,   20, 20};
    int wip[4];

    pipeline::init(5);
    pipeline::setupTool(9, stages, processingTime);
    pipeline::AddLot(1000000);

    ASSERT_EQ(1000000, pipeline::Simulate(30*1000000, wip));
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}

