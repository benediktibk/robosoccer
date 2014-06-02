#include "layer/autonomous/robotstatedrivetodirectdriving.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;
using namespace std;

RobotStateDriveToDirectDriving::RobotStateDriveToDirectDriving(
		ControllableRobot &robot, const Pose &target, Logger &logger, Logger::LogFileType logFileType) :
	RobotState(robot, logger, logFileType),
	m_target(target)
{ }

bool RobotStateDriveToDirectDriving::reachedTarget() const
{
	return false;
}

bool RobotStateDriveToDirectDriving::cantReachTarget() const
{
	return false;
}

RobotState *RobotStateDriveToDirectDriving::nextState(bool /*movementStopped*/)
{
	return 0;
}

bool RobotStateDriveToDirectDriving::isEquivalentToDriveToDirect(const Pose &target) const
{
	return m_target == target;
}

bool RobotStateDriveToDirectDriving::isEquivalentToDriveTo(const Pose &) const
{
	return false;
}

string RobotStateDriveToDirectDriving::getName() const
{
	return string("drive to direct - driving");
}

void RobotStateDriveToDirectDriving::updateInternal(bool /*movementStopped*/)
{

}
