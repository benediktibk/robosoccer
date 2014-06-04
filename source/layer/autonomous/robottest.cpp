#include "layer/autonomous/robottest.h"
#include "layer/autonomous/robotimpl.h"
#include "layer/autonomous/intelligentballmock.h"
#include "layer/autonomous/obstaclefetchermock.h"
#include "layer/autonomous/robotstates/driveto.h"
#include "layer/abstraction/controllablerobotmock.h"
#include "common/time/watchmock.h"
#include "common/logging/loggermock.h"
#include "common/geometry/pose.h"
#include "common/geometry/compare.h"
#include "common/routing/routermock.h"
#include "common/routing/routerimpl.h"
#include "common/routing/fieldpositioncheckermock.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Time;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Routing;
using namespace std;

void RobotTest::setUp()
{
	m_hardwareRobot = new ControllableRobotMock();
	m_watch = new WatchMock();
	m_logger = new LoggerMock();
	m_routerMock = new RouterMock();
	m_field = new FieldPositionCheckerMock();
	m_router = new RouterImpl(ReadableRobot::getWidth(), *m_field);
	m_obstacleFetcher = new ObstacleFetcherMock();
	m_robot = new RobotImpl(*m_hardwareRobot, *m_routerMock, *m_watch, *m_logger, 0, *m_obstacleFetcher);
	m_robotWithRealRouter = new RobotImpl(*m_hardwareRobot, *m_router, *m_watch, *m_logger, 0, *m_obstacleFetcher);
	m_ball = new IntelligentBallMock();
}

void RobotTest::tearDown()
{
	delete m_robot;
	m_robot = 0;
	delete m_robotWithRealRouter;
	m_robotWithRealRouter = 0;
	delete m_hardwareRobot;
	m_hardwareRobot = 0;
	delete m_routerMock;
	m_routerMock = 0;
	delete m_router;
	m_router = 0;
	delete m_field;
	m_field = 0;
	delete m_watch;
	m_watch = 0;
	delete m_logger;
	m_logger = 0;
	delete m_ball;
	m_ball = 0;
	delete m_obstacleFetcher;
	m_obstacleFetcher = 0;
}

void RobotTest::goTo_alreadyAtPosition_noCallToMoveRobot()
{
	m_hardwareRobot->setPose(Pose(Point(1, 3), Angle()));

	m_robot->goTo(Pose(Point(1, 3), Angle()), false, false, false);
	m_robot->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_hardwareRobot->getCallsToGoToCombined());
}

void RobotTest::goTo_notYetAtPosition_oneCallToMoveRobot()
{
	m_hardwareRobot->setPose(Pose(Point(1, 3), Angle()));

	m_robot->goTo(Pose(Point(2, 3), Angle()), false, false, false);
	m_robot->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToGoToCombined());
}

void RobotTest::goTo_twiceWithSameTarget_oneCallToMoveRobot()
{
	m_hardwareRobot->setPose(Pose(Point(1, 3), Angle()));

	m_robot->goTo(Pose(Point(2, 3), Angle()), false, false, false);
	m_robot->update();
	m_robot->goTo(Pose(Point(2, 3), Angle()), false, false, false);
	m_robot->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToGoToCombined());
}

void RobotTest::goTo_positionOutsideTheFieldAndDriveSlowlyAtTheEnd_updateDoesNotCrash()
{
	m_routerMock->setInvalidRoute();

	m_robot->goTo(Pose(Point(2, 3), Angle()), false, true, false);
	m_robot->update();

	CPPUNIT_ASSERT(true);
}

void RobotTest::goToDirect_alreadyAtPosition_noCallToMoveRobot()
{
	m_hardwareRobot->setPose(Pose(Point(1, 3), Angle()));

	m_robot->goToDirect(Pose(Point(1, 3), Angle()));
	m_robot->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_hardwareRobot->getCallsToGoToCombined());
}

void RobotTest::goToDirect_notYetAtPosition_oneCallToMoveRobot()
{
	m_hardwareRobot->setPose(Pose(Point(1, 3), Angle()));

	m_robot->goToDirect(Pose(Point(2, 3), Angle()));
	m_robot->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToGoToCombined());
}

void RobotTest::goToDirect_twiceWithSameTarget_oneCallToMoveRobot()
{
	m_hardwareRobot->setPose(Pose(Point(1, 3), Angle()));

	m_robot->goToDirect(Pose(Point(2, 3), Angle()));
	m_robot->update();
	m_robot->goToDirect(Pose(Point(2, 3), Angle()));
	m_robot->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToGoToCombined());
}

