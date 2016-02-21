#include <utils/SmartPointer.h>

#define BOOST_TEST_MODULE smart_ptr_test
#define BOOST_TEST_DYN_LINK 1

#include <boost/test/unit_test.hpp>
#include <utils/SmartPointer.h>
#include <utils/Noisy.h>

#include <memory>

class NoisyDerived : public Noisy
{
public:
	NoisyDerived()
	{

	}
};

BOOST_AUTO_TEST_SUITE (UtilsTestSuite)

BOOST_AUTO_TEST_CASE(SimpleCreation)
{
	SmartPtr<Noisy> ns1(new Noisy);

	BOOST_CHECK(ns1->getId() == 0);
}

BOOST_AUTO_TEST_CASE(SimpleCopyConstruction)
{
	SmartPtr<Noisy> ns1(new Noisy);
	SmartPtr<Noisy> ns2 = ns1;
	SmartPtr<Noisy> ns3 = ns2;

	BOOST_CHECK(ns2->getId() == 1);
	BOOST_CHECK(ns3->getId() == 1);
}

BOOST_AUTO_TEST_CASE(SimpleAssignment)
{
	SmartPtr<Noisy> ns1(new Noisy());
	SmartPtr<Noisy> ns2;
	ns2 = ns1;

	BOOST_CHECK(ns2->getId() == 2);
}

BOOST_AUTO_TEST_CASE(BasicOperatos)
{
	SmartPtr<Noisy> ns1(new NoisyDerived());
	SmartPtr<Noisy> n2= ns1;

	ns1= n2;

	SmartPtr<Noisy> ns3= my_make_shared<Noisy>();

	BOOST_CHECK(!ns1);
}

BOOST_AUTO_TEST_SUITE_END()
