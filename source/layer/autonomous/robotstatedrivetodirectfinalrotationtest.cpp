#include "layer/autonomous/robotstatedrivetodirectfinalrotationtest.h"
#include "layer/autonomous/robotstatedrivetodirectfinalrotation.h"
#include "layer/abstraction/controllablerobotmock.h"
#include "common/logging/loggermock.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;

RobotState *RobotStateDriveToDirectFinalRotationTest::createInstance()
{
	return new RobotStateDriveToDirectFinalRotation(
				*m_controllableRobot, Pose(Point(5, 4), Angle::getQuarterRotation()),
				*m_logger, Logger::LogFileTypeAutonomousRobotGoalie);
}
