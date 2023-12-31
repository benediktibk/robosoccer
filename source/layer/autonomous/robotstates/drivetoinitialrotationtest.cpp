#include "layer/autonomous/robotstates/drivetoinitialrotationtest.h"
#include "layer/autonomous/robotstates/drivetoinitialrotation.h"
#include "layer/autonomous/robotstates/drivetoinvalidroute.h"
#include "layer/autonomous/robotstates/drivetodriving.h"
#include "layer/autonomous/obstaclefetchermock.h"
#include "layer/autonomous/robotmock.h"
#include "layer/abstraction/controllablerobotmock.h"
#include "layer/abstraction/fieldpositioncheckermock.h"
#include "common/logging/loggermock.h"
#include "common/routing/routermock.h"
#include "common/routing/routerimpl.h"
#include "common/routing/fieldpositioncheckermock.h"
#include "common/geometry/compare.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common;
using namespace std;

RobotState *DriveToInitialRotationTest::createInstance()
{
	vector<Pose> targets;
	targets.push_back(Pose(Point(5, 4), Angle::getQuarterRotation()));

	return new DriveToInitialRotation(
				*m_controllableRobot, targets, targets.front(), *m_router, *m_logger, Logger::LogFileTypeAutonomousRobotGoalie,
				*m_obstacleFetcher,	*m_autonomousRobotMock, DriveModeDefault, *m_fieldPositionChecker);
}

void DriveToInitialRotationTest::update_onceCalled_robotGotOneCallToTurnToSecondPoint()
{
	m_robotState->update();

	Compare compare(0.0001);
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle(Point(0, 0), Point(5, 4)), m_controllableRobot->getLastAngleToTurnTo()));
}

void DriveToInitialRotationTest::update_twiceCalled_robotGotOneCallToTurnToSecondPoint()
{
	m_robotState->update();
	m_robotState->update();

	Compare compare(0.0001);
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle(Point(0, 0), Point(5, 4)), m_controllableRobot->getLastAngleToTurnTo()));
}

void DriveToInitialRotationTest::nextState_routeBecomesInvalidAndNoNewOnePossible_invalidRoute()
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

void DriveToInitialRotationTest::nextState_routeBecomesInvalidAndNewOnePossible_initialRotation()
{
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(3, 3), 1));
	m_obstacleFetcher->setAllObstaclesButMeInRangeDependentOnDriveMode(obstacles);
	m_router->setChessMode(true);

	RobotState *nextState = m_robotState->nextState(false);

	DriveToInitialRotation *nextStateCasted = dynamic_cast<DriveToInitialRotation*>(nextState);
	CPPUNIT_ASSERT(nextStateCasted != 0);
	delete nextState;
}

void DriveToInitialRotationTest::nextState_targetNotReached_0()
{
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getHalfRotation()));

	RobotState *nextState = m_robotState->nextState(false);

	CPPUNIT_ASSERT(nextState == 0);
}

void DriveToInitialRotationTest::nextState_movementStopped_driving()
{
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getHalfRotation()));
	m_robotState->update();

	RobotState *nextState = m_robotState->nextState(true);

	DriveToDriving *nextStateCasted = dynamic_cast<DriveToDriving*>(nextState);
	CPPUNIT_ASSERT(nextStateCasted != 0);
	delete nextState;
}

void DriveToInitialRotationTest::nextState_targetReached_driving()
{
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle(Point(0, 0), Point(5, 4))));

	RobotState *nextState = m_robotState->nextState(false);

	DriveToDriving *nextStateCasted = dynamic_cast<DriveToDriving*>(nextState);
	CPPUNIT_ASSERT(nextStateCasted != 0);
	delete nextState;
}

void DriveToInitialRotationTest::constructor_noRoute_routeCreated()
{
	DriveTo *stateCasted = dynamic_cast<DriveTo*>(m_robotState);

	CPPUNIT_ASSERT_EQUAL((size_t)2, stateCasted->getRoutePointsCount());
}

void DriveToInitialRotationTest::constructor_routeWithThreePoints_routeHasThreePoints()
{
	Routing::Route route(1);
	route.addPoint(Point(0, 0));
	route.addPoint(Point(1, 0));
	route.addPoint(Point(1, 2));

	vector<Pose> targets;
	targets.push_back(Pose(Point(5, 4), Angle::getQuarterRotation()));

	DriveToInitialRotation state(
					*m_controllableRobot, targets, targets.front(), *m_router, *m_logger, Logger::LogFileTypeAutonomousRobotGoalie,
					*m_obstacleFetcher,	*m_autonomousRobotMock, DriveModeDefault, route, *m_fieldPositionChecker);

	CPPUNIT_ASSERT_EQUAL((size_t)3, state.getRoutePointsCount());
}

void DriveToInitialRotationTest::reachedTarget_empty_false()
{
	CPPUNIT_ASSERT(!m_robotState->reachedTarget());
}

