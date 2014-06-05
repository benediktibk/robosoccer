#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_DRIVETODIRECTINITIALROTATIONTEST_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_DRIVETODIRECTINITIALROTATIONTEST_H

#include "layer/autonomous/robotstates/robotstatetest.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Autonomous
{
	class DriveToDirectInitialRotationTest :
			public RobotStateTest
	{
		CPPUNIT_TEST_SUITE(DriveToDirectInitialRotationTest);
		CPPUNIT_TEST(reachedTarget_empty_false);
		CPPUNIT_TEST(update_onceCalled_robotGotCallToTurnToTarget);
		CPPUNIT_TEST(update_twiceCalled_robotGotCallToTurnToTarget);
		CPPUNIT_TEST(nextState_rotationNotReached_0);
		CPPUNIT_TEST(nextState_rotationReached_driving);
		CPPUNIT_TEST(nextState_movementStopped_driving);
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual RobotState* createInstance();

	private:
		void reachedTarget_empty_false();
		void update_onceCalled_robotGotCallToTurnToTarget();
		void update_twiceCalled_robotGotCallToTurnToTarget();
		void nextState_rotationNotReached_0();
		void nextState_rotationReached_driving();
		void nextState_movementStopped_driving();
	};
}
}
}

#endif