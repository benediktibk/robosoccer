#include "layer/autonomous/robotstates/drivetodirectfinalrotationtest.h"
#include "layer/autonomous/robotstates/drivetodirectfinalrotation.h"
#include "layer/abstraction/controllablerobotmock.h"
#include "common/logging/loggermock.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;

RobotState *DriveToDirectFinalRotationTest::createInstance()
{
	return new DriveToDirectFinalRotation(
				*m_controllableRobot, Pose(Point(5, 4), Angle::getQuarterRotation()),
				*m_logger, Logger::LogFileTypeAutonomousRobotGoalie);
}

void DriveToDirectFinalRotationTest::reachedTarget_empty_false()
{
	CPPUNIT_ASSERT(!m_robotState->reachedTarget());
}
