#ifndef ROBOSOCCER_LAYER_MAIN_TARGETPOSITIONFETCHERTEST_H
#define ROBOSOCCER_LAYER_MAIN_TARGETPOSITIONFETCHERTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboSoccer
{
namespace Layer
{
namespace Main
{
class TargetPositionFetcherTest :
		public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(TargetPositionFetcherTest);
	CPPUNIT_TEST(getGoalPosition_fieldSideRight_correctPosition);
	CPPUNIT_TEST_SUITE_END();

private:
	void getGoalPosition_fieldSideRight_correctPosition();

};
}
}
}

#endif


