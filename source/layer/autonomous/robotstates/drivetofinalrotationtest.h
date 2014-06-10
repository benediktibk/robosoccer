#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_DRIVETOFINALROTATIONTEST_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_DRIVETOFINALROTATIONTEST_H

#include "layer/autonomous/robotstates/robotstatetest.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Autonomous
{
	class DriveToFinalRotationTest :
			public RobotStateTest
	{
		CPPUNIT_TEST_SUITE(DriveToFinalRotationTest);
		CPPUNIT_TEST(constructor_routeWithTwoPoints_routeHasTwoPoints);
		CPPUNIT_TEST(update_onceCalled_robotGotOneCallToTurnToFinalRotation);
		CPPUNIT_TEST(update_twiceCalled_robotGotOneCallToTurnToFinalRotation);
		CPPUNIT_TEST(nextState_finalRotationNotReached_0);
		CPPUNIT_TEST(nextState_finalRotationReached_reachedTarget);
		CPPUNIT_TEST(nextState_movementStopped_reachedTarget);
		CPPUNIT_TEST(reachedTarget_empty_false);
		CPPUNIT_TEST(nextState_currentTargetIsTheSecondTargetAndFinalRotationNotReached_0);
		CPPUNIT_TEST(nextState_currentTargetIsTheSecondTargetAndFinalRotationReached_reachedTarget);
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual RobotState* createInstance();

	private:
		void constructor_routeWithTwoPoints_routeHasTwoPoints();
		void update_onceCalled_robotGotOneCallToTurnToFinalRotation();
		void update_twiceCalled_robotGotOneCallToTurnToFinalRotation();
		void nextState_finalRotationNotReached_0();
		void nextState_finalRotationReached_reachedTarget();
		void nextState_movementStopped_reachedTarget();
		void reachedTarget_empty_false();
		void nextState_currentTargetIsTheSecondTargetAndFinalRotationNotReached_0();
		void nextState_currentTargetIsTheSecondTargetAndFinalRotationReached_reachedTarget();
	};
}
}
}

#endif
