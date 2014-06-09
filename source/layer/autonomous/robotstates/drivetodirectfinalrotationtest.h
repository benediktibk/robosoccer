#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_DRIVETODIRECTFINALROTATIONTEST_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_DRIVETODIRECTFINALROTATIONTEST_H

#include "layer/autonomous/robotstates/robotstatetest.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Autonomous
{
	class DriveToDirectFinalRotationTest :
			public RobotStateTest
	{
		CPPUNIT_TEST_SUITE(DriveToDirectFinalRotationTest);
		CPPUNIT_TEST(reachedTarget_empty_false);
		CPPUNIT_TEST(update_onceCalled_robotGotOneCallToTurnToFinalOrientation);
		CPPUNIT_TEST(update_twiceCalled_robotGotOneCallToTurnToFinalOrientation);
		CPPUNIT_TEST(nextState_targetNotReached_0);
		CPPUNIT_TEST(nextState_targetReached_reachedTarget);
		CPPUNIT_TEST(nextState_movementStopped_reachedTarget);
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual RobotState* createInstance();

	private:
		void reachedTarget_empty_false();
		void update_onceCalled_robotGotOneCallToTurnToFinalOrientation();
		void update_twiceCalled_robotGotOneCallToTurnToFinalOrientation();
		void nextState_targetNotReached_0();
		void nextState_targetReached_reachedTarget();
		void nextState_movementStopped_reachedTarget();
	};
}
}
}

#endif