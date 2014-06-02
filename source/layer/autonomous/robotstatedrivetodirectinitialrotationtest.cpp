#include "layer/autonomous/robotstatedrivetodirectinitialrotationtest.h"
#include "layer/autonomous/robotstatedrivetodirectinitialrotation.h"
#include "layer/abstraction/controllablerobotmock.h"
#include "common/logging/loggermock.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;

RobotState *RobotStateDriveToDirectInitialRotationTest::createInstance()
{
	return new RobotStateDriveToDirectInitialRotation(
				*m_controllableRobot, Pose(Point(5, 4), Angle::getQuarterRotation()),
				*m_logger, Logger::LogFileTypeAutonomousRobotGoalie);
}
