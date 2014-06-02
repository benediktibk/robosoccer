#include "layer/autonomous/robotstatedrivetodirectfinalrotation.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;
using namespace std;

RobotStateDriveToDirectFinalRotation::RobotStateDriveToDirectFinalRotation(
		ControllableRobot &robot, const Pose &target, Logger &logger, Logger::LogFileType logFileType) :
	RobotState(robot, logger, logFileType),
	m_target(target)
{ }

bool RobotStateDriveToDirectFinalRotation::reachedTarget() const
{
	return false;
}

bool RobotStateDriveToDirectFinalRotation::cantReachTarget() const
{
	return false;
}

RobotState *RobotStateDriveToDirectFinalRotation::nextState(bool /*movementStopped*/)
{
	return 0;
}

bool RobotStateDriveToDirectFinalRotation::isEquivalentToDriveToDirect(const Pose &target) const
{
	return m_target == target;
}

bool RobotStateDriveToDirectFinalRotation::isEquivalentToDriveTo(const Pose &) const
{
	return false;
}

string RobotStateDriveToDirectFinalRotation::getName() const
{
	return string("drive to direct - final rotation");
}

void RobotStateDriveToDirectFinalRotation::updateInternal(bool /*movementStopped*/)
{

}
