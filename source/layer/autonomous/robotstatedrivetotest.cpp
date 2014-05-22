#include "layer/autonomous/robotstatedrivetotest.h"
#include "layer/autonomous/robotstatedriveto.h"
#include "layer/autonomous/robotstatereachedtarget.h"
#include "layer/abstraction/controllablerobotmock.h"
#include "common/time/watchmock.h"
#include "common/geometry/compare.h"
#include "common/logging/loggermock.h"
#include "layer/autonomous/obstaclefetchermock.h"
#include "layer/autonomous/robotmock.h"
#include "common/routing/routerimpl.h"
#include "layer/main/fieldpositioncheckerfieldplayer.h"
#include "layer/autonomous/robotstate.h"
#include "common/routing/routermock.h"
#include <vector>

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Layer::Main;
using namespace RoboSoccer::Common::Routing;
using namespace std;

void RobotStateDriveToTest::setUp()
{
	RobotStateTest::setUp();
	m_field = new FieldPositionCheckerFieldPlayer();
	m_routerImpl = new RouterImpl(Abstraction::ReadableRobot::getWidth(), *m_field);
	m_robotStateWithRouter = new RobotStateDriveTo(*m_controllableRobot, Pose(Point(5, 4), Angle::getQuarterRotation()),
												   *m_routerImpl, *m_watch, *m_logger, Logger::LogFileTypeAutonomousRobotGoalie,
												   *m_obstacleFetcher, *m_autonomousRobotMock);
}

void RobotStateDriveToTest::tearDown()
{
	RobotStateTest::tearDown();
	delete m_field;
	m_field = 0;
	delete m_routerImpl;
	m_routerImpl = 0;
	delete m_robotStateWithRouter;
	m_robotStateWithRouter = 0;
}

RobotState *RobotStateDriveToTest::createInstance()
{
	return new RobotStateDriveTo(*m_controllableRobot, Pose(Point(5, 4), Angle::getQuarterRotation()),*m_router,
								 *m_watch, *m_logger, Logger::LogFileTypeAutonomousRobotGoalie, *m_obstacleFetcher,
								 *m_autonomousRobotMock);
}

void RobotStateDriveToTest::nextState_targetNotReached_0()
{
	m_controllableRobot->setPose(Pose(Point(1, 2), Angle()));

	RobotState *state = m_robotState->nextState();

	CPPUNIT_ASSERT(state == 0);
}

void RobotStateDriveToTest::nextState_targetReached_reachedTargetState()
{
	m_controllableRobot->setPose(Pose(Point(5, 4), Angle::getQuarterRotation()));

	RobotState *state = m_robotState->nextState();

	RobotStateReachedTarget *stateCasted = dynamic_cast<RobotStateReachedTarget*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void RobotStateDriveToTest::nextState_longTimeWaited_reachedTargetState()
{
	m_controllableRobot->setPose(Pose(Point(1, 2), Angle()));
	m_watch->setTime(100);

	RobotState *state = m_robotState->nextState();

	RobotStateReachedTarget *stateCasted = dynamic_cast<RobotStateReachedTarget*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void RobotStateDriveToTest::update_initialRotationNotReached_robotGotCallToTurnTowardsTarget()
{
	m_controllableRobot->setPose(Pose(Point(1, 2), Angle()));

	m_robotState->update();

	Compare compare(0.0001);
	Angle targetShouldBe(Point(1, 2), Point(5, 4));
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(targetShouldBe, m_controllableRobot->getLastAngleToTurnTo()));
}

void RobotStateDriveToTest::update_initialRotationNotReached_robotGotNoCallToDrive()
{
	m_controllableRobot->setPose(Pose(Point(1, 2), Angle()));

	m_robotState->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToGoToPositionPrecise());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToGoToPositionImprecise());
}

void RobotStateDriveToTest::update_initialRotationNotReachedTwiceCalled_robotGotNoAdditionalCallToTurn()
{
	m_controllableRobot->setPose(Pose(Point(1, 2), Angle()));

	m_robotState->update();
	m_robotState->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
}

void RobotStateDriveToTest::update_initialRotationNotReachedButMovementStopped_robotGotGallToDriveToTargetImprecise()
{
	m_controllableRobot->setPose(Pose(Point(1, 2), Angle()));
	m_controllableRobot->setIsMoving(false);
	m_robotState->update();
	m_controllableRobot->setIsMoving(true);
	m_robotState->update();
	m_controllableRobot->setIsMoving(false);
	m_robotState->update();

	Compare compare(0.00001);
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(5, 4), m_controllableRobot->getLastPointToDriveTo()));
}

