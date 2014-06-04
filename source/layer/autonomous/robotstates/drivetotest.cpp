#include "layer/autonomous/robotstates/drivetotest.h"
#include "layer/autonomous/robotstates/driveto.h"
#include "layer/autonomous/robotstates/reachedtarget.h"
#include "layer/abstraction/controllablerobotmock.h"
#include "common/time/watchmock.h"
#include "common/geometry/compare.h"
#include "common/logging/loggermock.h"
#include "layer/autonomous/obstaclefetchermock.h"
#include "layer/autonomous/robotmock.h"
#include "common/routing/routerimpl.h"
#include "common/routing/fieldpositioncheckermock.h"
#include "layer/autonomous/robotstates/robotstate.h"
#include "common/routing/routermock.h"
#include <vector>

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::Routing;
using namespace std;

void DriveToTest::setUp()
{
	RobotStateTest::setUp();
	m_field = new FieldPositionCheckerMock();
	m_routerImpl = new RouterImpl(Abstraction::ReadableRobot::getWidth(), *m_field);
	m_robotStateWithRouter = new DriveTo(*m_controllableRobot, Pose(Point(5, 4), Angle::getQuarterRotation()),
												   *m_routerImpl, *m_watch, *m_logger, Logger::LogFileTypeAutonomousRobotGoalie,
												   *m_obstacleFetcher, *m_autonomousRobotMock, false, false, false);
	m_robotStateWithRouterAndIgnoredBall =
			new DriveTo(*m_controllableRobot, Pose(Point(5, 4), Angle::getQuarterRotation()),	*m_routerImpl,
								  *m_watch, *m_logger, Logger::LogFileTypeAutonomousRobotGoalie, *m_obstacleFetcher,
								  *m_autonomousRobotMock, true, false, false);
	m_robotStateWithRouterAndDriveSlowlyAtTheEnd =
			new DriveTo(*m_controllableRobot, Pose(Point(5, 4), Angle::getQuarterRotation()),	*m_routerImpl,
								  *m_watch, *m_logger, Logger::LogFileTypeAutonomousRobotGoalie, *m_obstacleFetcher,
								  *m_autonomousRobotMock, false, true, false);
	m_robotStateWithRouterAndIgnoreGoalObstacles =
			new DriveTo(*m_controllableRobot, Pose(Point(5, 4), Angle::getQuarterRotation()),	*m_routerImpl,
								  *m_watch, *m_logger, Logger::LogFileTypeAutonomousRobotGoalie, *m_obstacleFetcher,
								  *m_autonomousRobotMock, false, false, true);
}

void DriveToTest::tearDown()
{
	RobotStateTest::tearDown();
	delete m_field;
	m_field = 0;
	delete m_routerImpl;
	m_routerImpl = 0;
	delete m_robotStateWithRouter;
	m_robotStateWithRouter = 0;
	delete m_robotStateWithRouterAndIgnoredBall;
	m_robotStateWithRouterAndIgnoredBall = 0;
	delete m_robotStateWithRouterAndDriveSlowlyAtTheEnd;
	m_robotStateWithRouterAndDriveSlowlyAtTheEnd = 0;
	delete m_robotStateWithRouterAndIgnoreGoalObstacles;
	m_robotStateWithRouterAndIgnoreGoalObstacles = 0;
}

RobotState *DriveToTest::createInstance()
{
	return new DriveTo(*m_controllableRobot, Pose(Point(5, 4), Angle::getQuarterRotation()),*m_router,
								 *m_watch, *m_logger, Logger::LogFileTypeAutonomousRobotGoalie, *m_obstacleFetcher,
								 *m_autonomousRobotMock, false, false, false);
}

void DriveToTest::nextState_targetNotReached_0()
{
	m_controllableRobot->setPose(Pose(Point(1, 2), Angle()));

	RobotState *state = m_robotState->nextState(false);

	CPPUNIT_ASSERT(state == 0);
}

