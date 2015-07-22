#ifndef ENUMS_H_
#define ENUMS_H_

class Base
{
	enum colour
	{
		RED,
		WHITE
	};
};

class Opcode
{
public:
	explicit Opcode(int value) : m_opcode(value)
	{

	}

	bool operator ==(const Opcode& rhs) const
	{
		return rhs.m_opcode == m_opcode;
	}

	bool operator < (const Opcode& rhs) const
	{
		return m_opcode < rhs.m_opcode;
	}

	int getOpcode();
private:
	int m_opcode;
};

class GetDevId : public Opcode
{
public:
	GetDevId() : Opcode(100)
	{

	}
};

enum class colour : int
{
	RED=0,
	YELLOW= 1
};

enum class mixedColours : int
{
	PINK
};

#endif /* ENUMS_H_ */
