#include "layer/autonomous/robottest.h"
#include "layer/autonomous/robotimpl.h"
#include "layer/autonomous/intelligentballmock.h"
#include "layer/autonomous/obstaclefetchermock.h"
#include "layer/abstraction/controllablerobotmock.h"
#include "common/time/watchmock.h"
#include "common/logging/loggermock.h"
#include "common/geometry/pose.h"
#include "common/geometry/compare.h"
#include "common/routing/routermock.h"

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
	m_router = new RouterMock();
	m_obstacleFetcher = new ObstacleFetcherMock();
	m_robot = new RobotImpl(*m_hardwareRobot, *m_router, *m_watch, *m_logger, 0, *m_obstacleFetcher);
	m_ball = new IntelligentBallMock();
}

void RobotTest::tearDown()
{
	delete m_robot;
	m_robot = 0;
	delete m_hardwareRobot;
	m_hardwareRobot = 0;
	delete m_router;
	m_router = 0;
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
	m_router->setInvalidRoute();

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