void DriveToTest::nextState_targetReached_reachedTargetState()
{
	m_controllableRobot->setPose(Pose(Point(5, 4), Angle::getQuarterRotation()));

	RobotState *state = m_robotState->nextState(false);

	ReachedTarget *stateCasted = dynamic_cast<ReachedTarget*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void DriveToTest::nextState_longTimeWaited_reachedTargetState()
{
	m_controllableRobot->setPose(Pose(Point(1, 2), Angle()));
	m_watch->setTime(100);

	RobotState *state = m_robotState->nextState(false);

	ReachedTarget *stateCasted = dynamic_cast<ReachedTarget*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void DriveToTest::update_initialRotationNotReached_robotGotCallToTurnTowardsTarget()
{
	m_controllableRobot->setPose(Pose(Point(1, 2), Angle()));

	m_robotState->update(false);

	Compare compare(0.0001);
	Angle targetShouldBe(Point(1, 2), Point(5, 4));
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(targetShouldBe, m_controllableRobot->getLastAngleToTurnTo()));
}

void DriveToTest::update_initialRotationNotReached_robotGotNoCallToDrive()
{
	m_controllableRobot->setPose(Pose(Point(1, 2), Angle()));

	m_robotState->update(false);

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToGoToPositionPrecise());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToGoToPositionImprecise());
}

void DriveToTest::update_initialRotationNotReachedTwiceCalled_robotGotNoAdditionalCallToTurn()
{
	m_controllableRobot->setPose(Pose(Point(1, 2), Angle()));

	m_robotState->update(false);
	m_robotState->update(false);

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
}

void DriveToTest::update_initialRotationNotReachedButMovementStopped_robotGotGallToDriveToTargetImprecise()
{
	m_controllableRobot->setPose(Pose(Point(1, 2), Angle()));
	m_robotState->update(false);
	m_robotState->update(false);
	m_robotState->update(true);

	Compare compare(0.00001);
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(5, 4), m_controllableRobot->getLastPointToDriveTo()));
}

void DriveToTest::update_positionNotReached_robotGotCallToDriveToTargetImprecise()
{
	m_controllableRobot->setPose(Pose(Point(0, 4), Angle()));

	m_robotState->update(false);

	Compare compare(0.0001);
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(5, 4), m_controllableRobot->getLastPointToDriveTo()));
}

void DriveToTest::update_positionNotReached_robotGotNoCallToTurnTowardsTarget()
{
	m_controllableRobot->setPose(Pose(Point(0, 4), Angle()));

	m_robotState->update(false);

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToTurn());
}

void DriveToTest::update_positionNotReachedTwiceCalled_robotGotNoAdditionalCallToDriveToTargetImprecise()
{
	m_controllableRobot->setPose(Pose(Point(0, 4), Angle()));

	m_robotState->update(false);
	m_robotState->update(false);

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToGoToCombined());
}

void DriveToTest::update_positionNotreachedButMovementStopped_robotGotCallToTurnTo()
{
	m_controllableRobot->setPose(Pose(Point(0, 4), Angle()));
	m_robotState->update(false);
	m_robotState->update(false);
	m_robotState->update(true);

	Compare compare(0.00001);
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getQuarterRotation(), m_controllableRobot->getLastAngleToTurnTo()));
}

void DriveToTest::update_finalRotationNotReached_robotGotCallToTurn()
{
	m_controllableRobot->setPose(Pose(Point(5, 4), Angle()));

	m_robotState->update(false);

	Compare compare(0.0001);
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getQuarterRotation(), m_controllableRobot->getLastAngleToTurnTo()));
}

void DriveToTest::update_finalRotationNotReached_robotGotNoCallToDrive()
{
	m_controllableRobot->setPose(Pose(Point(5, 4), Angle()));

	m_robotState->update(false);

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToGoToCombined());
}

void DriveToTest::update_finalRotationNotReachedTwiceCalled_robotGotNoAdditionalCallToTurn()
{
	m_controllableRobot->setPose(Pose(Point(5, 4), Angle()));

	m_robotState->update(false);
	m_robotState->update(false);

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
}

void DriveToTest::update_finalRotationNotReachedButMovementStopped_nextStateWouldBeReachedTarget()
{
	m_controllableRobot->setPose(Pose(Point(5, 4), Angle()));
	m_robotState->update(false);
	m_robotState->update(false);
	m_robotState->update(true);

	RobotState *state = m_robotState->nextState(true);

	ReachedTarget *stateCasted = dynamic_cast<ReachedTarget*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void DriveToTest::update_initialRotationReachedButRobotStillMoving_robotGotNoAdditionalCallsToMove()
{
	m_controllableRobot->setPose(Pose(Point(1, 2), Angle()));

	m_robotState->update(false);
	m_robotState->update(false);

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToGoToCombined());
}

