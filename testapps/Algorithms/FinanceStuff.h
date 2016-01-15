#ifndef FINANCESTUFF_H
#define FINANCESTUFF_H

#include <stdio.h>
#include <algorithm>
#include <utils/RCObjects.h>


class Storage;

class DataProxy
{
public:
	DataProxy(const Storage* storage, uint32_t possition) : m_storage(storage), m_currentPos(possition)
	{

	}

	DataProxy getNext();

	DataProxy getPrevious();

	uint8_t& operator*() const;

	bool operator != (const DataProxy& rhs) const ;

	bool operator == (const DataProxy& rhs) const;

private:
	const Storage* m_storage;
	uint32_t m_currentPos;
};

class Storage
{
friend class DataProxy;
public:
	Storage(uint32_t size) : m_size(size), m_ptr(new uint8_t(m_size))
	{
		for(unsigned int i=0; i< size; ++i)
		{
			m_ptr[i]= 0;
		}
	}

	DataProxy getFirst() const;

	DataProxy getLast() const;

	void resize();

	uint32_t getSize() const;

private:
	uint8_t& operator[](unsigned index) const;

private:
	size_t m_size;
	uint8_t* m_ptr;
};

DataProxy Storage::getFirst() const
{
	return DataProxy(this, 0);
}

DataProxy Storage::getLast() const
{
	return DataProxy(this, m_size);
}

uint8_t& Storage::operator[](unsigned index) const
{
	return m_ptr[index];
}

void Storage::resize()
{
	uint8_t* mem= new uint8_t(sizeof(m_size + 1) * sizeof(uint8_t));
	mem[0]= 0;
	std::copy(m_ptr, m_ptr + m_size, mem + 1);

	delete m_ptr;
}

uint32_t Storage::getSize() const
{
	return m_size;
}

DataProxy DataProxy::getNext()
{
	++m_currentPos;
	return *this;
}

DataProxy DataProxy::getPrevious()
{
	--m_currentPos;
	return *this;
}

uint8_t& DataProxy::operator*() const
{
	return (*m_storage)[m_currentPos];
}

bool DataProxy::operator !=(const DataProxy& rhs) const
{
	return rhs.m_currentPos != m_currentPos;
}

bool DataProxy::operator ==(const DataProxy& rhs) const
{
	return rhs.m_currentPos == m_currentPos;
}

class BigInt
{

public:
	BigInt(size_t size) : m_storage(size)
	{

	}

	BigInt(const std::string& str) : BigInt(str.size())
	{
		strToArrInt(str);
		std::cout << *this << std::endl;
	}

	void strToArrInt(const std::string& str)
	{
		DataProxy dt= m_storage.getFirst();

		for(auto it=str.begin(); it != str.end(); ++it)
		{
			*dt= *it - '0';
			dt= dt.getNext();
		}
	}

	unsigned getNextDigit(DataProxy& data)
	{
		if (data == m_storage.getFirst())
		{
			return 0;
		}
		else
		{
			return *(data.getPrevious());
		}
	}

	BigInt operator + (BigInt& rhs)
	{
		auto maxSize= m_storage.getSize() > rhs.m_storage.getSize() ? m_storage.getSize() : rhs.m_storage.getSize();
		BigInt temp(maxSize);

		DataProxy nextIt1= m_storage.getLast();
		DataProxy nextIt2= rhs.m_storage.getLast();

		unsigned int curryFlag= 0;
		auto result= temp.m_storage.getLast().getPrevious();
		uint32_t tempResult= 0;

		for(unsigned int i=0; i< maxSize; ++i)
		{
			auto nextDigitFirst= getNextDigit(nextIt1);
			auto nextDigitSecond= getNextDigit(nextIt2);

			tempResult =  nextDigitFirst + nextDigitSecond + curryFlag;

			std::cout << "digit 1: " << nextDigitFirst << " digit 2: " << nextDigitSecond << " result: " << tempResult << std::endl;

			if (tempResult >= 10)
			{
				curryFlag= 1;
				tempResult-= 10;
			}
			else
			{
				curryFlag= 0;
			}

			*result= tempResult;
			std::cout << temp << std::endl;
			result= result.getPrevious();
		}

		if (curryFlag == 1)
		{
			temp.m_storage.resize();
			*temp.m_storage.getFirst()= 1;
		}

		return temp;
	}

	friend std::ostream& operator << (std::ostream& os, const BigInt& rhs)
	{
		for(auto dt= rhs.m_storage.getFirst(); dt != rhs.m_storage.getLast(); dt=dt.getNext())
		{
			os << (unsigned)*dt;
		}

		return os;
	}

private:
	Storage m_storage;
};


#endif /* FINANCESTUFF_H_ */
