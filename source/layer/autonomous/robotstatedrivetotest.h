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
		CPPUNIT_TEST(nextState_took10s_targetReachedState);
		CPPUNIT_TEST(nextState_took10sWithSeveralCalls_targetReachedState);
		CPPUNIT_TEST(update_initialRotationNotReached_robotGotCallToTurnTowardsTarget);
		CPPUNIT_TEST(update_initialRotationNotReached_robotGotNoCallToDrive);
		CPPUNIT_TEST(update_initialRotationNotReachedTwiceCalled_robotGotNoAdditionalCallToTurn);
		CPPUNIT_TEST(update_positionNotReached_robotGotCallToDriveToTargetPrecise);
		CPPUNIT_TEST(update_positionNotReached_robotGotNoCallToTurnTowardsTarget);
		CPPUNIT_TEST(update_positionNotReachedTwiceCalled_robotGotNoAdditionalCallToDriveToTargetPrecise);
		CPPUNIT_TEST(update_finalRotationNotReached_robotGotCallToTurn);
		CPPUNIT_TEST(update_finalRotationNotReached_robotGotNoCallToDrive);
		CPPUNIT_TEST(update_finalRotationNotReachedTwiceCalled_robotGotNoAdditionalCallToTurn);
		CPPUNIT_TEST(update_initialRotationReachedButRobotStillMoving_robotGotNoAdditionalCallsToMove);
		CPPUNIT_TEST(update_positionReachedButRobotStillMoving_robotGotNoAdditionalCallsToMove);
		CPPUNIT_TEST(update_finalRotationReachedButRobotStillMoving_robotGotNoAdditionalCallsToMove);
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
		void nextState_took10s_targetReachedState();
		void nextState_took10sWithSeveralCalls_targetReachedState();
		void update_initialRotationNotReached_robotGotCallToTurnTowardsTarget();
		void update_initialRotationNotReached_robotGotNoCallToDrive();
		void update_initialRotationNotReachedTwiceCalled_robotGotNoAdditionalCallToTurn();
		void update_positionNotReached_robotGotCallToDriveToTargetPrecise();
		void update_positionNotReached_robotGotNoCallToTurnTowardsTarget();
		void update_positionNotReachedTwiceCalled_robotGotNoAdditionalCallToDriveToTargetPrecise();
		void update_finalRotationNotReached_robotGotCallToTurn();
		void update_finalRotationNotReached_robotGotNoCallToDrive();
		void update_finalRotationNotReachedTwiceCalled_robotGotNoAdditionalCallToTurn();
		void update_initialRotationReachedButRobotStillMoving_robotGotNoAdditionalCallsToMove();
		void update_positionReachedButRobotStillMoving_robotGotNoAdditionalCallsToMove();
		void update_finalRotationReachedButRobotStillMoving_robotGotNoAdditionalCallsToMove();
		void isEquivalentToDriveTo_sameTarget_true();
		void isEquivalentToDriveTo_differentTarget_true();
	};
}
}
}

#endif


