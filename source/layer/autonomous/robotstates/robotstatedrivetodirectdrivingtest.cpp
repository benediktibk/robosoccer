#include "layer/autonomous/robotstates/robotstatedrivetodirectdrivingtest.h"
#include "layer/autonomous/robotstates/robotstatedrivetodirectdriving.h"
#include "layer/abstraction/controllablerobotmock.h"
#include "common/logging/loggermock.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;

RobotState *RobotStateDriveToDirectDrivingTest::createInstance()
{
	return new RobotStateDriveToDirectDriving(
				*m_controllableRobot, Pose(Point(5, 4), Angle::getQuarterRotation()),
				*m_logger, Logger::LogFileTypeAutonomousRobotGoalie);
}
