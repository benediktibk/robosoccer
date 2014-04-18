#include "common/other/signumtest.h"
#include "common/other/signum.h"

using namespace RoboSoccer::Common::Other;

void SignumTest::signum_4_1()
{
	CPPUNIT_ASSERT_EQUAL((int)1, sgn<double>(4));
}

void SignumTest::signum_0_0()
{
	CPPUNIT_ASSERT_EQUAL((int)0, sgn<double>(0));
}

void SignumTest::signum_minus3_minus1()
{
	CPPUNIT_ASSERT_EQUAL((int)-1, sgn<double>(-3));
}
