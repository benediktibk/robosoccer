#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTTEST_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTTEST_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

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
}
}
namespace Layer
{
namespace Abstraction
{
	class ControllableRobotMock;
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
		CPPUNIT_TEST(update_kickAndTurnToReachedTarget_oneCallToKick);
		CPPUNIT_TEST(update_empty_robotGotCallToUpdate);
		CPPUNIT_TEST(getObstacle_empty_sameAsFromControllableRobot);
		CPPUNIT_TEST(getObstacles_empty_oneWhichIsSameAsFromControllableRobot);
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

		void update_kickAndTurnToReachedTarget_oneCallToKick();
		void update_empty_robotGotCallToUpdate();
		void getObstacle_empty_sameAsFromControllableRobot();
		void getObstacles_empty_oneWhichIsSameAsFromControllableRobot();

	private:
		Abstraction::ControllableRobotMock *m_hardwareRobot;
		Common::Time::WatchMock *m_watch;
		Common::Logging::LoggerMock *m_logger;
		Common::Routing::RouterMock *m_router;
		ObstacleFetcherMock *m_obstacleFetcher;
		RobotImpl *m_robot;
		IntelligentBallMock *m_ball;
	};
}
}
}

#endif
