#include "layer/autonomous/robotstates/drivetodrivingtest.h"
#include "layer/autonomous/robotstates/drivetodriving.h"
#include "layer/autonomous/robotstates/drivetoinvalidroute.h"
#include "layer/autonomous/robotstates/drivetoinitialrotation.h"
#include "layer/autonomous/robotstates/drivetofinalrotation.h"
#include "layer/autonomous/obstaclefetchermock.h"
#include "layer/autonomous/robotmock.h"
#include "layer/abstraction/controllablerobotmock.h"
#include "common/logging/loggermock.h"
#include "common/routing/routermock.h"
#include "common/geometry/compare.h"
#include "common/routing/routerimpl.h"
#include "common/routing/fieldpositioncheckermock.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::Routing;
using namespace std;

RobotState *DriveToDrivingTest::createInstance()
{
	vector<Pose> targets;
	targets.push_back(Pose(Point(5, 4), Angle::getQuarterRotation()));

	return new DriveToDriving(
				*m_controllableRobot, targets, targets.front(), *m_router, *m_logger, Logger::LogFileTypeAutonomousRobotGoalie,
				*m_obstacleFetcher,	*m_autonomousRobotMock, DriveModeDefault, *m_route);
}

void DriveToDrivingTest::constructor_routeWithThreePoints_routesHasThreePoints()
{
	Route route(1);
	route.addPoint(Point(0, 0));
	route.addPoint(Point(1, 0));
	route.addPoint(Point(1, 2));

	vector<Pose> targets;
	targets.push_back(Pose(Point(5, 4), Angle::getQuarterRotation()));

	DriveToDriving state(
					*m_controllableRobot, targets, targets.front(), *m_router, *m_logger, Logger::LogFileTypeAutonomousRobotGoalie,
					*m_obstacleFetcher,	*m_autonomousRobotMock, DriveModeDefault, route);

	CPPUNIT_ASSERT_EQUAL((size_t)3, state.getRoutePointsCount());
}

void DriveToDrivingTest::update_onceCalled_robotGotOneCallToGoToSecondPoint()
{
	m_robotState->update();

	Compare compare(0.00001);
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToGoToPositionImprecise());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(5, 4), m_controllableRobot->getLastPointToDriveTo()));
}

void DriveToDrivingTest::update_twiceCalled_robotGotOneCallToGoToSecondPoint()
{
	m_robotState->update();
	m_robotState->update();

	Compare compare(0.00001);
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToGoToPositionImprecise());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(5, 4), m_controllableRobot->getLastPointToDriveTo()));
}

void DriveToDrivingTest::nextState_routeBecomesInvalidAndNoNewOnePossible_invalidRoute()
{
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(3, 3), 1));
	m_obstacleFetcher->setAllObstaclesButMeInRangeDependentOnDriveMode(obstacles);
	m_router->setInvalidRoute();

	RobotState *nextState = m_robotState->nextState(false);

	DriveToInvalidRoute *nextStateCasted = dynamic_cast<DriveToInvalidRoute*>(nextState);
	CPPUNIT_ASSERT(nextStateCasted != 0);
	delete nextState;
}

void DriveToDrivingTest::nextState_routeBecomesInvalidAndNewOnePossible_initialRotation()
{
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(3, 3), 1));
	m_obstacleFetcher->setAllObstaclesButMeInRangeDependentOnDriveMode(obstacles);

	RobotState *nextState = m_robotState->nextState(false);

	DriveToInitialRotation *nextStateCasted = dynamic_cast<DriveToInitialRotation*>(nextState);
	CPPUNIT_ASSERT(nextStateCasted != 0);
	delete nextState;
}

void DriveToDrivingTest::nextState_targetNotReached_0()
{
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getHalfRotation()));

	RobotState *nextState = m_robotState->nextState(false);

	CPPUNIT_ASSERT(nextState == 0);
}

void DriveToDrivingTest::nextState_targetReachedAndNoPointsLeft_finalRotation()
{
	m_controllableRobot->setPose(Pose(Point(5, 4), Angle(0)));

	RobotState *nextState = m_robotState->nextState(false);

	DriveToFinalRotation *nextStateCasted = dynamic_cast<DriveToFinalRotation*>(nextState);
	CPPUNIT_ASSERT(nextStateCasted != 0);
	CPPUNIT_ASSERT_EQUAL((size_t)2, nextStateCasted->getRoutePointsCount());
	delete nextState;
}

