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
		CPPUNIT_TEST(constructor_3SecondsAlreadyPassedBy_getTimeReturns0);
		CPPUNIT_TEST(getTimeAndRestart_someTimePassedAlreadyBefore_getTimeReturns0);
		CPPUNIT_TEST(getTimeAndRestart_2SecondsPassedBy_2);
		CPPUNIT_TEST(getTimeAndRestart_initialTime1SecondAnd2SecondsPassedBy_2);
		CPPUNIT_TEST(getTime_initialTime1SecondAnd2SecondsPassedBy_2);
		CPPUNIT_TEST(restart_3SecondsAlreadyPassedBy_getTimeReturns0);
		CPPUNIT_TEST(restart_4SecondsAlreadyPassedByAndStartTimeSetTo1And2SecondsPassedByAfter_getTimeReturns3);
		CPPUNIT_TEST_SUITE_END();

	private:
		void constructor_3SecondsAlreadyPassedBy_getTimeReturns0();
		void getTimeAndRestart_someTimePassedAlreadyBefore_getTimeReturns0();
		void getTimeAndRestart_2SecondsPassedBy_2();
		void getTimeAndRestart_initialTime1SecondAnd2SecondsPassedBy_2();
		void getTime_initialTime1SecondAnd2SecondsPassedBy_2();
		void restart_3SecondsAlreadyPassedBy_getTimeReturns0();
		void restart_4SecondsAlreadyPassedByAndStartTimeSetTo1And2SecondsPassedByAfter_getTimeReturns3();
	};
}
}
}

#endif