void DriveToTest::update_positionReachedButRobotStillMoving_robotGotNoAdditionalCallsToMove()
{
	m_controllableRobot->setPose(Pose(Point(0, 4), Angle()));

	m_robotState->update(false);
	m_robotState->update(false);

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToGoToCombined());
}

void DriveToTest::update_finalRotationReachedButRobotStillMoving_robotGotNoAdditionalCallsToMove()
{
	m_controllableRobot->setPose(Pose(Point(5, 4), Angle()));

	m_robotState->update(false);
	m_robotState->update(false);

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToGoToCombined());
}

void DriveToTest::update_initalRotationReachedAndMovementStopped_robotGotCallToMove()
{
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle()));
	m_robotState->update(false);
	m_robotState->update(false);
	m_controllableRobot->setPose(Pose(Point(0, 4), Angle()));

	m_robotState->update(true);

	Compare compare(0.0001);
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(5, 4), m_controllableRobot->getLastPointToDriveTo()));
}

void DriveToTest::update_positionReachedAndMovementStopped_robotGotCallToTurn()
{
	m_controllableRobot->setPose(Pose(Point(0, 4), Angle()));
	m_robotState->update(false);
	m_robotState->update(false);
	m_controllableRobot->setPose(Pose(Point(5, 4), Angle()));

	m_robotState->update(true);

	Compare compare(0.0001);
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getQuarterRotation(), m_controllableRobot->getLastAngleToTurnTo()));
}

void DriveToTest::isEquivalentToDriveTo_empty_false()
{
	CPPUNIT_ASSERT(!m_robotState->isEquivalentToDriveTo(Pose(Point(5, 4),Angle())));
}

void DriveToTest::isEquivalentToDriveToDirect_sameTarget_true()
{
	CPPUNIT_ASSERT(m_robotState->isEquivalentToDriveTo(Pose(Point(5, 4), Angle::getQuarterRotation())));
}

void DriveToTest::isEquivalentToDriveToDirect_differentTarget_false()
{
	CPPUNIT_ASSERT(!m_robotState->isEquivalentToDriveTo(Pose(Point(5, 1), Angle::getQuarterRotation())));
}

void DriveToTest::reachedTarget_empty_false()
{
	CPPUNIT_ASSERT(!m_robotState->reachedTarget());
}

void DriveToTest::cantReachTarget_empty_false()
{
	CPPUNIT_ASSERT(!m_robotState->cantReachTarget());
}

void DriveToTest::update_initialRotationNotReachedAndThreePointsInRoute_turningToSecondPoint()
{
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getEighthRotation()));
	m_router->setChessMode(true);
	m_robotState->update(false);

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL(Angle::getQuarterRotation(),m_controllableRobot->getLastAngleToTurnTo());
}

void DriveToTest::update_initialRotationReachedAndThreePointsInRoute_robotGotCallToMoveToSecondPoint()
{
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getEighthRotation()));
	m_router->setChessMode(true);
	m_robotState->update(false);
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getQuarterRotation()));
	m_robotState->update(false);

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL(Point(0,4),m_controllableRobot->getLastPointToDriveTo());
}

void DriveToTest::update_secondPositionReachedAndRotationNotReached_turningToThirdPoint()
{
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getEighthRotation()));
	m_router->setChessMode(true);
	m_robotState->update(false);
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getQuarterRotation()));
	m_robotState->update(false);
	m_controllableRobot->setPose(Pose(Point(0,4),Angle::getEighthRotation()));
	m_robotState->update(false);

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT_EQUAL(Angle(),m_controllableRobot->getLastAngleToTurnTo());
}

void DriveToTest::update_secondPositionReachedAndRotationReached_robotGotCallToMoveToThirdPoint()
{
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getEighthRotation()));
	m_router->setChessMode(true);
	m_robotState->update(false);
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getQuarterRotation()));
	m_robotState->update(false);
	m_controllableRobot->setPose(Pose(Point(0,4),Angle::getEighthRotation()));
	m_robotState->update(false);
	m_controllableRobot->setPose(Pose(Point(0,4),Angle()));
	m_robotState->update(false);

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL((unsigned int)2, m_controllableRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT_EQUAL(Point(5,4),m_controllableRobot->getLastPointToDriveTo());
}

