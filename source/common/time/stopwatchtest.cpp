#include "common/time/stopwatchtest.h"
#include "common/time/stopwatch.h"
#include "common/time/watchmock.h"
#include <unistd.h>

using namespace RoboSoccer::Common::Time;

void StopWatchTest::constructor_3SecondsAlreadyPassedBy_getTimeReturns0()
{
	WatchMock watch;
	watch.setTime(1);

	StopWatch stopWatch(watch);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, stopWatch.getTime(), 0.00001);
}

void StopWatchTest::getTimeAndRestart_someTimePassedAlreadyBefore_getTimeReturns0()
{
	WatchMock watch;
	StopWatch stopWatch(watch);
	stopWatch.getTimeAndRestart();
	watch.setTime(1);

	stopWatch.getTimeAndRestart();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, stopWatch.getTime(), 0.00001);
}

void StopWatchTest::getTimeAndRestart_2SecondsPassedBy_2()
{
	WatchMock watch;
	StopWatch stopWatch(watch);
	watch.setTime(2);

	double time = stopWatch.getTimeAndRestart();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(2, time, 0.00001);
}

void StopWatchTest::getTimeAndRestart_initialTime1SecondAnd2SecondsPassedBy_2()
{
	WatchMock watch;
	watch.setTime(1);
	StopWatch stopWatch(watch);
	watch.setTime(3);

	double time = stopWatch.getTimeAndRestart();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(2, time, 0.00001);
}

void StopWatchTest::getTime_initialTime1SecondAnd2SecondsPassedBy_2()
{
	WatchMock watch;
	watch.setTime(1);
	StopWatch stopWatch(watch);
	watch.setTime(3);

	double time = stopWatch.getTime();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(2, time, 0.00001);
}

void StopWatchTest::restart_3SecondsAlreadyPassedBy_getTimeReturns0()
{
	WatchMock watch;
	watch.setTime(1);
	StopWatch stopWatch(watch);
	watch.setTime(4);

	stopWatch.restart();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, stopWatch.getTime(), 0.00001);
}

void StopWatchTest::restart_4SecondsAlreadyPassedByAndStartTimeSetTo1And2SecondsPassedByAfter_getTimeReturns3()
{
	WatchMock watch;
	StopWatch stopWatch(watch);
	watch.setTime(4);

	stopWatch.restart(1);
	watch.setTime(6);

	CPPUNIT_ASSERT_DOUBLES_EQUAL(3, stopWatch.getTime(), 0.00001);
}