void RobotTest::update_goToDirectAndInitialRotationNotReached_robotGotCallToTurnTowardsTarget()
{
	m_robot->goToDirect(Pose(Point(5, 4), Angle::getQuarterRotation()));
	m_hardwareRobot->setPose(Pose(Point(1, 2), Angle()));

	m_robot->update();

	Compare compare(0.0001);
	Angle targetShouldBe(Point(1, 2), Point(5, 4));
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToTurn());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(targetShouldBe, m_hardwareRobot->getLastAngleToTurnTo()));
}

void RobotTest::update_goToDirectAndInitialRotationNotReached_robotGotNoCallToDrive()
{
	m_robot->goToDirect(Pose(Point(5, 4), Angle::getQuarterRotation()));
	m_hardwareRobot->setPose(Pose(Point(1, 2), Angle()));

	m_robot->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_hardwareRobot->getCallsToGoToPositionPrecise());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_hardwareRobot->getCallsToGoToPositionImprecise());
}

void RobotTest::update_goToDirectAndInitialRotationNotReachedTwiceCalled_robotGotNoAdditionalCallToTurn()
{
	m_robot->goToDirect(Pose(Point(5, 4), Angle::getQuarterRotation()));
	m_hardwareRobot->setPose(Pose(Point(1, 2), Angle()));

	m_robot->update();
	m_robot->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToTurn());
}

void RobotTest::update_goToDirectAndInitialRotationNotReachedButMovementStopped_robotGotGallToDriveToTargetImprecise()
{
	m_robot->goToDirect(Pose(Point(5, 4), Angle::getQuarterRotation()));
	m_hardwareRobot->setPose(Pose(Point(1, 2), Angle()));
	m_robot->update();
	m_hardwareRobot->setIsMoving(true);
	m_robot->update();
	m_hardwareRobot->setIsMoving(false);
	m_robot->update();

	Compare compare(0.00001);
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToGoToPositionPrecise());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(5, 4), m_hardwareRobot->getLastPointToDriveTo()));
}

void RobotTest::update_goToDirectAndPositionNotReached_robotGotCallToDriveToTargetImprecise()
{
	m_robot->goToDirect(Pose(Point(5, 4), Angle::getQuarterRotation()));
	m_hardwareRobot->setPose(Pose(Point(0, 4), Angle()));

	m_robot->update();

	Compare compare(0.0001);
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToGoToPositionPrecise());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_hardwareRobot->getCallsToGoToPositionImprecise());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(5, 4), m_hardwareRobot->getLastPointToDriveTo()));
}

void RobotTest::update_goToDirectAndPositionNotReached_robotGotNoCallToTurnTowardsTarget()
{
	m_robot->goToDirect(Pose(Point(5, 4), Angle::getQuarterRotation()));
	m_hardwareRobot->setPose(Pose(Point(0, 4), Angle()));

	m_robot->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_hardwareRobot->getCallsToTurn());
}

void RobotTest::update_goToDirectAndPositionNotReachedTwiceCalled_robotGotNoAdditionalCallToDriveToTargetImprecise()
{
	m_robot->goToDirect(Pose(Point(5, 4), Angle::getQuarterRotation()));
	m_hardwareRobot->setPose(Pose(Point(0, 4), Angle()));

	m_robot->update();
	m_robot->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToGoToPositionPrecise());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_hardwareRobot->getCallsToGoToPositionImprecise());
}

void RobotTest::update_goToDirectAndPositionNotreachedButMovementStopped_robotGotCallToTurnTo()
{
	m_robot->goToDirect(Pose(Point(5, 4), Angle::getQuarterRotation()));
	m_hardwareRobot->setPose(Pose(Point(0, 4), Angle()));
	m_robot->update();
	m_hardwareRobot->setIsMoving(true);
	m_robot->update();
	m_hardwareRobot->setIsMoving(false);
	m_robot->update();

	Compare compare(0.00001);
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToGoToPositionPrecise());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_hardwareRobot->getCallsToGoToPositionImprecise());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToTurn());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getQuarterRotation(), m_hardwareRobot->getLastAngleToTurnTo()));
}

