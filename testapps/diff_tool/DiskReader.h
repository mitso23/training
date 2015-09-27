#ifndef DISKREADER_H_
#define DISKREADER_H_

#include "File.h"

#include <string>
#include <fstream>

class DiskReader
{
public:
	DiskReader(const std::string& filename) : m_filename(filename)
	{

	}

	bool readDataDisk(File& file)
	{
		std::ifstream stream(m_filename);
		if (!stream)
			return false;

		std::string line;
		size_t lineNumber= 0;
		while(std::getline(stream, line))
		{
			file.setLine(std::move(line), ++lineNumber);
		}

		return true;
	}

private:
	const std::string& m_filename;
};

#endif /* DISKREADER_H_ */
