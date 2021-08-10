#pragma once

#include <string>
#include <memory>
#include <vector>

class FileReader
{

 public:
	FileReader(std::string filename);

	std::vector<uint8_t> Read(size_t size) const;

 private:
	std::string m_fileName;
	int m_fd = -1;
};