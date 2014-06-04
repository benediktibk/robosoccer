#include "layer/autonomous/robotstates/robotstatedrivetodirectdriving.h"
#include "layer/autonomous/robotstates/robotstatedrivetodirectfinalrotation.h"
#include "layer/abstraction/controllablerobot.h"
#include "common/geometry/compare.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;
using namespace std;

RobotStateDriveToDirectDriving::RobotStateDriveToDirectDriving(
		ControllableRobot &robot, const Pose &target, Logger &logger, Logger::LogFileType logFileType) :
	RobotState(robot, logger, logFileType),
	m_target(target),
	m_precision(0.01),
	m_movementStarted(false)
{ }

bool RobotStateDriveToDirectDriving::reachedTarget() const
{
	return false;
}

bool RobotStateDriveToDirectDriving::cantReachTarget() const
{
	return false;
}

RobotState *RobotStateDriveToDirectDriving::nextState(bool movementStopped)
{
	Pose pose = getRobot().getPose();
	Compare compare(m_precision);

	if (compare.isFuzzyEqual(pose.getPosition(), m_target.getPosition()))
	{
		log("position reached");
		return new RobotStateDriveToDirectFinalRotation(getRobot(), m_target, getLogger(), getLogFileType());
	}
	else if (movementStopped && m_movementStarted)
	{
		log("position not really reached, but movement stopped");
		return new RobotStateDriveToDirectFinalRotation(getRobot(), m_target, getLogger(), getLogFileType());
	}
	else
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

void RobotStateDriveToDirectDriving::updateInternal(bool)
{
	if (m_movementStarted)
		return;

	getRobot().gotoPositionPrecise(m_target.getPosition());
	m_movementStarted = true;
}
