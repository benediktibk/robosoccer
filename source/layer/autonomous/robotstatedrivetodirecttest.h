#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATEDRIVETODIRECTTEST_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATEDRIVETODIRECTTEST_H

#include "layer/autonomous/robotstatetest.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Autonomous
{
	class RobotStateDriveToDirectTest :
			public RobotStateTest
	{
		CPPUNIT_TEST_SUITE(RobotStateDriveToDirectTest);
		CPPUNIT_TEST(nextState_targetNotReached_0);
		CPPUNIT_TEST(nextState_targetReached_reachedTargetState);
		CPPUNIT_TEST(nextState_longTimeWaited_reachedTargetState);
		CPPUNIT_TEST(update_initialRotationNotReached_robotGotCallToTurnTowardsTarget);
		CPPUNIT_TEST(update_initialRotationNotReached_robotGotNoCallToDrive);
		CPPUNIT_TEST(update_initialRotationNotReachedTwiceCalled_robotGotNoAdditionalCallToTurn);
		CPPUNIT_TEST(update_positionNotReached_robotGotCallToDriveToTargetImprecise);
		CPPUNIT_TEST(update_positionNotReached_robotGotNoCallToTurnTowardsTarget);
		CPPUNIT_TEST(update_positionNotReachedTwiceCalled_robotGotNoAdditionalCallToDriveToTargetImprecise);
		CPPUNIT_TEST(update_finalRotationNotReached_robotGotCallToTurn);
		CPPUNIT_TEST(update_finalRotationNotReached_robotGotNoCallToDrive);
		CPPUNIT_TEST(update_finalRotationNotReachedTwiceCalled_robotGotNoAdditionalCallToTurn);
		CPPUNIT_TEST(isEquivalentToDriveTo_empty_false);
		CPPUNIT_TEST(isEquivalentToDriveToDirect_sameTarget_true);
		CPPUNIT_TEST(isEquivalentToDriveToDirect_differentTarget_false);
		CPPUNIT_TEST(reachedTarget_empty_false);
		CPPUNIT_TEST(cantReachTarget_empty_false);
		CPPUNIT_TEST_SUITE_END();

	protected:
		virtual RobotState* createInstance();

	private:
		void nextState_targetNotReached_0();
		void nextState_targetReached_reachedTargetState();
		void nextState_longTimeWaited_reachedTargetState();
		void update_initialRotationNotReached_robotGotCallToTurnTowardsTarget();
		void update_initialRotationNotReached_robotGotNoCallToDrive();
		void update_initialRotationNotReachedTwiceCalled_robotGotNoAdditionalCallToTurn();
		void update_positionNotReached_robotGotCallToDriveToTargetImprecise();
		void update_positionNotReached_robotGotNoCallToTurnTowardsTarget();
		void update_positionNotReachedTwiceCalled_robotGotNoAdditionalCallToDriveToTargetImprecise();
		void update_finalRotationNotReached_robotGotCallToTurn();
		void update_finalRotationNotReached_robotGotNoCallToDrive();
		void update_finalRotationNotReachedTwiceCalled_robotGotNoAdditionalCallToTurn();
		void isEquivalentToDriveTo_empty_false();
		void isEquivalentToDriveToDirect_sameTarget_true();
		void isEquivalentToDriveToDirect_differentTarget_false();
		void reachedTarget_empty_false();
		void cantReachTarget_empty_false();
	};
}
}
}

#endif
