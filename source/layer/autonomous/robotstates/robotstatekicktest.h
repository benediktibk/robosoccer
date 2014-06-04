#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_ROBOTSTATEKICKTEST_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_ROBOTSTATEKICKTEST_H

#include "layer/autonomous/robotstates/robotstatetest.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Autonomous
{
	class KickTest :
			public RobotStateTest
	{
		CPPUNIT_TEST_SUITE(KickTest);
		CPPUNIT_TEST(targetReached_empty_false);
		CPPUNIT_TEST(cantReachTarget_empty_false);
		CPPUNIT_TEST(nextState_noTimePassedBy_0);
		CPPUNIT_TEST(nextState_oneSecondAndRobotStillMoving_0);
		CPPUNIT_TEST(nextState_robotNotMovingAnymore_reachedTarget);
		CPPUNIT_TEST(update_severalTimesCalled_oneCallToKick);
		CPPUNIT_TEST(isEquivalentToDriveTo_empty_false);
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual RobotState* createInstance();

	private:
		void targetReached_empty_false();
		void cantReachTarget_empty_false();
		void nextState_noTimePassedBy_0();
		void nextState_oneSecondAndRobotStillMoving_0();
		void nextState_robotNotMovingAnymore_reachedTarget();
		void update_severalTimesCalled_oneCallToKick();
		void isEquivalentToDriveTo_empty_false();
	};
}
}
}

#endif


