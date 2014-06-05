#include "layer/autonomous/robotstates/drivetodrivingtest.h"
#include "layer/autonomous/robotstates/drivetodriving.h"
#include "layer/autonomous/robotstates/drivetoinvalidroute.h"
#include "layer/autonomous/robotstates/drivetoinitialrotation.h"
#include "layer/autonomous/obstaclefetchermock.h"
#include "layer/autonomous/robotmock.h"
#include "layer/abstraction/controllablerobotmock.h"
#include "common/logging/loggermock.h"
#include "common/routing/routermock.h"
#include "common/geometry/compare.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::Routing;
using namespace std;

RobotState *DriveToDrivingTest::createInstance()
{
	return new DriveToDriving(
				*m_controllableRobot, Pose(Point(5, 4), Angle::getQuarterRotation()),
				*m_router, *m_logger, Logger::LogFileTypeAutonomousRobotGoalie, *m_obstacleFetcher,
				*m_autonomousRobotMock, false, false, false, *m_route);
}

void DriveToDrivingTest::constructor_routeWithThreePoints_routesHasThreePoints()
{
	Route route(1);
	route.addPoint(Point(0, 0));
	route.addPoint(Point(1, 0));
	route.addPoint(Point(1, 2));

	DriveToDriving state(
					*m_controllableRobot, Pose(Point(5, 4), Angle::getQuarterRotation()),
					*m_router, *m_logger, Logger::LogFileTypeAutonomousRobotGoalie, *m_obstacleFetcher,
					*m_autonomousRobotMock, false, false, false, route);

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
	m_obstacleFetcher->setAllObstaclesButMeInRange(obstacles);
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
	m_obstacleFetcher->setAllObstaclesButMeInRange(obstacles);

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