void RobotTest::update_goToDirectAndFinalRotationNotReached_robotGotCallToTurn()
{
	m_robot->goToDirect(Pose(Point(5, 4), Angle::getQuarterRotation()));
	m_hardwareRobot->setPose(Pose(Point(5, 4), Angle()));

	m_robot->update();

	Compare compare(0.0001);
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToTurn());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getQuarterRotation(), m_hardwareRobot->getLastAngleToTurnTo()));
}

void RobotTest::update_goToDirectAndFinalRotationNotReached_robotGotNoCallToDrive()
{
	m_robot->goToDirect(Pose(Point(5, 4), Angle::getQuarterRotation()));
	m_hardwareRobot->setPose(Pose(Point(5, 4), Angle()));

	m_robot->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_hardwareRobot->getCallsToGoToPositionPrecise());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_hardwareRobot->getCallsToGoToPositionImprecise());
}

void RobotTest::update_goToDirectAndFinalRotationNotReachedTwiceCalled_robotGotNoAdditionalCallToTurn()
{
	m_robot->goToDirect(Pose(Point(5, 4), Angle::getQuarterRotation()));
	m_hardwareRobot->setPose(Pose(Point(5, 4), Angle()));

	m_robot->update();
	m_robot->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToTurn());
}

void RobotTest::update_goToDirectAndInitialRotationReachedButRobotStillMoving_robotGotNoAdditionalCallsToMove()
{
	m_robot->goToDirect(Pose(Point(5, 4), Angle::getQuarterRotation()));
	m_hardwareRobot->setPose(Pose(Point(1, 2), Angle()));

	m_robot->update();
	m_robot->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_hardwareRobot->getCallsToGoToPositionPrecise());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_hardwareRobot->getCallsToGoToPositionImprecise());
}

void RobotTest::update_goToDirectAndPositionReachedButRobotStillMoving_robotGotNoAdditionalCallsToMove()
{
	m_robot->goToDirect(Pose(Point(5, 4), Angle::getQuarterRotation()));
	m_hardwareRobot->setPose(Pose(Point(0, 4), Angle()));

	m_robot->update();
	m_robot->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_hardwareRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToGoToPositionPrecise());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_hardwareRobot->getCallsToGoToPositionImprecise());
}

void RobotTest::update_goToDirectAndFinalRotationReachedButRobotStillMoving_robotGotNoAdditionalCallsToMove()
{
	m_robot->goToDirect(Pose(Point(5, 4), Angle::getQuarterRotation()));
	m_hardwareRobot->setPose(Pose(Point(5, 4), Angle()));

	m_robot->update();
	m_robot->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_hardwareRobot->getCallsToGoToPositionPrecise());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_hardwareRobot->getCallsToGoToPositionImprecise());
}

void RobotTest::update_goToDirectAndInitalRotationReachedAndMovementStopped_robotGotCallToMove()
{
	m_robot->goToDirect(Pose(Point(5, 4), Angle::getQuarterRotation()));
	m_hardwareRobot->setPose(Pose(Point(0, 0), Angle()));
	m_robot->update();
	m_hardwareRobot->setIsMoving(true);
	m_robot->update();
	m_hardwareRobot->setPose(Pose(Point(0, 4), Angle()));
	m_hardwareRobot->setIsMoving(false);

	m_robot->update();

	Compare compare(0.0001);
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToGoToPositionPrecise());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_hardwareRobot->getCallsToGoToPositionImprecise());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(5, 4), m_hardwareRobot->getLastPointToDriveTo()));
}

void RobotTest::update_goToDirectAndPositionReachedAndMovementStopped_robotGotCallToTurn()
{
	m_robot->goToDirect(Pose(Point(5, 4), Angle::getQuarterRotation()));
	m_hardwareRobot->setPose(Pose(Point(0, 4), Angle()));
	m_robot->update();
	m_hardwareRobot->setIsMoving(true);
	m_robot->update();
	m_hardwareRobot->setPose(Pose(Point(5, 4), Angle()));
	m_hardwareRobot->setIsMoving(false);

	m_robot->update();

	Compare compare(0.0001);
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToGoToPositionPrecise());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_hardwareRobot->getCallsToGoToPositionImprecise());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getQuarterRotation(), m_hardwareRobot->getLastAngleToTurnTo()));
}

