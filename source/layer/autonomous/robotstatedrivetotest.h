#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATEDRIVETOTEST_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATEDRIVETOTEST_H

#include "layer/autonomous/robotstatetest.h"

namespace RoboSoccer
{
namespace Common
{
namespace Routing
{
	class RouterImpl;
}
}
namespace Layer
{
namespace Main
{
	class FieldPositionCheckerFieldPlayer;
}
namespace Autonomous
{
	class RobotState;

	class RobotStateDriveToTest :
			public RobotStateTest
	{
		CPPUNIT_TEST_SUB_SUITE(RobotStateDriveToTest, RobotStateTest);
		CPPUNIT_TEST(nextState_targetNotReached_0);
		CPPUNIT_TEST(nextState_targetReached_reachedTargetState);
		CPPUNIT_TEST(nextState_longTimeWaited_reachedTargetState);
		CPPUNIT_TEST(update_initialRotationNotReached_robotGotCallToTurnTowardsTarget);
		CPPUNIT_TEST(update_initialRotationNotReached_robotGotNoCallToDrive);
		CPPUNIT_TEST(update_initialRotationNotReachedTwiceCalled_robotGotNoAdditionalCallToTurn);
		CPPUNIT_TEST(update_initialRotationNotReachedButMovementStopped_robotGotGallToDriveToTargetImprecise);
		CPPUNIT_TEST(update_positionNotReached_robotGotCallToDriveToTargetImprecise);
		CPPUNIT_TEST(update_positionNotReached_robotGotNoCallToTurnTowardsTarget);
		CPPUNIT_TEST(update_positionNotReachedTwiceCalled_robotGotNoAdditionalCallToDriveToTargetImprecise);
		CPPUNIT_TEST(update_positionNotreachedButMovementStopped_robotGotCallToTurnTo);
		CPPUNIT_TEST(update_finalRotationNotReached_robotGotCallToTurn);
		CPPUNIT_TEST(update_finalRotationNotReached_robotGotNoCallToDrive);
		CPPUNIT_TEST(update_finalRotationNotReachedTwiceCalled_robotGotNoAdditionalCallToTurn);
		CPPUNIT_TEST(update_finalRotationNotReachedButMovementStopped_nextStateWouldBeReachedTarget);
		CPPUNIT_TEST(update_initialRotationReachedButRobotStillMoving_robotGotNoAdditionalCallsToMove);
		CPPUNIT_TEST(update_positionReachedButRobotStillMoving_robotGotNoAdditionalCallsToMove);
		CPPUNIT_TEST(update_finalRotationReachedButRobotStillMoving_robotGotNoAdditionalCallsToMove);
		CPPUNIT_TEST(update_initalRotationReachedAndMovementStopped_robotGotCallToMove);
		CPPUNIT_TEST(update_positionReachedAndMovementStopped_robotGotCallToTurn);
		CPPUNIT_TEST(isEquivalentToDriveTo_empty_false);
		CPPUNIT_TEST(isEquivalentToDriveToDirect_sameTarget_true);
		CPPUNIT_TEST(isEquivalentToDriveToDirect_differentTarget_false);
		CPPUNIT_TEST(reachedTarget_empty_false);
		CPPUNIT_TEST(cantReachTarget_empty_false);
		CPPUNIT_TEST_SUITE_END();

	public:
		virtual void setUp();
		virtual void tearDown();

	protected:
		virtual RobotState* createInstance();

	private:
		void nextState_targetNotReached_0();
		void nextState_targetReached_reachedTargetState();
		void nextState_longTimeWaited_reachedTargetState();
		void update_initialRotationNotReached_robotGotCallToTurnTowardsTarget();
		void update_initialRotationNotReached_robotGotNoCallToDrive();
		void update_initialRotationNotReachedTwiceCalled_robotGotNoAdditionalCallToTurn();
		void update_initialRotationNotReachedButMovementStopped_robotGotGallToDriveToTargetImprecise();
		void update_positionNotReached_robotGotCallToDriveToTargetImprecise();
		void update_positionNotReached_robotGotNoCallToTurnTowardsTarget();
		void update_positionNotReachedTwiceCalled_robotGotNoAdditionalCallToDriveToTargetImprecise();
		void update_positionNotreachedButMovementStopped_robotGotCallToTurnTo();
		void update_finalRotationNotReached_robotGotCallToTurn();
		void update_finalRotationNotReached_robotGotNoCallToDrive();
		void update_finalRotationNotReachedTwiceCalled_robotGotNoAdditionalCallToTurn();
		void update_finalRotationNotReachedButMovementStopped_nextStateWouldBeReachedTarget();
		void update_initialRotationReachedButRobotStillMoving_robotGotNoAdditionalCallsToMove();
		void update_positionReachedButRobotStillMoving_robotGotNoAdditionalCallsToMove();
		void update_finalRotationReachedButRobotStillMoving_robotGotNoAdditionalCallsToMove();
		void update_initalRotationReachedAndMovementStopped_robotGotCallToMove();
		void update_positionReachedAndMovementStopped_robotGotCallToTurn();
		void isEquivalentToDriveTo_empty_false();
		void isEquivalentToDriveToDirect_sameTarget_true();
		void isEquivalentToDriveToDirect_differentTarget_false();
		void reachedTarget_empty_false();
		void cantReachTarget_empty_false();

	private:
		RobotState *m_robotStateWithRouter;
		Common::Routing::RouterImpl *m_routerImpl;
		Main::FieldPositionCheckerFieldPlayer *m_field;
	};
}
}
}

#endif


