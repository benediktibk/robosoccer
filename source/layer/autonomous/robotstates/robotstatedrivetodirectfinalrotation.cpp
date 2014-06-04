#include "layer/autonomous/robotstates/robotstatedrivetodirectfinalrotation.h"
#include "layer/autonomous/robotstates/robotstatereachedtarget.h"
#include "layer/abstraction/controllablerobot.h"
#include "common/geometry/compare.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;
using namespace std;

DriveToDirectFinalRotation::DriveToDirectFinalRotation(
		ControllableRobot &robot, const Pose &target, Logger &logger, Logger::LogFileType logFileType) :
	RobotState(robot, logger, logFileType),
	m_target(target),
	m_precision(0.1),
	m_movementStarted(false)
{ }

bool DriveToDirectFinalRotation::reachedTarget() const
{
	return false;
}

bool DriveToDirectFinalRotation::cantReachTarget() const
{
	return false;
}

RobotState *DriveToDirectFinalRotation::nextState(bool movementStopped)
{
	Pose pose = getRobot().getPose();
	Compare compare(m_precision);

	if (compare.isFuzzyEqual(pose.getOrientation(), m_target.getOrientation()))
	{
		log("final rotation reached");
		return new ReachedTarget(getRobot(), getLogger(), getLogFileType());
	}
	else if (movementStopped && m_movementStarted)
	{
		log("final rotation not really reached, but movement stopped");
		return new ReachedTarget(getRobot(), getLogger(), getLogFileType());
	}
	else
		return 0;
}

bool DriveToDirectFinalRotation::isEquivalentToDriveToDirect(const Pose &target) const
{
	return m_target == target;
}

bool DriveToDirectFinalRotation::isEquivalentToDriveTo(const Pose &) const
{
	return false;
}

string DriveToDirectFinalRotation::getName() const
{
	return string("drive to direct - final rotation");
}

void DriveToDirectFinalRotation::updateInternal(bool)
{
	if (m_movementStarted)
		return;

	getRobot().turn(m_target.getOrientation());
	m_movementStarted = true;
}
