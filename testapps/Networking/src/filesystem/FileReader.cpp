#include "FileReader.h"
#include "Logging.h"

#include <fcntl.h>
#include <unistd.h>
#include <string.h>

FileReader::FileReader(std::string filename)
	: m_fileName(std::move(filename))
{
	LOGD("");

	m_fd = open(m_fileName.c_str(), O_RDONLY);

	if (m_fd < 0)
	{
		LOGD("Failed to open the file", m_fileName, "error",strerror(errno));
		throw 1;
	}
}


std::vector<uint8_t> FileReader::Read(size_t size) const
{
	LOGD("size: ", size);

	std::vector<uint8_t> result;
	result.resize(size);

	auto res = read(m_fd, result.data(), size);
	if (res < 0)
	{
		LOGE("Failed to read: ", strerror(errno));
		abort();
		return result;
	}

	if (size != static_cast<decltype(size)>(res))
	{
		LOGE("Read only", res);
		abort();
		return result;
	}

	LOGD("Successfully read: ", size);

	return std::move(result);
}