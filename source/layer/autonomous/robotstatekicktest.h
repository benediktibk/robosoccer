#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATEKICKTEST_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATEKICKTEST_H

#include "layer/autonomous/robotstatetest.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Autonomous
{
	class RobotStateKickTest :
			public RobotStateTest
	{
		CPPUNIT_TEST_SUITE(RobotStateKickTest);
		CPPUNIT_TEST(targetReached_empty_false);
		CPPUNIT_TEST(cantReachTarget_empty_false);
		CPPUNIT_TEST(nextState_noTimePassedBy_0);
		CPPUNIT_TEST(nextState_oneSecondWaited_followingState);
		CPPUNIT_TEST(update_severalTimesCalled_oneCallToKick);
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual RobotState* createInstance();

	private:
		void targetReached_empty_false();
		void cantReachTarget_empty_false();
		void nextState_noTimePassedBy_0();
		void nextState_oneSecondWaited_followingState();
		void update_severalTimesCalled_oneCallToKick();
	};
}
}
}

#endif