void RobotStateDriveToTest::update_positionNotReached_robotGotCallToDriveToTargetImprecise()
{
	m_controllableRobot->setPose(Pose(Point(0, 4), Angle()));

	m_robotState->update();

	Compare compare(0.0001);
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(5, 4), m_controllableRobot->getLastPointToDriveTo()));
}

void RobotStateDriveToTest::update_positionNotReached_robotGotNoCallToTurnTowardsTarget()
{
	m_controllableRobot->setPose(Pose(Point(0, 4), Angle()));

	m_robotState->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToTurn());
}

void RobotStateDriveToTest::update_positionNotReachedTwiceCalled_robotGotNoAdditionalCallToDriveToTargetImprecise()
{
	m_controllableRobot->setPose(Pose(Point(0, 4), Angle()));

	m_robotState->update();
	m_robotState->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToGoToCombined());
}

void RobotStateDriveToTest::update_positionNotreachedButMovementStopped_robotGotCallToTurnTo()
{
	m_controllableRobot->setPose(Pose(Point(0, 4), Angle()));
	m_controllableRobot->setIsMoving(false);
	m_robotState->update();
	m_controllableRobot->setIsMoving(true);
	m_robotState->update();
	m_controllableRobot->setIsMoving(false);
	m_robotState->update();

	Compare compare(0.00001);
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getQuarterRotation(), m_controllableRobot->getLastAngleToTurnTo()));
}

void RobotStateDriveToTest::update_finalRotationNotReached_robotGotCallToTurn()
{
	m_controllableRobot->setPose(Pose(Point(5, 4), Angle()));

	m_robotState->update();

	Compare compare(0.0001);
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getQuarterRotation(), m_controllableRobot->getLastAngleToTurnTo()));
}

void RobotStateDriveToTest::update_finalRotationNotReached_robotGotNoCallToDrive()
{
	m_controllableRobot->setPose(Pose(Point(5, 4), Angle()));

	m_robotState->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToGoToCombined());
}

void RobotStateDriveToTest::update_finalRotationNotReachedTwiceCalled_robotGotNoAdditionalCallToTurn()
{
	m_controllableRobot->setPose(Pose(Point(5, 4), Angle()));

	m_robotState->update();
	m_robotState->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
}

void RobotStateDriveToTest::update_finalRotationNotReachedButMovementStopped_nextStateWouldBeReachedTarget()
{
	m_controllableRobot->setPose(Pose(Point(5, 4), Angle()));
	m_controllableRobot->setIsMoving(false);
	m_robotState->update();
	m_controllableRobot->setIsMoving(true);
	m_robotState->update();
	m_controllableRobot->setIsMoving(false);
	m_robotState->update();

	RobotState *state = m_robotState->nextState();

	RobotStateReachedTarget *stateCasted = dynamic_cast<RobotStateReachedTarget*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void RobotStateDriveToTest::update_initialRotationReachedButRobotStillMoving_robotGotNoAdditionalCallsToMove()
{
	m_controllableRobot->setPose(Pose(Point(1, 2), Angle()));

	m_robotState->update();
	m_controllableRobot->setIsMoving(true);
	m_robotState->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToGoToCombined());
}

void RobotStateDriveToTest::update_positionReachedButRobotStillMoving_robotGotNoAdditionalCallsToMove()
{
	m_controllableRobot->setPose(Pose(Point(0, 4), Angle()));

	m_robotState->update();
	m_controllableRobot->setIsMoving(true);
	m_robotState->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToGoToCombined());
}

void RobotStateDriveToTest::update_finalRotationReachedButRobotStillMoving_robotGotNoAdditionalCallsToMove()
{
	m_controllableRobot->setPose(Pose(Point(5, 4), Angle()));

	m_robotState->update();
	m_controllableRobot->setIsMoving(true);
	m_robotState->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL((unsigned int)0, m_controllableRobot->getCallsToGoToCombined());
}

void RobotStateDriveToTest::update_initalRotationReachedAndMovementStopped_robotGotCallToMove()
{
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle()));
	m_robotState->update();
	m_controllableRobot->setIsMoving(true);
	m_robotState->update();
	m_controllableRobot->setIsMoving(false);
	m_controllableRobot->setPose(Pose(Point(0, 4), Angle()));

	m_robotState->update();

	Compare compare(0.0001);
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(5, 4), m_controllableRobot->getLastPointToDriveTo()));
}

void RobotStateDriveToTest::update_positionReachedAndMovementStopped_robotGotCallToTurn()
{
	m_controllableRobot->setPose(Pose(Point(0, 4), Angle()));
	m_robotState->update();
	m_controllableRobot->setIsMoving(true);
	m_robotState->update();
	m_controllableRobot->setIsMoving(false);
	m_controllableRobot->setPose(Pose(Point(5, 4), Angle()));

	m_robotState->update();

	Compare compare(0.0001);
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getQuarterRotation(), m_controllableRobot->getLastAngleToTurnTo()));
}

