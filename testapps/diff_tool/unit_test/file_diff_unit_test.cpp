#define BOOST_TEST_MODULE stringtest
#define BOOST_TEST_DYN_LINK 1

#include <boost/test/unit_test.hpp>
#include "../DiskReader.h"
#include "../File.h"
#include <vector>
#include <string>
#include <iterator>
#include <fstream>
#include <utils/utils.h>

BOOST_AUTO_TEST_SUITE (UtilsTestSuite)

BOOST_AUTO_TEST_CASE(FileIterTest)
{
	File file;
	std::vector<std::string> vec {	"One", "Two", "Three"};

	//Fill the file with some useful information
	{
		int i=0;
		for(auto it=vec.begin(); it!= vec.end(); ++it)
		{
			file.setLine(*it, i++);
		}
	}

	//check that ++ works
	{
		auto comp= vec.begin();
		for(auto it=file.begin(); it!= file.end(); ++it)
		{
			BOOST_CHECK( (*it).first == *comp++);
		}
	}

	//check that -- works
	{
		auto comp= vec.end() - 1;
		auto it=file.end() - 1;
		BOOST_CHECK( (*it).first == *comp);
		--it;
		--comp;
		BOOST_CHECK( (*it).first == *comp);
	}

	//Check that substracting iterators works
	BOOST_CHECK(file.end() - file.begin() == 3);

	{
		//Check + works
		BOOST_CHECK(*file.begin() == line_t("One", 0));
		BOOST_CHECK(*(file.begin() + 1) == line_t("Two", 1));
		BOOST_CHECK(*(file.begin() + 2) == line_t("Three", 2));
	}

	{
		//Check += works
		auto it= file.begin();
		BOOST_CHECK(*(it) == line_t("One", 0));
		BOOST_CHECK(*(it+=1) == line_t("Two", 1));
		BOOST_CHECK(*(it+=1) == line_t("Three", 2));
	}

	{
		//Check -= works
		auto it= file.end() - 1;
		BOOST_CHECK(*it == line_t("Three", 2));
		BOOST_CHECK(*(it-=1) == line_t("Two", 1));
		BOOST_CHECK(*(it-=1) == line_t("One", 0));
	}

	//Check that the comparison operators work
	{
		auto it= file.begin();
		auto it2= it + 1;
		auto it3= it;

		BOOST_CHECK(it < it2);
		BOOST_CHECK(it2 > it);

		BOOST_CHECK(it == it3);
		BOOST_CHECK(it2 != it);
	}

	//Check that the * operator works in read write mode
	{
		auto it= file.begin();
		*it= line_t("Four", 0);
		BOOST_CHECK(*it == line_t("Four", 0));
	}

	//Check that the * operator works in read mode
	{
		const File& cfile= file;
		BOOST_CHECK(*file.begin() == line_t("Four", 0));
	}
}

BOOST_AUTO_TEST_CASE(FileAlgorithms)
{
	File file;
	std::vector<std::string> vec {	"C", "A", "B"};

	//Fill the file with some useful information
	{
		int i=0;
		for(auto it=vec.begin(); it!= vec.end(); ++it)
		{
			file.setLine(*it, i++);
		}
	}

	auto it= std::find(file.begin(), file.end(), line_t("C", 0));
	BOOST_CHECK(it != file.end());

	auto it2= std::find_if(file.begin(), file.end(), [](const line_t& line) { return line == line_t("C", 0); });
	BOOST_CHECK(it2 != file.end());

	std::sort(file.begin(), file.end());
	BOOST_CHECK(*file.begin()  == line_t("A", 1));
	BOOST_CHECK(*(file.begin() + 1) == line_t("B", 2));
	BOOST_CHECK(*(file.begin() + 2)== line_t("C", 0));

	*file.begin()= line_t("C", 0);
	*(file.begin() + 1) = line_t("A", 1);
	*(file.begin() + 2) = line_t("B", 2);
	file.sort();

	BOOST_CHECK(*file.begin() == line_t("A", 1));
	BOOST_CHECK(*(file.begin() + 1) == line_t("B", 2));
	BOOST_CHECK(*(file.begin() + 2)== line_t("C", 0));
}

struct comparator
{
	bool operator () (const line_t& lhs, const std::string rhs)
	{
		return lhs.first == rhs;
	}
};

BOOST_AUTO_TEST_CASE(FileReader)
{
	DiskReader ds("/home/mitso23/training/resources/text1_diff.c");
	std::ifstream stream("/home/mitso23/training/resources/text1_diff.c");

	File fs;
	ds.readDataDisk(fs);


	std::vector<std::string> names;
	names.reserve(fs.end() - fs.begin());
	auto it2= std::back_inserter(names);
	std::string temp;

	while(std::getline(stream, temp))
		*it2++= std::move(temp);

	BOOST_CHECK(std::equal(fs.begin(), fs.end(), names.begin(), comparator()) == true);

	std::sort(fs.begin(), fs.end());
	std::sort(names.begin(), names.end());
	BOOST_CHECK(std::equal(fs.begin(), fs.end(), names.begin(), comparator()) == true);
}


BOOST_AUTO_TEST_SUITE_END( )
