#ifndef FILEDIFF_H
#define FILEDIFF_H

#include "File.h"
#include "DiskReader.h"

#include <utils/utils.h>
#include <list>

class FileDiff
{
	//This needs to be removed as more state need to be added use state machine classes
	typedef enum
	{
		COMMON, DIFF, REMOVED, ADDED
	} line_state_t;

	typedef std::pair<size_t, size_t> common_line_t;

public:
	FileDiff(std::string&& path1, std::string&& path2) : m_path1(path1), m_path2(path2)
	{
		DiskReader reader1(m_path1);
		DiskReader reader2(m_path2);

		reader1.readDataDisk(m_file1);
		reader2.readDataDisk(m_file2);
	}

	void print(line_t startA, line_t EndA, line_t startB, line_t EndB, line_state_t state)
	{
		switch(state)
		{
			case COMMON:
			{
				std::cout << "A Common start: " << startA << " end: " << EndA << std::endl;
				std::cout << "B Common start: " << startB << " end: " << EndB << std::endl;
			}
			break;
			case DIFF:
			{
				std::cout << "A Diff start: " << startA << " end: " << EndA << std::endl;
				std::cout << "B Diff start: " << startB << " end: " << EndB << std::endl;
			}
			break;
			case REMOVED:
			{
				std::cout << "A Removed start: " << startA << " end: " << EndA << std::endl;
				std::cout << "B Removed start: " << startB << " end: " << EndB << std::endl;
			}
			break;
			case ADDED:
			{
				std::cout << "A Added start: " << startA << " end: " << EndA << std::endl;
				std::cout << "B Added start: " << startB << " end: " << EndB << std::endl;

			}
			break;
		}
	}

	void findCommonLines()
	{
		std::sort(m_file2.begin(), m_file2.end() - 1, File::compare());

		//print_cont(m_file1);
		//print_cont(m_file2);
#if 1
		line_t previousCommonLineA;
		line_t previousCommonLineB;
		line_t currentCommonLineA;
		line_t currentCommonLineB;

		for(auto it=m_file1.begin(); it!= m_file1.end(); ++it)
		{
			std::pair<FileIter, FileIter> pair= std::equal_range(m_file2.begin(), m_file2.end() - 1, *it, File::compare());
			if (pair.first != pair.second)
			{
				currentCommonLineA= *it;
				currentCommonLineB=*(pair.first);

				std::cout << *it << std::endl;
				std::cout << *(pair.first) << std::endl;

				if((currentCommonLineA.second - previousCommonLineA.second) > 1 && (currentCommonLineB.second - previousCommonLineB.second) > 1)
				{
					print(previousCommonLineA, currentCommonLineA, previousCommonLineB, currentCommonLineB, line_state_t::DIFF);
				}

				previousCommonLineA= currentCommonLineA;
				previousCommonLineB= currentCommonLineB;

				break;
			}
		}
#endif
	}

	void outputDiffToDisk()
	{
		findCommonLines();
	}

private:

	std::string m_path1;
	std::string m_path2;
	File m_file1;
	File m_file2;
	std::list<std::pair<size_t, size_t> > m_commonLines;
};

#endif /* FILEDIFF_H_ */
