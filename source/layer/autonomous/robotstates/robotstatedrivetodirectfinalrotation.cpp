#include "layer/autonomous/robotstates/robotstatedrivetodirectfinalrotation.h"
#include "layer/autonomous/robotstates/robotstatereachedtarget.h"
#include "layer/abstraction/controllablerobot.h"
#include "common/geometry/compare.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;
using namespace std;

RobotStateDriveToDirectFinalRotation::RobotStateDriveToDirectFinalRotation(
		ControllableRobot &robot, const Pose &target, Logger &logger, Logger::LogFileType logFileType) :
	RobotState(robot, logger, logFileType),
	m_target(target),
	m_precision(0.1),
	m_movementStarted(false)
{ }

bool RobotStateDriveToDirectFinalRotation::reachedTarget() const
{
	return false;
}

bool RobotStateDriveToDirectFinalRotation::cantReachTarget() const
{
	return false;
}

RobotState *RobotStateDriveToDirectFinalRotation::nextState(bool movementStopped)
{
	Pose pose = getRobot().getPose();
	Compare compare(m_precision);

	if (compare.isFuzzyEqual(pose.getOrientation(), m_target.getOrientation()))
	{
		log("final rotation reached");
		return new RobotStateReachedTarget(getRobot(), getLogger(), getLogFileType());
	}
	else if (movementStopped && m_movementStarted)
	{
		log("final rotation not really reached, but movement stopped");
		return new RobotStateReachedTarget(getRobot(), getLogger(), getLogFileType());
	}
	else
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

void RobotStateDriveToDirectFinalRotation::updateInternal(bool)
{
	if (m_movementStarted)
		return;

	getRobot().turn(m_target.getOrientation());
	m_movementStarted = true;
}