void RobotTest::update_goToAndinitialRotationNotReached_robotGotCallToTurnTowardsTarget()
{
	m_hardwareRobot->setPose(Pose(Point(1, 2), Angle()));
	m_robot->goTo(Pose(Point(5, 4), Angle::getQuarterRotation()), false, false, false);

	m_robot->update();

	Compare compare(0.0001);
	Angle targetShouldBe(Point(1, 2), Point(5, 4));
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToTurn());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(targetShouldBe, m_hardwareRobot->getLastAngleToTurnTo()));
}

void RobotTest::update_goToAndinitialRotationNotReached_robotGotNoCallToDrive()
{
	m_hardwareRobot->setPose(Pose(Point(1, 2), Angle()));
	m_robot->goTo(Pose(Point(5, 4), Angle::getQuarterRotation()), false, false, false);

	m_robot->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_hardwareRobot->getCallsToGoToPositionPrecise());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_hardwareRobot->getCallsToGoToPositionImprecise());
}

void RobotTest::update_goToAndinitialRotationNotReachedTwiceCalled_robotGotNoAdditionalCallToTurn()
{
	m_hardwareRobot->setPose(Pose(Point(1, 2), Angle()));
	m_robot->goTo(Pose(Point(5, 4), Angle::getQuarterRotation()), false, false, false);

	m_robot->update();
	m_robot->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToTurn());
}

void RobotTest::update_goToAndinitialRotationNotReachedButMovementStopped_robotGotGallToDriveToTargetImprecise()
{
	m_hardwareRobot->setPose(Pose(Point(1, 2), Angle()));
	m_robot->goTo(Pose(Point(5, 4), Angle::getQuarterRotation()), false, false, false);

	m_robot->update();
	m_robot->update();
	m_hardwareRobot->setIsMoving(true);
	m_robot->update();
	m_hardwareRobot->setIsMoving(false);
	m_robot->update();

	Compare compare(0.00001);
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(5, 4), m_hardwareRobot->getLastPointToDriveTo()));
}

void RobotTest::update_goToAndpositionNotReached_robotGotCallToDriveToTargetImprecise()
{
	m_hardwareRobot->setPose(Pose(Point(0, 4), Angle()));
	m_robot->goTo(Pose(Point(5, 4), Angle::getQuarterRotation()), false, false, false);

	m_robot->update();

	Compare compare(0.0001);
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(5, 4), m_hardwareRobot->getLastPointToDriveTo()));
}

void RobotTest::update_goToAndpositionNotReached_robotGotNoCallToTurnTowardsTarget()
{
	m_hardwareRobot->setPose(Pose(Point(0, 4), Angle()));
	m_robot->goTo(Pose(Point(5, 4), Angle::getQuarterRotation()), false, false, false);

	m_robot->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_hardwareRobot->getCallsToTurn());
}

void RobotTest::update_goToAndpositionNotReachedTwiceCalled_robotGotNoAdditionalCallToDriveToTargetImprecise()
{
	m_hardwareRobot->setPose(Pose(Point(0, 4), Angle()));
	m_robot->goTo(Pose(Point(5, 4), Angle::getQuarterRotation()), false, false, false);

	m_robot->update();
	m_robot->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToGoToCombined());
}

void RobotTest::update_goToAndpositionNotreachedButMovementStopped_robotGotCallToTurnTo()
{
	m_hardwareRobot->setPose(Pose(Point(0, 4), Angle()));
	m_robot->goTo(Pose(Point(5, 4), Angle::getQuarterRotation()), false, false, false);

	m_robot->update();
	m_robot->update();
	m_hardwareRobot->setIsMoving(true);
	m_robot->update();
	m_hardwareRobot->setIsMoving(false);
	m_robot->update();

	Compare compare(0.00001);
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToTurn());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getQuarterRotation(), m_hardwareRobot->getLastAngleToTurnTo()));
}

void RobotTest::update_goToAndfinalRotationNotReached_robotGotCallToTurn()
{
	m_hardwareRobot->setPose(Pose(Point(5, 4), Angle()));
	m_robot->goTo(Pose(Point(5, 4), Angle::getQuarterRotation()), false, false, false);

	m_robot->update();

	Compare compare(0.0001);
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToTurn());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getQuarterRotation(), m_hardwareRobot->getLastAngleToTurnTo()));
}

void RobotTest::update_goToAndfinalRotationNotReached_robotGotNoCallToDrive()
{
	m_hardwareRobot->setPose(Pose(Point(5, 4), Angle()));
	m_robot->goTo(Pose(Point(5, 4), Angle::getQuarterRotation()), false, false, false);

	m_robot->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_hardwareRobot->getCallsToGoToCombined());
}