void RobotStateDriveToTest::isEquivalentToDriveTo_empty_false()
{
	CPPUNIT_ASSERT(!m_robotState->isEquivalentToDriveTo(Pose(Point(5, 4),Angle())));
}

void RobotStateDriveToTest::isEquivalentToDriveToDirect_sameTarget_true()
{
	CPPUNIT_ASSERT(m_robotState->isEquivalentToDriveTo(Pose(Point(5, 4), Angle::getQuarterRotation())));
}

void RobotStateDriveToTest::isEquivalentToDriveToDirect_differentTarget_false()
{
	CPPUNIT_ASSERT(!m_robotState->isEquivalentToDriveTo(Pose(Point(5, 1), Angle::getQuarterRotation())));
}

void RobotStateDriveToTest::reachedTarget_empty_false()
{
	CPPUNIT_ASSERT(!m_robotState->reachedTarget());
}

void RobotStateDriveToTest::cantReachTarget_empty_false()
{
	CPPUNIT_ASSERT(!m_robotState->cantReachTarget());
}

void RobotStateDriveToTest::update_initialRotationNotReachedAndThreePointsInRoute_turningToSecondPoint()
{
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getEighthRotation()));
	m_router->setChessMode(true);
	m_robotState->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL(Angle::getQuarterRotation(),m_controllableRobot->getLastAngleToTurnTo());
}

void RobotStateDriveToTest::update_initialRotationReachedAndThreePointsInRoute_robotGotCallToMoveToSecondPoint()
{
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getEighthRotation()));
	m_router->setChessMode(true);
	m_robotState->update();
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getQuarterRotation()));
	m_robotState->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL(Point(0,4),m_controllableRobot->getLastPointToDriveTo());
}

void RobotStateDriveToTest::update_secondPositionReachedAndRotationNotReached_turningToThirdPoint()
{
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getEighthRotation()));
	m_router->setChessMode(true);
	m_robotState->update();
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getQuarterRotation()));
	m_robotState->update();
	m_controllableRobot->setPose(Pose(Point(0,4),Angle::getEighthRotation()));
	m_robotState->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT_EQUAL(Angle(),m_controllableRobot->getLastAngleToTurnTo());
}

void RobotStateDriveToTest::update_secondPositionReachedAndRotationReached_robotGotCallToMoveToThirdPoint()
{
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getEighthRotation()));
	m_router->setChessMode(true);
	m_robotState->update();
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getQuarterRotation()));
	m_robotState->update();
	m_controllableRobot->setPose(Pose(Point(0,4),Angle::getEighthRotation()));
	m_robotState->update();
	m_controllableRobot->setPose(Pose(Point(0,4),Angle()));
	m_robotState->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL((unsigned int)2, m_controllableRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT_EQUAL(Point(5,4),m_controllableRobot->getLastPointToDriveTo());
}

void RobotStateDriveToTest::update_thirdPositionReachedAndFinalRotationNotReached_turningToFinalRotation()
{
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getEighthRotation()));
	m_router->setChessMode(true);
	m_robotState->update();
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getQuarterRotation()));
	m_robotState->update();
	m_controllableRobot->setPose(Pose(Point(0,4),Angle::getEighthRotation()));
	m_robotState->update();
	m_controllableRobot->setPose(Pose(Point(0,4),Angle()));
	m_robotState->update();
	m_controllableRobot->setPose(Pose(Point(5, 4), Angle::getEighthRotation()));
	m_robotState->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)3, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL((unsigned int)2, m_controllableRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT_EQUAL(Angle::getQuarterRotation(),m_controllableRobot->getLastAngleToTurnTo());
}

