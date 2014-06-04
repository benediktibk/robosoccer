#include "layer/autonomous/robotstates/drivetodirectdriving.h"
#include "layer/autonomous/robotstates/drivetodirectfinalrotation.h"
#include "layer/abstraction/controllablerobot.h"
#include "common/geometry/compare.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;
using namespace std;

DriveToDirectDriving::DriveToDirectDriving(
		ControllableRobot &robot, const Pose &target, Logger &logger, Logger::LogFileType logFileType) :
	RobotState(robot, logger, logFileType),
	m_target(target),
	m_precision(0.01),
	m_movementStarted(false)
{ }

bool DriveToDirectDriving::reachedTarget() const
{
	return false;
}

RobotState *DriveToDirectDriving::nextState(bool movementStopped)
{
	Pose pose = getRobot().getPose();
	Compare compare(m_precision);

	if (compare.isFuzzyEqual(pose.getPosition(), m_target.getPosition()))
	{
		log("position reached");
		return new DriveToDirectFinalRotation(getRobot(), m_target, getLogger(), getLogFileType());
	}
	else if (movementStopped && m_movementStarted)
	{
		log("position not really reached, but movement stopped");
		return new DriveToDirectFinalRotation(getRobot(), m_target, getLogger(), getLogFileType());
	}
	else
		return 0;
}

bool DriveToDirectDriving::isEquivalentToDriveToDirect(const Pose &target) const
{
	return m_target == target;
}

bool DriveToDirectDriving::isEquivalentToDriveTo(const Pose &) const
{
	return false;
}

string DriveToDirectDriving::getName() const
{
	return string("drive to direct - driving");
}

void DriveToDirectDriving::updateInternal(bool)
{
	if (m_movementStarted)
		return;

	getRobot().gotoPositionPrecise(m_target.getPosition());
	m_movementStarted = true;
}