void RobotTest::update_goToAndfinalRotationNotReachedTwiceCalled_robotGotNoAdditionalCallToTurn()
{
	m_hardwareRobot->setPose(Pose(Point(5, 4), Angle()));
	m_robot->goTo(Pose(Point(5, 4), Angle::getQuarterRotation()), false, false, false);

	m_robot->update();
	m_robot->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToTurn());
}

void RobotTest::update_goToAndfinalRotationNotReachedButMovementStopped_reachedTarget()
{
	m_hardwareRobot->setPose(Pose(Point(5, 4), Angle()));
	m_robot->goTo(Pose(Point(5, 4), Angle::getQuarterRotation()), false, false, false);

	m_robot->update();
	m_robot->update();
	m_hardwareRobot->setIsMoving(true);
	m_robot->update();
	m_hardwareRobot->setIsMoving(false);
	m_robot->update();

	CPPUNIT_ASSERT(m_robot->reachedTarget());
}

void RobotTest::update_goToAndinitialRotationReachedButRobotStillMoving_robotGotNoAdditionalCallsToMove()
{
	m_hardwareRobot->setPose(Pose(Point(1, 2), Angle()));
	m_robot->goTo(Pose(Point(5, 4), Angle::getQuarterRotation()), false, false, false);

	m_robot->update();
	m_robot->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_hardwareRobot->getCallsToGoToCombined());
}

void RobotTest::update_goToAndpositionReachedButRobotStillMoving_robotGotNoAdditionalCallsToMove()
{
	m_hardwareRobot->setPose(Pose(Point(0, 4), Angle()));
	m_robot->goTo(Pose(Point(5, 4), Angle::getQuarterRotation()), false, false, false);

	m_robot->update();
	m_robot->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_hardwareRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToGoToCombined());
}

void RobotTest::update_goToAndfinalRotationReachedButRobotStillMoving_robotGotNoAdditionalCallsToMove()
{
	m_hardwareRobot->setPose(Pose(Point(5, 4), Angle()));
	m_robot->goTo(Pose(Point(5, 4), Angle::getQuarterRotation()), false, false, false);

	m_robot->update();
	m_robot->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_hardwareRobot->getCallsToGoToCombined());
}

void RobotTest::update_goToAndinitalRotationReachedAndMovementStopped_robotGotCallToMove()
{
	m_hardwareRobot->setPose(Pose(Point(0, 0), Angle()));
	m_robot->goTo(Pose(Point(5, 4), Angle::getQuarterRotation()), false, false, false);
	m_robot->update();
	m_robot->update();
	m_hardwareRobot->setPose(Pose(Point(0, 4), Angle()));

	m_hardwareRobot->setIsMoving(true);
	m_robot->update();
	m_hardwareRobot->setIsMoving(false);
	m_robot->update();

	Compare compare(0.0001);
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(5, 4), m_hardwareRobot->getLastPointToDriveTo()));
}

void RobotTest::update_goToAndpositionReachedAndMovementStopped_robotGotCallToTurn()
{
	m_hardwareRobot->setPose(Pose(Point(0, 4), Angle()));
	m_robot->goTo(Pose(Point(5, 4), Angle::getQuarterRotation()), false, false, false);
	m_robot->update();
	m_robot->update();
	m_hardwareRobot->setPose(Pose(Point(5, 4), Angle()));

	m_hardwareRobot->setIsMoving(true);
	m_robot->update();
	m_hardwareRobot->setIsMoving(false);
	m_robot->update();

	Compare compare(0.0001);
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getQuarterRotation(), m_hardwareRobot->getLastAngleToTurnTo()));
}

void RobotTest::update_goToAndinitialRotationReachedAndThreePointsInRouteAndMovementStoppedByRobot_robotGotCallToMoveToSecondPoint()
{
	m_hardwareRobot->setPose(Pose(Point(0, 0), Angle::getEighthRotation()));
	m_robot->goTo(Pose(Point(5, 4), Angle::getQuarterRotation()), false, false, false);
	m_routerMock->setChessMode(true);
	m_robot->update();
	m_robot->update();
	m_hardwareRobot->setIsMoving(true);
	m_robot->update();
	m_hardwareRobot->setIsMoving(false);
	m_robot->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT_EQUAL(Point(0,4),m_hardwareRobot->getLastPointToDriveTo());
}

