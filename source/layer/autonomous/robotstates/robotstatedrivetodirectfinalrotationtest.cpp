#include "layer/autonomous/robotstates/robotstatedrivetodirectfinalrotationtest.h"
#include "layer/autonomous/robotstates/robotstatedrivetodirectfinalrotation.h"
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
