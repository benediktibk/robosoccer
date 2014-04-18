#include "common/time/stopwatchtest.h"
#include "common/time/stopwatch.h"
#include "common/time/watchimpl.h"
#include <unistd.h>

using namespace RoboSoccer::Common::Time;

void StopWatchTest::getTimeAndRestart_twiceDirectBehindCalled_0()
{
	WatchImpl watch;
	StopWatch stopWatch(watch);

	stopWatch.getTimeAndRestart();
	double time = stopWatch.getTimeAndRestart();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, time, 0.01);
}

void StopWatchTest::getTimeAndRestart_sleepOf200ms_02()
{
	WatchImpl watch;
	StopWatch stopWatch(watch);

	usleep(50000);
	stopWatch.getTimeAndRestart();
	usleep(200000);
	double time = stopWatch.getTimeAndRestart();

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0.2, time, 0.01);
}



