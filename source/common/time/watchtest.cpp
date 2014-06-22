#include "common/time/watchtest.h"
#include "common/time/watchimpl.h"
#include <unistd.h>

using namespace RoboSoccer::Common::Time;

void WatchTest::getTime_nearlyNoTimePassedBy_0()
{
	WatchImpl watch;

	CPPUNIT_ASSERT_DOUBLES_EQUAL(0, watch.getTime(), 0.0001);
}