void RobotTest::update_goToAndsecondPositionReachedAndRotationNotReachedAndAllIntermediateMovementsStoppedByRobot_turningToThirdPoint()
{
	m_hardwareRobot->setPose(Pose(Point(0, 0), Angle::getHalfRotation()));
	m_robot->goTo(Pose(Point(5, 4), Angle::getQuarterRotation()), false, false, false);
	m_routerMock->setChessMode(true);
	m_robot->update();
	m_robot->update();
	m_hardwareRobot->setIsMoving(true);
	m_robot->update();
	m_hardwareRobot->setIsMoving(false);
	m_robot->update();
	m_robot->update();
	m_hardwareRobot->setIsMoving(true);
	m_robot->update();
	m_hardwareRobot->setIsMoving(false);
	m_robot->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, m_hardwareRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT_EQUAL(Angle(Point(0,0),Point(5,4)),m_hardwareRobot->getLastAngleToTurnTo());
}

void RobotTest::update_goToAndsecondPositionReachedAndRotationReachedAndAllIntermediateMovementsStoppedByRobot_robotGotCallToMoveToThirdPoint()
{
	m_hardwareRobot->setPose(Pose(Point(0, 0), Angle::getEighthRotation()));
	m_robot->goTo(Pose(Point(5, 4), Angle::getQuarterRotation()), false, false, false);
	m_routerMock->setChessMode(true);
	m_robot->update();
	m_robot->update();
	m_hardwareRobot->setIsMoving(true);
	m_robot->update();
	m_hardwareRobot->setIsMoving(false);
	m_robot->update();
	m_robot->update();
	m_hardwareRobot->setIsMoving(true);
	m_robot->update();
	m_hardwareRobot->setIsMoving(false);
	m_robot->update();
	m_robot->update();
	m_hardwareRobot->setIsMoving(true);
	m_robot->update();
	m_hardwareRobot->setIsMoving(false);
	m_robot->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, m_hardwareRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL((unsigned int)2, m_hardwareRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT_EQUAL(Point(5,4),m_hardwareRobot->getLastPointToDriveTo());
}

void RobotTest::update_goToAndinitialRotationReachedAndRouteChanged_robotGotTwoCallsToTurn()
{
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(1,1),0.5));
	m_robot->goTo(Pose(Point(5, 4), Angle::getQuarterRotation()), false, false, false);

	m_hardwareRobot->setPose(Pose(Point(0, 0), Angle::getHalfRotation()));
	m_routerMock->setChessMode(false);
	m_robot->update();
	m_hardwareRobot->setPose(Pose(Point(0, 0), Angle(Point(0,0),Point(5,4))));
	m_robot->update();
	m_obstacleFetcher->setAllObstaclesButMeInRange(obstacles);
	m_routerMock->setChessMode(true);
	m_robot->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT_EQUAL((unsigned int)2, m_hardwareRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL(Angle::getQuarterRotation(),m_hardwareRobot->getLastAngleToTurnTo());
}

void RobotTest::update_goToAndinitialRotationReachedAndRouteChangedAndinitialRotationReachedAgain_robotGotTwoCallsToDrive()
{
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(1,1),0.5));
	m_robot->goTo(Pose(Point(5, 4), Angle::getQuarterRotation()), false, false, false);

	m_hardwareRobot->setPose(Pose(Point(0, 0), Angle::getHalfRotation()));
	m_routerMock->setChessMode(false);
	m_robot->update();
	m_hardwareRobot->setPose(Pose(Point(0, 0), Angle(Point(0,0),Point(5,4))));
	m_robot->update();
	m_obstacleFetcher->setAllObstaclesButMeInRange(obstacles);
	m_routerMock->setChessMode(true);
	m_robot->update();
	m_hardwareRobot->setPose(Pose(Point(0, 0), Angle::getQuarterRotation()));
	m_robot->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, m_hardwareRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT_EQUAL((unsigned int)2, m_hardwareRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL(Point(0,4),m_hardwareRobot->getLastPointToDriveTo());
}

