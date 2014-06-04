#include "layer/autonomous/robotstates/drivetodirectinitialrotationtest.h"
#include "layer/autonomous/robotstates/drivetodirectinitialrotation.h"
#include "layer/abstraction/controllablerobotmock.h"
#include "common/logging/loggermock.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;

RobotState *DriveToDirectInitialRotationTest::createInstance()
{
	return new DriveToDirectInitialRotation(
				*m_controllableRobot, Pose(Point(5, 4), Angle::getQuarterRotation()),
				*m_logger, Logger::LogFileTypeAutonomousRobotGoalie);
}
