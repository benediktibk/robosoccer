#include "layer/autonomous/robotstates/drivetoinvalidroutetest.h"
#include "layer/autonomous/robotstates/drivetoinvalidroute.h"
#include "layer/autonomous/robotstates/drivetoinitialrotation.h"
#include "layer/autonomous/obstaclefetchermock.h"
#include "layer/autonomous/robotmock.h"
#include "layer/abstraction/fieldpositioncheckergoalkeeper.h"
#include "layer/abstraction/controllablerobotmock.h"
#include "layer/abstraction/fieldpositioncheckermock.h"
#include "common/logging/loggermock.h"
#include "common/routing/routermock.h"
#include "common/routing/routerimpl.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common;
using namespace std;

RobotState *DriveToInvalidRouteTest::createInstance()
{
	vector<Pose> targets;
	targets.push_back(Pose(Point(5, 4), Angle::getQuarterRotation()));

	return new DriveToInvalidRoute(
				*m_controllableRobot, targets, targets.front(), *m_router, *m_logger, Logger::LogFileTypeAutonomousRobotGoalie,
				*m_obstacleFetcher,	*m_autonomousRobotMock, DriveModeDefault, *m_fieldPositionChecker);
}

void DriveToInvalidRouteTest::update_onceCalled_robotGotOneCallToStop()
{
	m_robotState->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToStop());
}

void DriveToInvalidRouteTest::update_twiceCalled_robotGotTwoCallsToStop()
{
	m_robotState->update();
	m_robotState->update();

	CPPUNIT_ASSERT_EQUAL((unsigned int)2, m_controllableRobot->getCallsToStop());
}

void DriveToInvalidRouteTest::nextState_noRouteFeasible_0()
{
	m_router->setInvalidRoute();

	RobotState *nextState = m_robotState->nextState(false);

	CPPUNIT_ASSERT(nextState == 0);
}

void DriveToInvalidRouteTest::nextState_feasibleRoute_initialRotation()
{
	RobotState *nextState = m_robotState->nextState(false);

	DriveToInitialRotation *nextStateCasted = dynamic_cast<DriveToInitialRotation*>(nextState);
	CPPUNIT_ASSERT(nextStateCasted != 0);
	delete nextState;
}

void DriveToInvalidRouteTest::nextState_inGoalRealWorldExample_initialRotation()
{
	vector<Circle> obstacles;
	m_controllableRobot->setPose(Pose(Point(1.29548090934753, -0.0183960431814194), Angle::getQuarterRotation()));
	m_obstacleFetcher->setAllObstaclesButMeInRangeDependentOnDriveMode(obstacles);
	FieldPositionCheckerGoalkeeper fieldPositionChecker;
	vector<Pose> targets;
	targets.push_back(Pose(Point(0, 0), Angle::getQuarterRotation()));
	Routing::RouterImpl router(0.095, fieldPositionChecker);
	DriveToInvalidRoute state(
				*m_controllableRobot, targets, targets.front(), router, *m_logger,
				Logger::LogFileTypeAutonomousRobotGoalie, *m_obstacleFetcher, *m_autonomousRobotMock,
				DriveModeDefault, fieldPositionChecker);

	RobotState *nextState = state.nextState(false);

	DriveToInitialRotation *nextStateCasted = dynamic_cast<DriveToInitialRotation*>(nextState);
	CPPUNIT_ASSERT(nextStateCasted != 0);
	delete nextState;
}

void DriveToInvalidRouteTest::nextState_inGoal_initialRotation()
{
	vector<Circle> obstacles;
	m_controllableRobot->setPose(Pose(Point(1.4, 0), Angle::getQuarterRotation()));
	m_obstacleFetcher->setAllObstaclesButMeInRangeDependentOnDriveMode(obstacles);
	FieldPositionCheckerGoalkeeper fieldPositionChecker;
	vector<Pose> targets;
	targets.push_back(Pose(Point(0, 0), Angle::getQuarterRotation()));
	Routing::RouterImpl router(0.095, fieldPositionChecker);
	DriveToInvalidRoute state(
				*m_controllableRobot, targets, targets.front(), router, *m_logger,
				Logger::LogFileTypeAutonomousRobotGoalie, *m_obstacleFetcher, *m_autonomousRobotMock,
				DriveModeDefault, fieldPositionChecker);

	RobotState *nextState = state.nextState(false);

	DriveToInitialRotation *nextStateCasted = dynamic_cast<DriveToInitialRotation*>(nextState);
	CPPUNIT_ASSERT(nextStateCasted != 0);
	delete nextState;
}

void DriveToInvalidRouteTest::reachedTarget_empty_false()
{
	CPPUNIT_ASSERT(!m_robotState->reachedTarget());
}
