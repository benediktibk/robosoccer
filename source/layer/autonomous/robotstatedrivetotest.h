#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATEDRIVETOTEST_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATEDRIVETOTEST_H

#include "layer/autonomous/robotstatetest.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Autonomous
{
	class RobotStateDriveToTest :
			public RobotStateTest
	{
		CPPUNIT_TEST_SUITE(RobotStateDriveToTest);
		CPPUNIT_TEST(reachedTarget_empty_false);
		CPPUNIT_TEST(cantReachTarget_noObstacles_false);
		CPPUNIT_TEST(nextState_targetNotYetReached_0);
		CPPUNIT_TEST(nextState_targetReached_targetReachedState);
		CPPUNIT_TEST(update_noObstacles_callToGoToPrecise);
		CPPUNIT_TEST(isEquivalentToDriveTo_sameTarget_true);
		CPPUNIT_TEST(isEquivalentToDriveTo_differentTarget_true);
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual RobotState* createInstance();

	private:
		void reachedTarget_empty_false();
		void cantReachTarget_noObstacles_false();
		void nextState_targetNotYetReached_0();
		void nextState_targetReached_targetReachedState();
		void update_noObstacles_callToGoToPrecise();
		void isEquivalentToDriveTo_sameTarget_true();
		void isEquivalentToDriveTo_differentTarget_true();
	};
}
}
}

#endif


