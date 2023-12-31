#include "layer/autonomous/robotstates/drivetofinalrotationtest.h"
#include "layer/autonomous/robotstates/drivetofinalrotation.h"
#include "layer/autonomous/robotstates/drivetoinvalidroute.h"
#include "layer/autonomous/robotstates/reachedtarget.h"
#include "layer/autonomous/obstaclefetchermock.h"
#include "layer/autonomous/robotmock.h"
#include "layer/abstraction/controllablerobotmock.h"
#include "layer/abstraction/fieldpositioncheckermock.h"
#include "common/logging/loggermock.h"
#include "common/routing/routermock.h"
#include "common/geometry/compare.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::Routing;
using namespace std;

RobotState *DriveToFinalRotationTest::createInstance()
{
	vector<Pose> targets;
	targets.push_back(Pose(Point(5, 4), Angle::getQuarterRotation()));

	return new DriveToFinalRotation(
				*m_controllableRobot, targets, targets.front(), *m_router, *m_logger, Logger::LogFileTypeAutonomousRobotGoalie,
				*m_obstacleFetcher, *m_autonomousRobotMock, DriveModeDefault, *m_route, *m_fieldPositionChecker);
}

void DriveToFinalRotationTest::constructor_routeWithTwoPoints_routeHasTwoPoints()
{
	vector<Pose> targets;
	targets.push_back(Pose(Point(5, 4), Angle::getQuarterRotation()));

	DriveToFinalRotation state(
					*m_controllableRobot, targets, targets.front(), *m_router, *m_logger, Logger::LogFileTypeAutonomousRobotGoalie,
					*m_obstacleFetcher,	*m_autonomousRobotMock, DriveModeDefault, *m_route, *m_fieldPositionChecker);

	CPPUNIT_ASSERT_EQUAL((size_t)2, state.getRoutePointsCount());
}

void DriveToFinalRotationTest::update_onceCalled_robotGotOneCallToTurnToFinalRotation()
{
	m_robotState->update();

	Compare compare(0.0001);
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getQuarterRotation(), m_controllableRobot->getLastAngleToTurnTo()));
}

void DriveToFinalRotationTest::update_twiceCalled_robotGotOneCallToTurnToFinalRotation()
{
	m_robotState->update();
	m_robotState->update();

	Compare compare(0.0001);
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle::getQuarterRotation(), m_controllableRobot->getLastAngleToTurnTo()));
}

void DriveToFinalRotationTest::nextState_finalRotationNotReached_0()
{
	m_controllableRobot->setPose(Pose(Point(5, 4), Angle::getHalfRotation()));

	RobotState *nextState = m_robotState->nextState(false);

	CPPUNIT_ASSERT(nextState == 0);
}

void DriveToFinalRotationTest::nextState_finalRotationReached_reachedTarget()
{
	m_controllableRobot->setPose(Pose(Point(5, 4), Angle::getQuarterRotation()));

	RobotState *nextState = m_robotState->nextState(false);

	ReachedTarget *nextStateCasted = dynamic_cast<ReachedTarget*>(nextState);
	CPPUNIT_ASSERT(nextStateCasted != 0);
	delete nextState;
}

void DriveToFinalRotationTest::nextState_movementStopped_reachedTarget()
{
	m_controllableRobot->setPose(Pose(Point(5, 4), Angle::getHalfRotation()));
	m_robotState->update();

	RobotState *nextState = m_robotState->nextState(true);

	ReachedTarget *nextStateCasted = dynamic_cast<ReachedTarget*>(nextState);
	CPPUNIT_ASSERT(nextStateCasted != 0);
	delete nextState;
}

void DriveToFinalRotationTest::reachedTarget_empty_false()
{
	CPPUNIT_ASSERT(!m_robotState->reachedTarget());
}

void DriveToFinalRotationTest::nextState_currentTargetIsTheSecondTargetAndFinalRotationNotReached_0()
{
	m_controllableRobot->setPose(Pose(Point(1, 1), Angle()));
	vector<Pose> targets;
	targets.push_back(Pose(Point(5, 4), Angle::getQuarterRotation()));
	targets.push_back(Pose(Point(1, 1), Angle::getQuarterRotation()));
	DriveToFinalRotation state(
				*m_controllableRobot, targets, targets.back(), *m_router, *m_logger, Logger::LogFileTypeAutonomousRobotGoalie,
				*m_obstacleFetcher, *m_autonomousRobotMock, DriveModeDefault, *m_route, *m_fieldPositionChecker);
	state.update();

	RobotState *nextState = state.nextState(false);

	CPPUNIT_ASSERT(nextState == 0);
}

void DriveToFinalRotationTest::nextState_currentTargetIsTheSecondTargetAndFinalRotationReached_reachedTarget()
{
	m_controllableRobot->setPose(Pose(Point(1, 1), Angle()));
	vector<Pose> targets;
	targets.push_back(Pose(Point(5, 4), Angle::getQuarterRotation()));
	targets.push_back(Pose(Point(1, 1), Angle::getQuarterRotation()));
	DriveToFinalRotation state(
				*m_controllableRobot, targets, targets.back(), *m_router, *m_logger, Logger::LogFileTypeAutonomousRobotGoalie,
				*m_obstacleFetcher, *m_autonomousRobotMock, DriveModeDefault, *m_route, *m_fieldPositionChecker);
	state.update();
	m_controllableRobot->setPose(Pose(Point(1, 1), Angle::getQuarterRotation()));
	state.update();

	RobotState *nextState = state.nextState(false);

	ReachedTarget *nextStateCasted = dynamic_cast<ReachedTarget*>(nextState);
	CPPUNIT_ASSERT(nextStateCasted != 0);
	delete nextState;
}