void RobotStateDriveToTest::nextState_thirdPositionReachedAndFinalRotationReached_reachedTargetState()
{
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getEighthRotation()));
	m_router->setChessMode(true);
	m_robotState->update();
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getQuarterRotation()));
	m_robotState->update();
	m_controllableRobot->setPose(Pose(Point(0,4),Angle::getEighthRotation()));
	m_robotState->update();
	m_controllableRobot->setPose(Pose(Point(0,4),Angle()));
	m_robotState->update();
	m_controllableRobot->setPose(Pose(Point(5, 4), Angle::getEighthRotation()));
	m_robotState->update();
	m_controllableRobot->setPose(Pose(Point(5, 4), Angle::getQuarterRotation()));
	m_robotState->update();

	RobotState *state = m_robotState->nextState();

	RobotStateReachedTarget *stateCasted = dynamic_cast<RobotStateReachedTarget*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void RobotStateDriveToTest::nextState_thirdPositionReachedAndFinalRotationReachedAndAllIntermediateMovementsStoppedByRobot_reachedTargetState()
{
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getEighthRotation()));
	m_router->setChessMode(true);
	m_robotState->update();
	m_controllableRobot->setIsMoving(true);
	m_robotState->update();
	m_controllableRobot->setIsMoving(false);
	m_robotState->update();
	m_controllableRobot->setIsMoving(true);
	m_robotState->update();
	m_controllableRobot->setIsMoving(false);
	m_robotState->update();
	m_controllableRobot->setIsMoving(true);
	m_robotState->update();
	m_controllableRobot->setIsMoving(false);
	m_robotState->update();
	m_controllableRobot->setIsMoving(true);
	m_robotState->update();
	m_controllableRobot->setIsMoving(false);
	m_robotState->update();
	m_controllableRobot->setIsMoving(true);
	m_robotState->update();
	m_controllableRobot->setIsMoving(false);
	m_robotState->update();

	RobotState *state = m_robotState->nextState();

	RobotStateReachedTarget *stateCasted = dynamic_cast<RobotStateReachedTarget*>(state);
	CPPUNIT_ASSERT(stateCasted != 0);
	delete state;
}

void RobotStateDriveToTest::update_initialRotationReachedAndThreePointsInRouteAndMovementStoppedByRobot_robotGotCallToMoveToSecondPoint()
{
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getEighthRotation()));
	m_router->setChessMode(true);
	m_robotState->update();
	m_controllableRobot->setIsMoving(true);
	m_robotState->update();
	m_controllableRobot->setIsMoving(false);
	m_robotState->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT_EQUAL(Point(0,4),m_controllableRobot->getLastPointToDriveTo());
}

void RobotStateDriveToTest::update_secondPositionReachedAndRotationNotReachedAndAllIntermediateMovementsStoppedByRobot_turningToThirdPoint()
{
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getHalfRotation()));
	m_router->setChessMode(true);
	m_robotState->update();
	m_controllableRobot->setIsMoving(true);
	m_robotState->update();
	m_controllableRobot->setIsMoving(false);
	m_robotState->update();
	m_controllableRobot->setIsMoving(true);
	m_robotState->update();
	m_controllableRobot->setIsMoving(false);
	m_robotState->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT_EQUAL(Angle(Point(0,0),Point(5,4)),m_controllableRobot->getLastAngleToTurnTo());
}

void RobotStateDriveToTest::update_secondPositionReachedAndRotationReachedAndAllIntermediateMovementsStoppedByRobot_robotGotCallToMoveToThirdPoint()
{
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getEighthRotation()));
	m_router->setChessMode(true);
	m_robotState->update();
	m_controllableRobot->setIsMoving(true);
	m_robotState->update();
	m_controllableRobot->setIsMoving(false);
	m_robotState->update();
	m_controllableRobot->setIsMoving(true);
	m_robotState->update();
	m_controllableRobot->setIsMoving(false);
	m_robotState->update();
	m_controllableRobot->setIsMoving(true);
	m_robotState->update();
	m_controllableRobot->setIsMoving(false);
	m_robotState->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL((unsigned int)2, m_controllableRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT_EQUAL(Point(5,4),m_controllableRobot->getLastPointToDriveTo());
}

void RobotStateDriveToTest::update_initialRotationReachedAndRouteChanged_robotGotTwoCallsToTurn()
{
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(1,1),0.5));

	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getHalfRotation()));
	m_router->setChessMode(false);
	m_robotState->update();
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle(Point(0,0),Point(5,4))));
	m_robotState->update();
	m_obstacleFetcher->setAllObstaclesButMeInRange(obstacles);
	m_router->setChessMode(true);
	m_robotState->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT_EQUAL((unsigned int)2, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL(Angle::getQuarterRotation(),m_controllableRobot->getLastAngleToTurnTo());
}

void RobotStateDriveToTest::update_initialRotationReachedAndRouteChangedAndinitialRotationReachedAgain_robotGotTwoCallsToDrive()
{
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(1,1),0.5));

	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getHalfRotation()));
	m_router->setChessMode(false);
	m_robotState->update();
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle(Point(0,0),Point(5,4))));
	m_robotState->update();
	m_obstacleFetcher->setAllObstaclesButMeInRange(obstacles);
	m_router->setChessMode(true);
	m_robotState->update();
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getQuarterRotation()));
	m_robotState->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, m_controllableRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT_EQUAL((unsigned int)2, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT_EQUAL(Point(0,4),m_controllableRobot->getLastPointToDriveTo());
}