void DriveToTest::update_thirdPositionReachedAndFinalRotationNotReached_turningToFinalRotation()
{
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getEighthRotation()));
	m_router->setChessMode(true);
	m_robotState->update(false);
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getQuarterRotation()));
	m_robotState->update(false);
	m_controllableRobot->setPose(Pose(Point(0,4),Angle::getEighthRotation()));
	m_robotState->update(false);
	m_controllableRobot->setPose(Pose(Point(0,4),Angle()));
	m_robotState->update(false);
	m_controllableRobot->setPose(Pose(Point(5, 4), Angle::getEighthRotation()));
	m_robotState->update(false);

	CPPUNIT_ASSERT_EQUAL((unsigned int)3, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL((unsigned int)2, m_controllableRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT_EQUAL(Angle::getQuarterRotation(),m_controllableRobot->getLastAngleToTurnTo());
}

void DriveToTest::nextState_thirdPositionReachedAndFinalRotationReached_reachedTargetState()
{
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getEighthRotation()));
	m_router->setChessMode(true);
	m_robotState->update(false);
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getQuarterRotation()));
	m_robotState->update(false);
	m_controllableRobot->setPose(Pose(Point(0,4),Angle::getEighthRotation()));
	m_robotState->update(false);
	m_controllableRobot->setPose(Pose(Point(0,4),Angle()));
	m_robotState->update(false);
	m_controllableRobot->setPose(Pose(Point(5, 4), Angle::getEighthRotation()));
	m_robotState->update(false);
	m_controllableRobot->setPose(Pose(Point(5, 4), Angle::getQuarterRotation()));
	m_robotState->update(false);

	RobotState *state = m_robotState->nextState(false);

	ReachedTarget *stateCasted = dynamic_cast<ReachedTarget*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void DriveToTest::nextState_thirdPositionReachedAndFinalRotationReachedAndAllIntermediateMovementsStoppedByRobot_reachedTargetState()
{
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getEighthRotation()));
	m_router->setChessMode(true);
	m_robotState->update(false);
	m_robotState->update(false);
	m_robotState->update(true);
	m_robotState->update(false);
	m_robotState->update(true);
	m_robotState->update(false);
	m_robotState->update(true);
	m_robotState->update(false);
	m_robotState->update(true);
	m_robotState->update(false);
	m_robotState->update(true);

	RobotState *state = m_robotState->nextState(true);

	ReachedTarget *stateCasted = dynamic_cast<ReachedTarget*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void DriveToTest::update_initialRotationReachedAndThreePointsInRouteAndMovementStoppedByRobot_robotGotCallToMoveToSecondPoint()
{
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getEighthRotation()));
	m_router->setChessMode(true);
	m_robotState->update(false);
	m_robotState->update(false);
	m_robotState->update(true);

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT_EQUAL(Point(0,4),m_controllableRobot->getLastPointToDriveTo());
}

void DriveToTest::update_secondPositionReachedAndRotationNotReachedAndAllIntermediateMovementsStoppedByRobot_turningToThirdPoint()
{
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getHalfRotation()));
	m_router->setChessMode(true);
	m_robotState->update(false);
	m_robotState->update(false);
	m_robotState->update(true);
	m_robotState->update(false);
	m_robotState->update(true);

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT_EQUAL(Angle(Point(0,0),Point(5,4)),m_controllableRobot->getLastAngleToTurnTo());
}

void DriveToTest::update_secondPositionReachedAndRotationReachedAndAllIntermediateMovementsStoppedByRobot_robotGotCallToMoveToThirdPoint()
{
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getEighthRotation()));
	m_router->setChessMode(true);
	m_robotState->update(false);
	m_robotState->update(false);
	m_robotState->update(true);
	m_robotState->update(false);
	m_robotState->update(true);
	m_robotState->update(false);
	m_robotState->update(true);

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL((unsigned int)2, m_controllableRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT_EQUAL(Point(5,4),m_controllableRobot->getLastPointToDriveTo());
}

