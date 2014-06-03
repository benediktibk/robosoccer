#include "layer/autonomous/robotstatedrivetodirectinitialrotation.h"
#include "layer/autonomous/robotstatedrivetodirectdriving.h"
#include "layer/abstraction/controllablerobot.h"
#include "common/geometry/compare.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;
using namespace std;

RobotStateDriveToDirectInitialRotation::RobotStateDriveToDirectInitialRotation(
		ControllableRobot &robot, const Pose &target, Logger &logger, Logger::LogFileType logFileType) :
	RobotState(robot, logger, logFileType),
	m_target(target),
	m_precision(0.4),
	m_movementStarted(false)
{ }

bool RobotStateDriveToDirectInitialRotation::reachedTarget() const
{
	return false;
}

bool RobotStateDriveToDirectInitialRotation::cantReachTarget() const
{
	return false;
}

RobotState *RobotStateDriveToDirectInitialRotation::nextState(bool movementStopped)
{
	Pose pose = getRobot().getPose();
	Compare compareAngle(m_precision);
	Angle targetAngle = calculateTargetAngle();

	if (compareAngle.isFuzzyEqual(pose.getOrientation(), targetAngle))
	{
		log("inital rotation reached");
		return new RobotStateDriveToDirectDriving(getRobot(), m_target, getLogger(), getLogFileType());
	}
	else if (movementStopped && m_movementStarted)
	{
		log("inital rotation not really reached, but movement stopped");
		return new RobotStateDriveToDirectDriving(getRobot(), m_target, getLogger(), getLogFileType());
	}
	else
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

void RobotStateDriveToDirectInitialRotation::updateInternal(bool)
{
	if (m_movementStarted)
		return;

	Angle targetAngle = calculateTargetAngle();
	getRobot().turn(targetAngle);
	m_movementStarted = true;
}

Angle RobotStateDriveToDirectInitialRotation::calculateTargetAngle() const
{
	Pose pose = getRobot().getPose();
	return Angle(pose.getPosition(), m_target.getPosition());
}
