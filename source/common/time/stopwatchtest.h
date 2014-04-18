#ifndef ROBOSOCCER_COMMON_TIME_STOPWATCHTEST_H
#define ROBOSOCCER_COMMON_TIME_STOPWATCHTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboSoccer
{
namespace Common
{
namespace Time
{
class StopWatchTest :
		public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE(StopWatchTest);
	CPPUNIT_TEST(getTimeAndRestart_twiceDirectBehindCalled_0);
	CPPUNIT_TEST(getTimeAndRestart_sleepOf200ms_02);
	CPPUNIT_TEST_SUITE_END();

private:
	void getTimeAndRestart_twiceDirectBehindCalled_0();
	void getTimeAndRestart_sleepOf200ms_02();
};
}
}
}

#endif


