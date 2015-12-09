#ifndef FILEDIFF_H
#define FILEDIFF_H

#include "File.h"
#include "DiskReader.h"

#include <utils/utils.h>
#include <list>

/**
 * Algorithm. We start from Document one and fine the first common line between the file 1 and file 2
 * if line1_end - line1_start > 1 && line2_end - line2_start > 0 then mark the lines as DIFFERENT
 * if line1_end - line1_start > 1 && line2_end - line2_start = 0 then mark it as ADDED
 * if line1_end - line1_start = 1 && line2_end - line2_start > 0 then mark it as REMOVED
 * if line1_end - line1_start = 1 && line2_end - line2_start = 0 then mark it as COMMON
 */

class FileDiff
{
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

	void addStateA(size_t startA, size_t endA, line_state_t state)
	{
		for(size_t i=startA; i <= endA; ++i)
		{
			m_file1_state[i]= state;
		}

	}

	void addStateB(size_t startB, size_t endB, line_state_t state)
	{
		for(size_t i=startB; i <= endB; ++i)
		{
			m_file2_state[i]= state;
		}
	}

	void findCommonLines()
	{
		line_t previousCommonLineA = line_t("", -1);
		line_t previousCommonLineB = line_t("", -1);
		line_t currentCommonLineA;
		line_t currentCommonLineB;

		for(auto it=m_file1.begin(); it!= m_file1.end(); ++it)
		{
			for(auto it2= m_file2.begin(); it2 != m_file2.end(); ++it2)
			{
				if(*it == *it2)
				{
					currentCommonLineA = *it;
					currentCommonLineB= *it2;

					addStateA(currentCommonLineA, currentCommonLineA, COMMON);
					addStateB(currentCommonLineB, currentCommonLineB, COMMON);

				}

				if((currentCommonLineA - previousCommonLineA) > 1 && (currentCommonLineB - previousCommonLineB) > 1)
				{
					addStateA(previousCommonLineA + 1, currentCommonLineA - 1, DIFF);
					addStateB(previousCommonLineB + 1, currentCommonLineB - 1, DIFF);
				}
				else if((currentCommonLineA - previousCommonLineA > 1) && (currentCommonLineB - previousCommonLineB) == 1)
				{
					addStateA(previousCommonLineA + 1, currentCommonLineA - 1, REMOVED);
				}
				else if ((currentCommonLineA - previousCommonLineA == 1) && (currentCommonLineB - previousCommonLineB) > 1)
				{
					addStateA(previousCommonLineB + 1, currentCommonLineB - 1, ADDED);
				}

			}
		}
	}

private:

	std::string m_path1;
	std::string m_path2;
	File m_file1;
	File m_file2;
	std::map<line_t, line_state_t> m_file1_state;
	std::map<line_t, line_state_t> m_file2_state;
};

#endif /* FILEDIFF_H_ */
