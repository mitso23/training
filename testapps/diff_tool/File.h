#ifndef FILE_H
#define FILE_H

#include <string>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

typedef std::pair<std::string, size_t> line_t;
typedef std::iterator<std::random_access_iterator_tag, line_t> iterator;

bool operator < (const line_t& lhs, const line_t& rhs)
{
	bool less= lhs.first < rhs.first;

	return less;
}

std::ostream& operator << (std::ostream& lhs, const line_t& rhs)
{
	return lhs << std::string("data: ") << rhs.first << std::string(" line: ")
			<< (unsigned) rhs.second;
}

class File;

class FileIter: public iterator
{
public:
	FileIter(File* file, size_t pos);

	FileIter operator ++();

	FileIter operator --();

	line_t& operator*();

	const line_t& operator*() const;

	bool operator !=(const FileIter& rhs);

	FileIter operator + (const FileIter&);

	size_t operator - (const FileIter&);

	friend FileIter operator + (const FileIter&, size_t);

	friend FileIter operator - (const FileIter&, size_t);

	friend FileIter operator + (size_t, const FileIter&);

	friend FileIter operator - (size_t, const FileIter&);

	FileIter& operator+=(int);

	FileIter& operator-=(int);

	bool operator == (const FileIter& rhs);

	bool operator < (const FileIter& rhs);

	bool operator > (const FileIter& rhs);

private:
	File* m_file;
	size_t m_pos;
};

//If we have 26 elements start: 0 end: 26 last element at 25
class File
{
public:
	File() :
		m_start(0), m_end(0)
	{

	}

	FileIter begin()
	{
		return FileIter(this, m_start);
	}

	const FileIter begin() const
	{
		return FileIter(const_cast<File*> (this), m_start);
	}

	FileIter end()
	{
		return FileIter(this, m_end);
	}

	const FileIter end() const
	{
		return FileIter(const_cast<File*> (this), m_end);
	}

	friend class FileIter;

	void setLine(std::string&& str, size_t lineNumber)
	{
		m_data.push_back(std::make_pair(str, lineNumber));
		++m_end;
	}

	void setLine(const std::string& str, size_t lineNumber)
	{
		m_data.push_back(std::make_pair(str, lineNumber));
		++m_end;
	}

	struct compare
	{
		bool operator() (const line_t& line1, const line_t& line2)
		{
			return line1 < line2;
		}
	};

private:
	std::vector<line_t> m_data;
	size_t m_start;
	size_t m_end;
};

FileIter FileIter::operator ++()
{
	if (m_pos <  m_file->m_end)
	{
		return FileIter(m_file, ++m_pos);
	}
	else
	{
		return m_file->end();
	}
}

FileIter FileIter::operator --()
{

	if (m_pos != m_file->m_end)
	{
		return FileIter(m_file, --m_pos);
	}
	else
	{
		return m_file->end();
	}
}

line_t& FileIter::operator*()
{
	return const_cast<line_t&>(static_cast<const FileIter&>(*this).operator*());
}

const line_t& FileIter::operator*() const
{
	if (m_pos == m_file->m_end)
	{
		if (m_file->m_data.size() == m_file->m_end)
		{
			m_file->m_data.push_back(line_t("", 0));
		} else if (m_file->m_data.size() < m_file->m_end)
		{
			std::cerr << "impossible" << std::endl;
		}
	}

	return m_file->m_data[m_pos];
}

bool FileIter::operator !=(const FileIter& rhs)
{
	return m_pos != rhs.m_pos;
}

FileIter operator + (const FileIter& lhs, size_t n)
{
	return FileIter(lhs.m_file, lhs.m_pos + n);
}

FileIter operator - (const FileIter& lhs, size_t n)
{
	return FileIter(lhs.m_file, lhs.m_pos - n);
}

FileIter operator + (size_t n, const FileIter& rhs)
{
	return FileIter(rhs.m_file, rhs.m_pos + n);
}

FileIter operator -(size_t n, const FileIter& rhs)
{
	return FileIter(rhs.m_file, rhs.m_pos - n);
}

FileIter& FileIter::operator+=(int n)
{
	m_pos += n;
	return *this;
}

FileIter& FileIter::operator-=(int n)
{
	m_pos -= n;
	return *this;
}

size_t FileIter::operator - (const FileIter& rhs)
{
	return m_pos - rhs.m_pos;
}

bool FileIter::operator == (const FileIter& rhs)
{
	return rhs.m_pos == m_pos;
}

bool FileIter::operator < (const FileIter& rhs)
{
	return m_pos < rhs.m_pos;
}

bool FileIter::operator > (const FileIter& rhs)
{
	return m_pos > rhs.m_pos;
}

FileIter::FileIter(File* file, size_t pos) :
	m_file(file), m_pos(pos)
{
	if (m_pos > m_file->m_end)
	{
		std::cerr << "Out of bound access error " << std::endl;
		m_pos = m_file->m_end;
	}
}

#endif /* FILE_H_ */
