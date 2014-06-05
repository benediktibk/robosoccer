#include "layer/autonomous/robotstates/drivetodirectinitialrotationtest.h"
#include "layer/autonomous/robotstates/drivetodirectinitialrotation.h"
#include "layer/autonomous/robotstates/drivetodirectdriving.h"
#include "layer/abstraction/controllablerobotmock.h"
#include "common/logging/loggermock.h"
#include "common/geometry/compare.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;

RobotState *DriveToDirectInitialRotationTest::createInstance()
{
	return new DriveToDirectInitialRotation(
				*m_controllableRobot, Pose(Point(5, 4), Angle::getQuarterRotation()),
				*m_logger, Logger::LogFileTypeAutonomousRobotGoalie);
}

void DriveToDirectInitialRotationTest::reachedTarget_empty_false()
{
	CPPUNIT_ASSERT(!m_robotState->reachedTarget());
}

void DriveToDirectInitialRotationTest::update_onceCalled_robotGotCallToTurnToTarget()
{
	m_robotState->update();

	Compare compare(0.0001);
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle(Point(0, 0), Point(5, 4)), m_controllableRobot->getLastAngleToTurnTo()));
}

void DriveToDirectInitialRotationTest::update_twiceCalled_robotGotCallToTurnToTarget()
{
	m_robotState->update();
	m_robotState->update();

	Compare compare(0.0001);
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToTurn());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Angle(Point(0, 0), Point(5, 4)), m_controllableRobot->getLastAngleToTurnTo()));
}

void DriveToDirectInitialRotationTest::nextState_rotationNotReached_0()
{
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getHalfRotation()));

	RobotState *nextState = m_robotState->nextState(false);

	CPPUNIT_ASSERT(nextState == 0);
}

void DriveToDirectInitialRotationTest::nextState_rotationReached_driving()
{
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle(Point(0, 0), Point(5, 4))));

	RobotState *nextState = m_robotState->nextState(false);

	DriveToDirectDriving *nextStateCasted = dynamic_cast<DriveToDirectDriving*>(nextState);
	CPPUNIT_ASSERT(nextStateCasted != 0);
	delete nextState;
}

void DriveToDirectInitialRotationTest::nextState_movementStopped_driving()
{
	m_controllableRobot->setPose(Pose(Point(0, 0), Angle::getHalfRotation()));
	m_robotState->update();

	RobotState *nextState = m_robotState->nextState(true);

	DriveToDirectDriving *nextStateCasted = dynamic_cast<DriveToDirectDriving*>(nextState);
	CPPUNIT_ASSERT(nextStateCasted != 0);
	delete nextState;
}
