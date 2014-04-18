#ifndef ROBOSOCCER_COMMON_ROUTING_ROUTINGRESULTTEST_H
#define ROBOSOCCER_COMMON_ROUTING_ROUTINGRESULTTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboSoccer
{
namespace Common
{
namespace Routing
{
class RoutingResultTest :
		public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(RoutingResultTest);
	CPPUNIT_TEST(constructor_empty_isNotValid);
	CPPUNIT_TEST(constructor_validParam_isValid);
	CPPUNIT_TEST_SUITE_END();

private:
	void constructor_empty_isNotValid();
	void constructor_validParam_isValid();
};
}
}
}

#endif


