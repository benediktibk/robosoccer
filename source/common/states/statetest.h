#ifndef ROBOSOCCER_COMMON_STATES_STATETEST_H
#define ROBOSOCCER_COMMON_STATES_STATETEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace RoboSoccer
{
namespace Common
{
namespace States
{
	class StateTest :
			public CPPUNIT_NS::TestFixture
	{
	public:
		CPPUNIT_TEST_SUITE(StateTest);
		CPPUNIT_TEST(update_updateAlwaysAndCalledThreeTimes_updateInternalWasCalledThreeTimes);
		CPPUNIT_TEST(update_updateOnlyOnceAndCalledFourTimes_updateInternalWasCalledOnce);
		CPPUNIT_TEST(updateAlreadyCalled_onceUpdateCalled_true);
		CPPUNIT_TEST(updateAlreadyCalled_neverUpdateCalled_false);
		CPPUNIT_TEST_SUITE_END();

	private:
		void update_updateAlwaysAndCalledThreeTimes_updateInternalWasCalledThreeTimes();
		void update_updateOnlyOnceAndCalledFourTimes_updateInternalWasCalledOnce();
		void updateAlreadyCalled_onceUpdateCalled_true();
		void updateAlreadyCalled_neverUpdateCalled_false();
	};
}
}
}

#endif


