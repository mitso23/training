#include <algorithm>

class ResourceManagementGood
{

public:
	//Constructor
	explicit ResourceManagementGood(size_t size)
		: m_size(size)
		, m_ptr(new int[m_size])
	{

	}

	//Copy constructor
	ResourceManagementGood(const ResourceManagementGood& rhs)
		: m_size(rhs.m_size)
	{
		m_ptr = new int[m_size];
		std::copy(m_ptr, rhs.m_ptr, rhs.m_ptr + m_size);
	}

	// assignment operator
	ResourceManagementGood& operator = (const ResourceManagementGood& rhs)
	{
		// self assignment return this
		if(this == &rhs)
		{
			return *this;
		}

		try
		{
			m_ptr = new int[m_size];
			std::copy(rhs.m_ptr, rhs.m_ptr + m_size, m_ptr);
		}
		catch(std::exception& e)
		{
			return *this;
		}
	}

	// Destructor
	~ResourceManagementGood()
	{
		delete[] m_ptr;
		m_size = 0;
	}

private:
	size_t m_size = 0;
	int* m_ptr = nullptr;
};