void RobotTest::update_goToAndinitialRotationNotReachedAndObstacleMovedALittleBit_turningToSecondPoint()
{
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(1,1),0.5));
	m_robotWithRealRouter->goTo(Pose(Point(5, 4), Angle::getQuarterRotation()), false, false, false);

	m_obstacleFetcher->setAllObstaclesButMeInRange(obstacles);
	m_hardwareRobot->setPose(Pose(Point(0, 0), Angle::getHalfRotation()));
	m_robotWithRealRouter->update();
	obstacles.front().setDiameter(0.6);
	m_obstacleFetcher->setAllObstaclesButMeInRange(obstacles);
	m_robotWithRealRouter->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_hardwareRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToTurn());
}

void RobotTest::update_goToAndinitialRotationNotReachedAndObstacleMoved_turningToSecondPointOfNewRoute()
{
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(1,1),0.5));
	m_robotWithRealRouter->goTo(Pose(Point(5, 4), Angle::getQuarterRotation()), false, false, false);

	m_obstacleFetcher->setAllObstaclesButMeInRange(obstacles);
	m_hardwareRobot->setPose(Pose(Point(0, 0), Angle::getHalfRotation()));
	m_robotWithRealRouter->update();
	obstacles.front().setCenter(Point(2,1.5));
	m_obstacleFetcher->setAllObstaclesButMeInRange(obstacles);
	m_robotWithRealRouter->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_hardwareRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT_EQUAL((unsigned int)2, m_hardwareRobot->getCallsToTurn());
}

void RobotTest::update_goToAndignoreBall_routePointsCountIs2()
{
	vector<Circle> obstacles;
	m_robotWithRealRouter->goTo(Pose(Point(5, 4), Angle::getQuarterRotation()), true, false, false);
	m_obstacleFetcher->setAllObstaclesButMeAndBallInRange(obstacles);
	obstacles.push_back(Circle(Point(2.5,2),0.5));
	m_obstacleFetcher->setAllObstaclesButMeInRange(obstacles);

	m_hardwareRobot->setPose(Pose(Point(0, 0), Angle::getEighthRotation()));
	m_robotWithRealRouter->update();

	DriveTo const &state = dynamic_cast<DriveTo const&>(m_robotWithRealRouter->getCurrentState());
	CPPUNIT_ASSERT_EQUAL((size_t)2, state.getRoutePointsCount());
}

void RobotTest::update_goToAndcloseToThirdPositionAndDriveSlowlyAtTheEnd_robotGotCallToDriveSlowly()
{
	m_hardwareRobot->setPose(Pose(Point(0, 0), Angle(Point(0,0),Point(5,4))));
	m_robotWithRealRouter->goTo(Pose(Point(5, 4), Angle::getQuarterRotation()), false, true, false);
	m_robotWithRealRouter->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToGoToPositionImprecise());

	m_robotWithRealRouter->update();
	m_hardwareRobot->setIsMoving(true);
	m_robotWithRealRouter->update();
	m_hardwareRobot->setIsMoving(false);
	m_robotWithRealRouter->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToGoToPositionImprecise());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToGoToPositionPrecise());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_hardwareRobot->getCallsToTurn());
}

void RobotTest::update_goToAndtargetNotInsideField_noCallToDriveAndTurn()
{
	m_hardwareRobot->setPose(Pose(Point(0, 0), Angle::getEighthRotation()));
	m_robotWithRealRouter->goTo(Pose(Point(5, 4), Angle::getQuarterRotation()), false, false, false);
	m_field->setAllCoordinatesOutside(true);

	m_robotWithRealRouter->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_hardwareRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_hardwareRobot->getCallsToTurn());
}

void RobotTest::update_goToAndobstacleOnTargetAndIgnoreObstacle_robotGotCallToDrive()
{
	vector<Circle> obstacles;
	m_obstacleFetcher->setAllObstaclesButMeAndGoalObstaclesInRange(obstacles);
	m_robotWithRealRouter->goTo(Pose(Point(5, 4), Angle::getQuarterRotation()), false, false, true);

	obstacles.push_back(Circle(Point(5,4),0.2));
	m_obstacleFetcher->setAllObstaclesButMeInRange(obstacles);
	m_hardwareRobot->setPose(Pose(Point(0, 0), Angle::getEighthRotation()));
	m_robotWithRealRouter->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_hardwareRobot->getCallsToTurn());
}

void RobotTest::update_goToAndinitialRotationNotReachedAndThreePointsInRoute_turningToSecondPoint()
{
	m_hardwareRobot->setPose(Pose(Point(0, 0), Angle::getEighthRotation()));
	m_routerMock->setChessMode(true);
	m_robot->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL(Angle::getQuarterRotation(),m_hardwareRobot->getLastAngleToTurnTo());
}