void DriveToTest::update_initialRotationReachedAndRouteChanged_robotGotTwoCallsToTurn()
{
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(1,1),0.5));

	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getHalfRotation()));
	m_router->setChessMode(false);
	m_robotState->update(false);
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle(Point(0,0),Point(5,4))));
	m_robotState->update(false);
	m_obstacleFetcher->setAllObstaclesButMeInRange(obstacles);
	m_router->setChessMode(true);
	m_robotState->update(false);

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT_EQUAL((unsigned int)2, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL(Angle::getQuarterRotation(),m_controllableRobot->getLastAngleToTurnTo());
}

void DriveToTest::update_initialRotationReachedAndRouteChangedAndinitialRotationReachedAgain_robotGotTwoCallsToDrive()
{
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(1,1),0.5));

	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getHalfRotation()));
	m_router->setChessMode(false);
	m_robotState->update(false);
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle(Point(0,0),Point(5,4))));
	m_robotState->update(false);
	m_obstacleFetcher->setAllObstaclesButMeInRange(obstacles);
	m_router->setChessMode(true);
	m_robotState->update(false);
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getQuarterRotation()));
	m_robotState->update(false);

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, m_controllableRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT_EQUAL((unsigned int)2, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL(Point(0,4),m_controllableRobot->getLastPointToDriveTo());
}

void DriveToTest::update_initialRotationNotReachedAndObstacleMovedALittleBit_turningToSecondPoint()
{
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(1,1),0.5));

	m_obstacleFetcher->setAllObstaclesButMeInRange(obstacles);
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getHalfRotation()));
	m_robotStateWithRouter->update(false);
	obstacles.front().setDiameter(0.6);
	m_obstacleFetcher->setAllObstaclesButMeInRange(obstacles);
	m_robotStateWithRouter->update(false);

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
}

void DriveToTest::update_initialRotationNotReachedAndObstacleMoved_turningToSecondPointOfNewRoute()
{
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(1,1),0.5));

	m_obstacleFetcher->setAllObstaclesButMeInRange(obstacles);
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getHalfRotation()));
	m_robotStateWithRouter->update(false);
	obstacles.front().setCenter(Point(2,1.5));
	m_obstacleFetcher->setAllObstaclesButMeInRange(obstacles);
	m_robotStateWithRouter->update(false);

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT_EQUAL((unsigned int)2, m_controllableRobot->getCallsToTurn());
}

void DriveToTest::update_ignoreBall_routePointsCountIs2()
{
	vector<Circle> obstacles;

	m_obstacleFetcher->setAllObstaclesButMeAndBallInRange(obstacles);

	obstacles.push_back(Circle(Point(2.5,2),0.5));
	m_obstacleFetcher->setAllObstaclesButMeInRange(obstacles);

	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getEighthRotation()));
	m_robotStateWithRouterAndIgnoredBall->update(false);

	CPPUNIT_ASSERT_EQUAL((size_t)2, m_robotStateWithRouterAndIgnoredBall->getRoutePointsCount());
}

void DriveToTest::update_closeToThirdPositionAndDriveSlowlyAtTheEnd_robotGotCallToDriveSlowly()
{
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle(Point(0,0),Point(5,4))));
	m_robotStateWithRouterAndDriveSlowlyAtTheEnd->update(false);

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToGoToPositionImprecise());

	m_robotStateWithRouterAndDriveSlowlyAtTheEnd->update(false);
	m_robotStateWithRouterAndDriveSlowlyAtTheEnd->update(true);

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToGoToPositionImprecise());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToGoToPositionPrecise());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToTurn());
}

void DriveToTest::update_targetNotInsideField_noCallToDriveAndTurn()
{
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getEighthRotation()));
	m_field->setAllCoordinatesOutside(true);
	m_robotStateWithRouter->update(false);

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToTurn());
}

void DriveToTest::update_obstacleOnTargetAndIgnoreObstacle_robotGotCallToDrive()
{
	vector<Circle> obstacles;

	m_obstacleFetcher->setAllObstaclesButMeAndGoalObstaclesInRange(obstacles);

	obstacles.push_back(Circle(Point(5,4),0.2));
	m_obstacleFetcher->setAllObstaclesButMeInRange(obstacles);
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getEighthRotation()));
	m_robotStateWithRouterAndIgnoreGoalObstacles->update(false);

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToTurn());
}
