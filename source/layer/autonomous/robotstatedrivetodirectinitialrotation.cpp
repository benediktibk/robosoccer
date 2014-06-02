#include "layer/autonomous/robotstatedrivetodirectinitialrotation.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;
using namespace std;

RobotStateDriveToDirectInitialRotation::RobotStateDriveToDirectInitialRotation(
		ControllableRobot &robot, const Pose &target, Logger &logger, Logger::LogFileType logFileType) :
	RobotState(robot, logger, logFileType),
	m_target(target)
{ }

bool RobotStateDriveToDirectInitialRotation::reachedTarget() const
{
	return false;
}

bool RobotStateDriveToDirectInitialRotation::cantReachTarget() const
{
	return false;
}

RobotState *RobotStateDriveToDirectInitialRotation::nextState()
{
	return 0;
}

bool RobotStateDriveToDirectInitialRotation::isEquivalentToDriveToDirect(const Pose &target) const
{
	return m_target == target;
}

bool RobotStateDriveToDirectInitialRotation::isEquivalentToDriveTo(const Pose &) const
{
	return false;
}

string RobotStateDriveToDirectInitialRotation::getName() const
{
	return string("drive to direct - inital rotation");
}

void RobotStateDriveToDirectInitialRotation::updateInternal()
{

}