void DriveToDrivingTest::nextState_movementStoppedAndNoPointsLeft_finalRotation()
{
	m_controllableRobot->setPose(Pose(Point(0, 2), Angle(0)));
	m_robotState->update();

	RobotState *nextState = m_robotState->nextState(true);

	DriveToFinalRotation *nextStateCasted = dynamic_cast<DriveToFinalRotation*>(nextState);
	CPPUNIT_ASSERT(nextStateCasted != 0);
	CPPUNIT_ASSERT_EQUAL((size_t)2, nextStateCasted->getRoutePointsCount());
	delete nextState;
}

void DriveToDrivingTest::nextState_targetReachedAndRoutePointsLeft_initialRotationWithShorterRoute()
{
	Route route(1);
	route.addPoint(Point(0, 0));
	route.addPoint(Point(5, 0));
	route.addPoint(Point(5, 4));

	vector<Pose> targets;
	targets.push_back(Pose(Point(5, 4), Angle::getQuarterRotation()));

	DriveToDriving state(
				*m_controllableRobot, targets, targets.front(), *m_router, *m_logger, Logger::LogFileTypeAutonomousRobotGoalie,
				*m_obstacleFetcher,	*m_autonomousRobotMock, DriveModeDefault, route);
	m_controllableRobot->setPose(Pose(Point(5, 0), Angle(0)));

	RobotState *nextState = state.nextState(false);

	DriveToInitialRotation *nextStateCasted = dynamic_cast<DriveToInitialRotation*>(nextState);
	CPPUNIT_ASSERT(nextStateCasted != 0);
	CPPUNIT_ASSERT_EQUAL((size_t)2, nextStateCasted->getRoutePointsCount());
	delete nextState;
}

void DriveToDrivingTest::nextState_movementStoppedAndRoutePointsLeft_initialRotationWithShorterRoute()
{
	Route route(1);
	route.addPoint(Point(0, 0));
	route.addPoint(Point(5, 0));
	route.addPoint(Point(5, 4));

	vector<Pose> targets;
	targets.push_back(Pose(Point(5, 4), Angle::getQuarterRotation()));

	DriveToDriving state(
				*m_controllableRobot, targets, targets.front(), *m_router, *m_logger, Logger::LogFileTypeAutonomousRobotGoalie,
				*m_obstacleFetcher,	*m_autonomousRobotMock, DriveModeDefault, route);
	m_controllableRobot->setPose(Pose(Point(1, 0), Angle(0)));
	state.update();

	RobotState *nextState = state.nextState(true);

	DriveToInitialRotation *nextStateCasted = dynamic_cast<DriveToInitialRotation*>(nextState);
	CPPUNIT_ASSERT(nextStateCasted != 0);
	CPPUNIT_ASSERT_EQUAL((size_t)2, nextStateCasted->getRoutePointsCount());
	delete nextState;
}

void DriveToDrivingTest::nextState_obstacleBehindRobotOccurs_0()
{
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(1, 1), 1));
	m_obstacleFetcher->setAllObstaclesButMeInRangeDependentOnDriveMode(obstacles);
	m_controllableRobot->setPose(Pose(Point(4, 3), Angle::getEighthRotation()));

	RobotState *nextState = m_robotState->nextState(false);

	CPPUNIT_ASSERT(nextState == 0);
}

void DriveToDrivingTest::nextState_obstacleCloseToStartPositionAndTargetNotReached_0()
{
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(0, -0.2), 1));
	m_obstacleFetcher->setAllObstaclesButMeInRangeDependentOnDriveMode(obstacles);
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getEighthRotation()));
	Route route(0.2);
	route.addPoint(Point(0, 0));
	route.addPoint(Point(5, 4));
	vector<Pose> targets;
	targets.push_back(Pose(Point(5, 4), Angle::getQuarterRotation()));
	FieldPositionCheckerMock fieldPositionChecker;
	RouterImpl router(0.5, fieldPositionChecker);
	DriveToDriving state(
				*m_controllableRobot, targets, targets.front(), router, *m_logger, Logger::LogFileTypeAutonomousRobotGoalie,
				*m_obstacleFetcher,	*m_autonomousRobotMock, DriveModeDefault, route);

	RobotState *nextState = state.nextState(false);

	CPPUNIT_ASSERT(nextState == 0);
}

void DriveToDrivingTest::reachedTarget_empty_false()
{
	CPPUNIT_ASSERT(!m_robotState->reachedTarget());
}