void RobotTest::update_goToAndinitialRotationReachedAndThreePointsInRoute_robotGotCallToMoveToSecondPoint()
{
	m_hardwareRobot->setPose(Pose(Point(0, 0), Angle::getEighthRotation()));
	m_routerMock->setChessMode(true);
	m_robot->update();
	m_hardwareRobot->setPose(Pose(Point(0, 0), Angle::getQuarterRotation()));
	m_robot->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL(Point(0,4),m_hardwareRobot->getLastPointToDriveTo());
}

void RobotTest::update_goToAndsecondPositionReachedAndRotationNotReached_turningToThirdPoint()
{
	m_hardwareRobot->setPose(Pose(Point(0, 0), Angle::getEighthRotation()));
	m_routerMock->setChessMode(true);
	m_robot->update();
	m_hardwareRobot->setPose(Pose(Point(0, 0), Angle::getQuarterRotation()));
	m_robot->update();
	m_hardwareRobot->setPose(Pose(Point(0,4),Angle::getEighthRotation()));
	m_robot->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, m_hardwareRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT_EQUAL(Angle(),m_hardwareRobot->getLastAngleToTurnTo());
}

void RobotTest::update_goToAndsecondPositionReachedAndRotationReached_robotGotCallToMoveToThirdPoint()
{
	m_hardwareRobot->setPose(Pose(Point(0, 0), Angle::getEighthRotation()));
	m_routerMock->setChessMode(true);
	m_robot->update();
	m_hardwareRobot->setPose(Pose(Point(0, 0), Angle::getQuarterRotation()));
	m_robot->update();
	m_hardwareRobot->setPose(Pose(Point(0,4),Angle::getEighthRotation()));
	m_robot->update();
	m_hardwareRobot->setPose(Pose(Point(0,4),Angle()));
	m_robot->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, m_hardwareRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL((unsigned int)2, m_hardwareRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT_EQUAL(Point(5,4),m_hardwareRobot->getLastPointToDriveTo());
}

void RobotTest::update_goToAndthirdPositionReachedAndFinalRotationNotReached_turningToFinalRotation()
{
	m_hardwareRobot->setPose(Pose(Point(0, 0), Angle::getEighthRotation()));
	m_routerMock->setChessMode(true);
	m_robot->update();
	m_hardwareRobot->setPose(Pose(Point(0, 0), Angle::getQuarterRotation()));
	m_robot->update();
	m_hardwareRobot->setPose(Pose(Point(0,4),Angle::getEighthRotation()));
	m_robot->update();
	m_hardwareRobot->setPose(Pose(Point(0,4),Angle()));
	m_robot->update();
	m_hardwareRobot->setPose(Pose(Point(5, 4), Angle::getEighthRotation()));
	m_robot->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)3, m_hardwareRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL((unsigned int)2, m_hardwareRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT_EQUAL(Angle::getQuarterRotation(),m_hardwareRobot->getLastAngleToTurnTo());
}

void RobotTest::update_kickAndTurnToReachedTarget_oneCallToKick()
{
	m_hardwareRobot->setPose(Pose(Point(0, 0), Angle()));
	m_ball->setPosition(Point(0.2, 0));

	m_robot->kick(*m_ball);
	m_robot->update();
	m_robot->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToKick());
}

void RobotTest::update_empty_robotGotCallToUpdate()
{
	m_robot->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_hardwareRobot->getCallsToUpdate());
}

void RobotTest::getObstacle_empty_sameAsFromControllableRobot()
{
	m_hardwareRobot->setPose(Pose(Point(4, 3), Angle(3)));
	Circle obstacleShouldBe = m_hardwareRobot->getObstacle();

	Circle obstacle = m_robot->getObstacle();

	CPPUNIT_ASSERT_EQUAL(obstacleShouldBe, obstacle);
}

void RobotTest::getObstacles_empty_oneWhichIsSameAsFromControllableRobot()
{
	m_hardwareRobot->setPose(Pose(Point(4, 3), Angle(3)));
	Circle obstacleShouldBe = m_hardwareRobot->getObstacle();

	vector<Circle> obstacles = m_robot->getObstacles();

	CPPUNIT_ASSERT_EQUAL((size_t)1, obstacles.size());
	CPPUNIT_ASSERT_EQUAL(obstacleShouldBe, obstacles.front());
}