void DriveToInitialRotationTest::constructor_noRouteAndFirstRouteInvalid_routeCreated()
{
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(5, 4), 1));
	m_obstacleFetcher->setAllObstaclesButMeInRangeDependentOnDriveMode(obstacles);
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getEighthRotation()));
	vector<Pose> targets;
	targets.push_back(Pose(Point(5, 4), Angle::getQuarterRotation()));
	targets.push_back(Pose(Point(3, 3), Angle::getQuarterRotation()));
	FieldPositionCheckerMock fieldPositionChecker;
	Routing::RouterImpl router(0.5, fieldPositionChecker);
	DriveToInitialRotation *state = new DriveToInitialRotation(
				*m_controllableRobot, targets, targets.front(), router, *m_logger, Logger::LogFileTypeAutonomousRobotGoalie,
				*m_obstacleFetcher,	*m_autonomousRobotMock, DriveModeDefault, fieldPositionChecker);

	DriveTo *stateCasted = dynamic_cast<DriveTo*>(state);

	CPPUNIT_ASSERT_EQUAL((size_t)2, stateCasted->getRoutePointsCount());
	delete state;
}

void DriveToInitialRotationTest::nextState_targetNotReachedButProposalRouteIsMuchBetter_initialRotationWithNewRoute()
{
	Routing::Route route(1);
	route.addPoint(Point(0, 0));
	route.addPoint(Point(1, 0));
	route.addPoint(Point(25, 0));
	route.addPoint(Point(5, 4));

	vector<Pose> targets;
	targets.push_back(Pose(Point(5, 4), Angle::getQuarterRotation()));

	DriveToInitialRotation state(
					*m_controllableRobot, targets, targets.front(), *m_router, *m_logger, Logger::LogFileTypeAutonomousRobotGoalie,
					*m_obstacleFetcher,	*m_autonomousRobotMock, DriveModeDefault, route, *m_fieldPositionChecker);

	RobotState *nextState = state.nextState(false);

	DriveToInitialRotation *nextStateCasted = dynamic_cast<DriveToInitialRotation*>(nextState);
	CPPUNIT_ASSERT(nextStateCasted != 0);
	CPPUNIT_ASSERT_EQUAL((size_t)2, nextStateCasted->getRoutePointsCount());
	delete nextState;
}

void DriveToInitialRotationTest::nextState_targetNotReachedAndProposalRouteIsMuchBetterButInvalid_0()
{
	Routing::Route route(1);
	route.addPoint(Point(0, 0));
	route.addPoint(Point(0, 1));
	route.addPoint(Point(25, 0));
	route.addPoint(Point(5, 4));

	vector<Pose> targets;
	targets.push_back(Pose(Point(5, 4), Angle::getQuarterRotation()));

	DriveToInitialRotation state(
					*m_controllableRobot, targets, targets.front(), *m_router, *m_logger, Logger::LogFileTypeAutonomousRobotGoalie,
					*m_obstacleFetcher,	*m_autonomousRobotMock, DriveModeDefault, route, *m_fieldPositionChecker);
	m_router->setInvalidRoute();

	RobotState *nextState = state.nextState(false);

	CPPUNIT_ASSERT(nextState == 0);
}

void DriveToInitialRotationTest::nextState_targetNotReachedAndProposalRouteIsMuchBetterButCurrentRouteIsToShort_0()
{
	Routing::Route route(0.1);
	route.addPoint(Point(0, 0));
	route.addPoint(Point(0, 0.04));
	route.addPoint(Point(0.05, 0.04));
	route.addPoint(Point(0.05, 0));

	vector<Pose> targets;
	targets.push_back(Pose(Point(0.05, 0), Angle::getQuarterRotation()));

	DriveToDriving state(
				*m_controllableRobot, targets, targets.front(), *m_router, *m_logger, Logger::LogFileTypeAutonomousRobotGoalie,
				*m_obstacleFetcher,	*m_autonomousRobotMock, DriveModeDefault, route, *m_fieldPositionChecker);
	m_controllableRobot->setPose(Pose(Point(0, 0.01), Angle(0)));

	RobotState *nextState = state.nextState(false);

	CPPUNIT_ASSERT(nextState == 0);
}

void DriveToInitialRotationTest::nextState_currentRouteNotFeasibleAndNextOneToo_invalidRoute()
{
	vector<Circle> obstacles;
	obstacles.push_back(Circle(Point(3, 3), 1));
	m_obstacleFetcher->setAllObstaclesButMeInRangeDependentOnDriveMode(obstacles);

	RobotState *nextState = m_robotState->nextState(false);

	DriveToInvalidRoute *nextStateCasted = dynamic_cast<DriveToInvalidRoute*>(nextState);
	CPPUNIT_ASSERT(nextStateCasted != 0);
	delete nextState;
}
