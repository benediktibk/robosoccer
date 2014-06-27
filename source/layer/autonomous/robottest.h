#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTTEST_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "common/geometry/pose.h"
#include <vector>

namespace RoboSoccer
{
namespace Common
{
namespace Time
{
	class WatchMock;
}
namespace Logging
{
	class LoggerMock;
}
namespace Routing
{
	class RouterMock;
	class RouterImpl;
}
}
namespace Layer
{
namespace Abstraction
{
	class ControllableRobotMock;
	class FieldPositionCheckerMock;
}
namespace Autonomous
{
	class RobotImpl;
	class IntelligentBallMock;
	class ObstacleFetcherMock;

	class RobotTest :
			public CPPUNIT_NS::TestFixture
	{
		CPPUNIT_TEST_SUITE(RobotTest);
		CPPUNIT_TEST(goTo_alreadyAtPosition_noCallToMoveRobot);
		CPPUNIT_TEST(goTo_notYetAtPosition_oneCallToMoveRobot);
		CPPUNIT_TEST(goTo_twiceWithSameTarget_oneCallToMoveRobot);
		CPPUNIT_TEST(goTo_positionOutsideTheFieldAndDriveSlowlyAtTheEnd_updateDoesNotCrash);
		CPPUNIT_TEST(goToDirect_alreadyAtPosition_noCallToMoveRobot);
		CPPUNIT_TEST(goToDirect_notYetAtPosition_oneCallToMoveRobot);
		CPPUNIT_TEST(goToDirect_twiceWithSameTarget_oneCallToMoveRobot);
		CPPUNIT_TEST(update_goToDirectAndInitialRotationNotReached_robotGotCallToTurnTowardsTarget);
		CPPUNIT_TEST(update_goToDirectAndInitialRotationNotReached_robotGotNoCallToDrive);
		CPPUNIT_TEST(update_goToDirectAndInitialRotationNotReachedTwiceCalled_robotGotNoAdditionalCallToTurn);
		CPPUNIT_TEST(update_goToDirectAndInitialRotationNotReachedButMovementStopped_robotGotGallToDriveToTargetImprecise);
		CPPUNIT_TEST(update_goToDirectAndPositionNotReached_robotGotCallToDriveToTargetImprecise);
		CPPUNIT_TEST(update_goToDirectAndPositionNotReached_robotGotNoCallToTurnTowardsTarget);
		CPPUNIT_TEST(update_goToDirectAndPositionNotReachedTwiceCalled_robotGotNoAdditionalCallToDriveToTargetImprecise);
		CPPUNIT_TEST(update_goToDirectAndPositionNotreachedButMovementStopped_robotGotCallToTurnTo);
		CPPUNIT_TEST(update_goToDirectAndFinalRotationNotReached_robotGotCallToTurn);
		CPPUNIT_TEST(update_goToDirectAndFinalRotationNotReached_robotGotNoCallToDrive);
		CPPUNIT_TEST(update_goToDirectAndFinalRotationNotReachedTwiceCalled_robotGotNoAdditionalCallToTurn);
		CPPUNIT_TEST(update_goToDirectAndInitialRotationReachedButRobotStillMoving_robotGotNoAdditionalCallsToMove);
		CPPUNIT_TEST(update_goToDirectAndPositionReachedButRobotStillMoving_robotGotNoAdditionalCallsToMove);
		CPPUNIT_TEST(update_goToDirectAndFinalRotationReachedButRobotStillMoving_robotGotNoAdditionalCallsToMove);
		CPPUNIT_TEST(update_goToDirectAndInitalRotationReachedAndMovementStopped_robotGotCallToMove);
		CPPUNIT_TEST(update_goToDirectAndPositionReachedAndMovementStopped_robotGotCallToTurn);
		CPPUNIT_TEST(update_goToAndInitialRotationNotReached_robotGotCallToTurnTowardsTarget);
		CPPUNIT_TEST(update_goToAndInitialRotationNotReached_robotGotNoCallToDrive);
		CPPUNIT_TEST(update_goToAndInitialRotationNotReachedTwiceCalled_robotGotNoAdditionalCallToTurn);
		CPPUNIT_TEST(update_goToAndInitialRotationNotReachedButMovementStopped_robotGotGallToDriveToTargetImprecise);
		CPPUNIT_TEST(update_goToAndPositionNotReached_robotGotCallToDriveToTargetImprecise);
		CPPUNIT_TEST(update_goToAndPositionNotReached_robotGotNoCallToTurnTowardsTarget);
		CPPUNIT_TEST(update_goToAndPositionNotReachedTwiceCalled_robotGotNoAdditionalCallToDriveToTargetImprecise);
		CPPUNIT_TEST(update_goToAndPositionNotreachedButMovementStopped_robotGotCallToTurnTo);
		CPPUNIT_TEST(update_goToAndFinalRotationNotReached_robotGotCallToTurn);
		CPPUNIT_TEST(update_goToAndFinalRotationNotReached_robotGotNoCallToDrive);
		CPPUNIT_TEST(update_goToAndFinalRotationNotReachedTwiceCalled_robotGotNoAdditionalCallToTurn);
		CPPUNIT_TEST(update_goToAndFinalRotationNotReachedButMovementStopped_reachedTarget);
		CPPUNIT_TEST(update_goToAndInitialRotationReachedButRobotStillMoving_robotGotNoAdditionalCallsToMove);
		CPPUNIT_TEST(update_goToAndPositionReachedButRobotStillMoving_robotGotNoAdditionalCallsToMove);
		CPPUNIT_TEST(update_goToAndFinalRotationReachedButRobotStillMoving_robotGotNoAdditionalCallsToMove);
		CPPUNIT_TEST(update_goToAndInitalRotationReachedAndMovementStopped_robotGotCallToMove);
		CPPUNIT_TEST(update_goToAndPositionReachedAndMovementStopped_robotGotCallToTurn);
		CPPUNIT_TEST(update_goToAndInitialRotationNotReachedAndThreePointsInRoute_turningToSecondPoint);
		CPPUNIT_TEST(update_goToAndInitialRotationReachedAndThreePointsInRoute_robotGotCallToMoveToSecondPoint);
		CPPUNIT_TEST(update_goToAndSecondPositionReachedAndRotationNotReached_turningToThirdPoint);
		CPPUNIT_TEST(update_goToAndSecondPositionReachedAndRotationReached_robotGotCallToMoveToThirdPoint);
		CPPUNIT_TEST(update_goToAndThirdPositionReachedAndFinalRotationNotReached_turningToFinalRotation);
		CPPUNIT_TEST(update_goToAndInitialRotationReachedAndThreePointsInRouteAndMovementStoppedByRobot_robotGotCallToMoveToSecondPoint);
		CPPUNIT_TEST(update_goToAndSecondPositionReachedAndRotationNotReachedAndAllIntermediateMovementsStoppedByRobot_turningToThirdPoint);
		CPPUNIT_TEST(update_goToAndSecondPositionReachedAndRotationReachedAndAllIntermediateMovementsStoppedByRobot_robotGotCallToMoveToThirdPoint);
		CPPUNIT_TEST(update_goToAndInitialRotationReachedAndRouteChanged_robotGotTwoCallsToTurn);
		CPPUNIT_TEST(update_goToAndInitialRotationReachedAndRouteChangedAndInitialRotationReachedAgain_robotGotTwoCallsToDrive);
		CPPUNIT_TEST(update_goToAndInitialRotationNotReachedAndObstacleMovedALittleBit_turningToSecondPoint);
		CPPUNIT_TEST(update_goToAndInitialRotationNotReachedAndObstacleMoved_turningToSecondPointOfNewRoute);
		CPPUNIT_TEST(update_goToAndIgnoreBall_routePointsCountIs2);
		CPPUNIT_TEST(update_goToAndCloseToThirdPositionAndDriveSlowlyAtTheEnd_robotGotCallToDriveSlowly);
		CPPUNIT_TEST(update_goToAndTargetNotInsideField_noCallToDriveAndTurn);
		CPPUNIT_TEST(update_goToAndObstacleOnTargetAndIgnoreObstacle_robotGotCallToDrive);
		CPPUNIT_TEST(update_kickAndTurnToReachedTarget_oneCallToKick);
		CPPUNIT_TEST(update_empty_robotGotCallToUpdate);
		CPPUNIT_TEST(update_goToAndAtTarget_reachedTarget);
		CPPUNIT_TEST(update_goToDirectAndAtTarget_reachedTarget);
		CPPUNIT_TEST(update_finalRotationReachedThroughMovementStopped_movementHasNotStopped);
		CPPUNIT_TEST(goTo_movementStoppedBefore_movementNotStopped);
		CPPUNIT_TEST(goToDirect_movementStoppedBefore_movementNotStopped);
		CPPUNIT_TEST(kick_movementStoppedBefore_movementNotStopped);
		CPPUNIT_TEST(goTo_movementStoppedBeforeAndUpdate_movementNotStopped);
		CPPUNIT_TEST(goToDirect_movementStoppedBeforeAndUpdate_movementNotStopped);
		CPPUNIT_TEST(kick_movementStoppedBeforeAndUpdate_movementNotStopped);
		CPPUNIT_TEST(getObstacle_empty_sameAsFromControllableRobot);
		CPPUNIT_TEST(getObstacles_empty_oneWhichIsSameAsFromControllableRobot);
		CPPUNIT_TEST(update_kickAndRobotInGoalZone_robotGotOneCallToKick);
		CPPUNIT_TEST(goTo_robotAtSecondTarget_noCallToDrive);
		CPPUNIT_TEST(update_goToAndInitialRotationReachedAndNewRouteIsMuchBetter_robotGotTwoCallsToTurn);
		CPPUNIT_TEST(update_goToAndInitialRotationReachedAndNewRouteIsMuchBetterButInvalid_robotGotCallToDriveToSecondPoint);
		CPPUNIT_TEST(update_initialRotationNotReachedAndNewRouteIsMuchBetter_robotGotTwoCallsToTurn);
		CPPUNIT_TEST(update_initialRotationNotReachedAndNewRouteIsMuchBetterButInvalid_robotGotCallToTurn);
		CPPUNIT_TEST_SUITE_END();

	public:
		virtual void setUp();
		virtual void tearDown();

	private:
		void goTo_alreadyAtPosition_noCallToMoveRobot();
		void goTo_notYetAtPosition_oneCallToMoveRobot();
		void goTo_twiceWithSameTarget_oneCallToMoveRobot();
		void goTo_positionOutsideTheFieldAndDriveSlowlyAtTheEnd_updateDoesNotCrash();
		void goToDirect_alreadyAtPosition_noCallToMoveRobot();
		void goToDirect_notYetAtPosition_oneCallToMoveRobot();
		void goToDirect_twiceWithSameTarget_oneCallToMoveRobot();
		void update_goToDirectAndInitialRotationNotReached_robotGotCallToTurnTowardsTarget();
		void update_goToDirectAndInitialRotationNotReached_robotGotNoCallToDrive();
		void update_goToDirectAndInitialRotationNotReachedTwiceCalled_robotGotNoAdditionalCallToTurn();
		void update_goToDirectAndInitialRotationNotReachedButMovementStopped_robotGotGallToDriveToTargetImprecise();
		void update_goToDirectAndPositionNotReached_robotGotCallToDriveToTargetImprecise();
		void update_goToDirectAndPositionNotReached_robotGotNoCallToTurnTowardsTarget();
		void update_goToDirectAndPositionNotReachedTwiceCalled_robotGotNoAdditionalCallToDriveToTargetImprecise();
		void update_goToDirectAndPositionNotreachedButMovementStopped_robotGotCallToTurnTo();
		void update_goToDirectAndFinalRotationNotReached_robotGotCallToTurn();
		void update_goToDirectAndFinalRotationNotReached_robotGotNoCallToDrive();
		void update_goToDirectAndFinalRotationNotReachedTwiceCalled_robotGotNoAdditionalCallToTurn();
		void update_goToDirectAndInitialRotationReachedButRobotStillMoving_robotGotNoAdditionalCallsToMove();
		void update_goToDirectAndPositionReachedButRobotStillMoving_robotGotNoAdditionalCallsToMove();
		void update_goToDirectAndFinalRotationReachedButRobotStillMoving_robotGotNoAdditionalCallsToMove();
		void update_goToDirectAndInitalRotationReachedAndMovementStopped_robotGotCallToMove();
		void update_goToDirectAndPositionReachedAndMovementStopped_robotGotCallToTurn();
		void update_goToAndInitialRotationNotReached_robotGotCallToTurnTowardsTarget();
		void update_goToAndInitialRotationNotReached_robotGotNoCallToDrive();
		void update_goToAndInitialRotationNotReachedTwiceCalled_robotGotNoAdditionalCallToTurn();
		void update_goToAndInitialRotationNotReachedButMovementStopped_robotGotGallToDriveToTargetImprecise();
		void update_goToAndPositionNotReached_robotGotCallToDriveToTargetImprecise();
		void update_goToAndPositionNotReached_robotGotNoCallToTurnTowardsTarget();
		void update_goToAndPositionNotReachedTwiceCalled_robotGotNoAdditionalCallToDriveToTargetImprecise();
		void update_goToAndPositionNotreachedButMovementStopped_robotGotCallToTurnTo();
		void update_goToAndFinalRotationNotReached_robotGotCallToTurn();
		void update_goToAndFinalRotationNotReached_robotGotNoCallToDrive();
		void update_goToAndFinalRotationNotReachedTwiceCalled_robotGotNoAdditionalCallToTurn();
		void update_goToAndFinalRotationNotReachedButMovementStopped_reachedTarget();
		void update_goToAndInitialRotationReachedButRobotStillMoving_robotGotNoAdditionalCallsToMove();
		void update_goToAndPositionReachedButRobotStillMoving_robotGotNoAdditionalCallsToMove();
		void update_goToAndFinalRotationReachedButRobotStillMoving_robotGotNoAdditionalCallsToMove();
		void update_goToAndInitalRotationReachedAndMovementStopped_robotGotCallToMove();
		void update_goToAndPositionReachedAndMovementStopped_robotGotCallToTurn();
		void update_goToAndInitialRotationNotReachedAndThreePointsInRoute_turningToSecondPoint();
		void update_goToAndInitialRotationReachedAndThreePointsInRoute_robotGotCallToMoveToSecondPoint();
		void update_goToAndSecondPositionReachedAndRotationNotReached_turningToThirdPoint();
		void update_goToAndSecondPositionReachedAndRotationReached_robotGotCallToMoveToThirdPoint();
		void update_goToAndThirdPositionReachedAndFinalRotationNotReached_turningToFinalRotation();
		void update_goToAndInitialRotationReachedAndThreePointsInRouteAndMovementStoppedByRobot_robotGotCallToMoveToSecondPoint();
		void update_goToAndSecondPositionReachedAndRotationNotReachedAndAllIntermediateMovementsStoppedByRobot_turningToThirdPoint();
		void update_goToAndSecondPositionReachedAndRotationReachedAndAllIntermediateMovementsStoppedByRobot_robotGotCallToMoveToThirdPoint();
		void update_goToAndInitialRotationReachedAndRouteChanged_robotGotTwoCallsToTurn();
		void update_goToAndInitialRotationReachedAndRouteChangedAndInitialRotationReachedAgain_robotGotTwoCallsToDrive();
		void update_goToAndInitialRotationNotReachedAndObstacleMovedALittleBit_turningToSecondPoint();
		void update_goToAndInitialRotationNotReachedAndObstacleMoved_turningToSecondPointOfNewRoute();
		void update_goToAndIgnoreBall_routePointsCountIs2();
		void update_goToAndCloseToThirdPositionAndDriveSlowlyAtTheEnd_robotGotCallToDriveSlowly();
		void update_goToAndTargetNotInsideField_noCallToDriveAndTurn();
		void update_goToAndObstacleOnTargetAndIgnoreObstacle_robotGotCallToDrive();
		void update_kickAndTurnToReachedTarget_oneCallToKick();
		void update_empty_robotGotCallToUpdate();
		void update_goToAndAtTarget_reachedTarget();
		void update_goToDirectAndAtTarget_reachedTarget();
		void update_finalRotationReachedThroughMovementStopped_movementHasNotStopped();
		void goTo_movementStoppedBefore_movementNotStopped();
		void goToDirect_movementStoppedBefore_movementNotStopped();
		void kick_movementStoppedBefore_movementNotStopped();
		void goTo_movementStoppedBeforeAndUpdate_movementNotStopped();
		void goToDirect_movementStoppedBeforeAndUpdate_movementNotStopped();
		void kick_movementStoppedBeforeAndUpdate_movementNotStopped();
		void getObstacle_empty_sameAsFromControllableRobot();
		void getObstacles_empty_oneWhichIsSameAsFromControllableRobot();
		void update_kickAndRobotInGoalZone_robotGotOneCallToKick();
		void goTo_robotAtSecondTarget_noCallToDrive();
		void update_goToAndInitialRotationReachedAndNewRouteIsMuchBetter_robotGotTwoCallsToTurn();
		void update_goToAndInitialRotationReachedAndNewRouteIsMuchBetterButInvalid_robotGotCallToDriveToSecondPoint();
		void update_initialRotationNotReachedAndNewRouteIsMuchBetter_robotGotTwoCallsToTurn();
		void update_initialRotationNotReachedAndNewRouteIsMuchBetterButInvalid_robotGotCallToTurn();

	private:
		Abstraction::ControllableRobotMock *m_hardwareRobot;
		Common::Time::WatchMock *m_watch;
		Common::Logging::LoggerMock *m_logger;
		Common::Routing::RouterMock *m_routerMock;
		Common::Routing::RouterImpl *m_router;
		Abstraction::FieldPositionCheckerMock *m_field;
		ObstacleFetcherMock *m_obstacleFetcher;
		std::vector<Common::Geometry::Pose> m_targets;
		RobotImpl *m_robot;
		RobotImpl *m_robotWithRealRouter;
		IntelligentBallMock *m_ball;
	};
}
}
}

#endif
