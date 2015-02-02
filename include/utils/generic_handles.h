#ifndef GENERIC_HANDLES_H_
#define GENERIC_HANDLES_H_

template<typename tag, typename type, type defaultValue>
class handle
{
public:

	handle() : m_data(defaultValue)
	{

	}

	explicit handle(type data) : m_data(data)
	{

	}

	friend bool operator == (struct handle lhs, struct handle rhs)
	{
		return lhs.m_data == rhs.m_data;
	}

	friend bool operator != (struct handle lhs, struct handle rhs)
	{
		return lhs.m_data != rhs.m_data;
	}

	type getHandle()
	{
		return m_data;
	}

private:
	type m_data;
};


#endif /* GENERIC_HANDLES_H_ */
