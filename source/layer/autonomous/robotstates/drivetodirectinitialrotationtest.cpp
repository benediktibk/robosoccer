#include "layer/autonomous/robotstates/drivetodirectinitialrotationtest.h"
#include "layer/autonomous/robotstates/drivetodirectinitialrotation.h"
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
