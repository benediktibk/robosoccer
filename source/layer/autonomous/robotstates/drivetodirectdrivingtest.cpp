#include "layer/autonomous/robotstates/drivetodirectdrivingtest.h"
#include "layer/autonomous/robotstates/drivetodirectdriving.h"
#include "layer/autonomous/robotstates/drivetodirectfinalrotation.h"
#include "layer/abstraction/controllablerobotmock.h"
#include "common/logging/loggermock.h"
#include "common/geometry/compare.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;

RobotState *DriveToDirectDrivingTest::createInstance()
{
	return new DriveToDirectDriving(
				*m_controllableRobot, Pose(Point(5, 4), Angle::getQuarterRotation()),
				*m_logger, Logger::LogFileTypeAutonomousRobotGoalie);
}

void DriveToDirectDrivingTest::reachedTarget_empty_false()
{
	CPPUNIT_ASSERT(!m_robotState->reachedTarget());
}

void DriveToDirectDrivingTest::update_onceCalled_robotGotOneCallToDriveToTarget()
{
	m_robotState->update();

	Compare compare(0.00001);
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(5, 4), m_controllableRobot->getLastPointToDriveTo()));
}

void DriveToDirectDrivingTest::update_twiceCalled_robotGotOneCallToDriveToTarget()
{
	m_robotState->update();
	m_robotState->update();

	Compare compare(0.00001);
	CPPUNIT_ASSERT_EQUAL((unsigned int)1, m_controllableRobot->getCallsToGoToCombined());
	CPPUNIT_ASSERT(compare.isFuzzyEqual(Point(5, 4), m_controllableRobot->getLastPointToDriveTo()));
}

void DriveToDirectDrivingTest::nextState_targetNotReached_0()
{
	m_controllableRobot->setPose(Pose(Point(3, 5), Angle::getHalfRotation()));

	RobotState *nextState = m_robotState->nextState(false);

	CPPUNIT_ASSERT(nextState == 0);
}

void DriveToDirectDrivingTest::nextState_targetReached_finalRotation()
{
	m_controllableRobot->setPose(Pose(Point(5, 4), Angle::getHalfRotation()));

	RobotState *nextState = m_robotState->nextState(false);

	DriveToDirectFinalRotation *nextStateCasted = dynamic_cast<DriveToDirectFinalRotation*>(nextState);
	CPPUNIT_ASSERT(nextStateCasted != 0);
	delete nextState;
}

void DriveToDirectDrivingTest::nextState_movementStopped_finalRotation()
{
	m_controllableRobot->setPose(Pose(Point(3, 5), Angle::getHalfRotation()));
	m_robotState->update();

	RobotState *nextState = m_robotState->nextState(true);

	DriveToDirectFinalRotation *nextStateCasted = dynamic_cast<DriveToDirectFinalRotation*>(nextState);
	CPPUNIT_ASSERT(nextStateCasted != 0);
	delete nextState;
}
