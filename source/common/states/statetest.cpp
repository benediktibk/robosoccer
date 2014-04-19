#include "common/states/statetest.h"
#include "common/states/statemock.h"
#include "common/logging/loggermock.h"

using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::States;

void StateTest::update_updateAlwaysAndCalledThreeTimes_updateInternalWasCalledThreeTimes()
{
	LoggerMock logger;
	StateMock state(logger, false);

	state.update();
	state.update();
	state.update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)3, state.getCallsToUpdate());
}

void StateTest::update_updateOnlyOnceAndCalledFourTimes_updateInternalWasCalledOnce()
{
	LoggerMock logger;
	StateMock state(logger, true);

	state.update();
	state.update();
	state.update();
	state.update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, state.getCallsToUpdate());
}
