#define BOOST_TEST_MODULE stringtest
#define BOOST_TEST_DYN_LINK 1

#include <boost/test/unit_test.hpp>
#include <utils/RCObjects.h>
#include <utils/Noisy.h>

static int constructorCounter= 0;
static int destructorCounter=0;

BOOST_AUTO_TEST_SUITE (UtilsTestSuite)
class Value;

class TestRCObjects
{
public:

	TestRCObjects() : m_value(new Value(0))
	{

	}

	void setValue(int value)
	{
		m_value->removeReference();
		m_value= new Value(value);
	}

	void disableSharing()
	{
		m_value->markUnshareable();
	}

	int getValue() const
	{
		return *m_value;
	}

private:
	class Value : public RCObject
	{
	public:
		operator int()
		{
			return m_value;
		}

		Value () : m_value(0)
		{
			++constructorCounter;
		}

		Value (int value ) : m_value(value)
		{
			std::cout << "constructor called" << std::endl;
			++constructorCounter;
		}

		Value(const Value& rhs) : m_value(rhs.m_value)
		{
			std::cout << "copy constructor called" << std::endl;
			++constructorCounter;
		}

		~Value()
		{
			std::cout << "destructor called" << std::endl;
			++destructorCounter;
		}
	public:
		int m_value;
	};

	RCPtr<Value> m_value;
};

BOOST_AUTO_TEST_CASE(SimpleCreation)
{
	{
		TestRCObjects obj;
		BOOST_CHECK(obj.getValue() == 0);
	}

	BOOST_CHECK(constructorCounter == 1);
	BOOST_CHECK(destructorCounter  == 1);

	constructorCounter= 0;
	destructorCounter= 0;

}

BOOST_AUTO_TEST_CASE(MultipleCreations)
{
	{
		TestRCObjects obj;
		TestRCObjects obj2= obj;
		TestRCObjects obj3= obj2;
	}

	BOOST_CHECK(constructorCounter == 1);
	BOOST_CHECK(destructorCounter  == 1);

	constructorCounter= 0;
	destructorCounter= 0;
}


BOOST_AUTO_TEST_CASE(DisableSharing)
{
	{
		TestRCObjects obj;
		obj.disableSharing();
		TestRCObjects obj2 = obj;
		obj2.disableSharing();
		TestRCObjects obj3 = obj2;
	}

	BOOST_CHECK(constructorCounter == 3);
	BOOST_CHECK(destructorCounter == 3);

	constructorCounter= 0;
	destructorCounter= 0;
}

BOOST_AUTO_TEST_CASE(MixSharingNonSharing)
{
	{
		TestRCObjects obj;
		obj.disableSharing();
		TestRCObjects obj2 = obj;
		TestRCObjects obj3 = obj2;
	}

	BOOST_CHECK(constructorCounter == 2);
	BOOST_CHECK(destructorCounter == 2);

	constructorCounter= 0;
	destructorCounter= 0;
}

BOOST_AUTO_TEST_CASE(CopyOnWrite)
{
	{
		TestRCObjects obj;
		TestRCObjects obj2 = obj;
		obj2.setValue(10);
	}

	BOOST_CHECK(constructorCounter == 2);
	BOOST_CHECK(destructorCounter == 2);

	constructorCounter= 0;
	destructorCounter= 0;
}

BOOST_AUTO_TEST_SUITE_END( )
