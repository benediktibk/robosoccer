#include "layer/autonomous/robotstates/drivetodirectinitialrotation.h"
#include "layer/autonomous/robotstates/drivetodirectdriving.h"
#include "layer/abstraction/controllablerobot.h"
#include "common/geometry/compare.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;
using namespace std;

DriveToDirectInitialRotation::DriveToDirectInitialRotation(
		ControllableRobot &robot, const Pose &target, Logger &logger, Logger::LogFileType logFileType) :
	RobotState(robot, logger, logFileType),
	m_target(target),
	m_precision(0.4),
	m_movementStarted(false)
{ }

bool DriveToDirectInitialRotation::reachedTarget() const
{
	return false;
}

bool DriveToDirectInitialRotation::cantReachTarget() const
{
	return false;
}

RobotState *DriveToDirectInitialRotation::nextState(bool movementStopped)
{
	Pose pose = getRobot().getPose();
	Compare compareAngle(m_precision);
	Angle targetAngle = calculateTargetAngle();

	if (compareAngle.isFuzzyEqual(pose.getOrientation(), targetAngle))
	{
		log("inital rotation reached");
		return new DriveToDirectDriving(getRobot(), m_target, getLogger(), getLogFileType());
	}
	else if (movementStopped && m_movementStarted)
	{
		log("inital rotation not really reached, but movement stopped");
		return new DriveToDirectDriving(getRobot(), m_target, getLogger(), getLogFileType());
	}
	else
		return 0;
}

bool DriveToDirectInitialRotation::isEquivalentToDriveToDirect(const Pose &target) const
{
	return m_target == target;
}

bool DriveToDirectInitialRotation::isEquivalentToDriveTo(const Pose &) const
{
	return false;
}

string DriveToDirectInitialRotation::getName() const
{
	return string("drive to direct - inital rotation");
}

void DriveToDirectInitialRotation::updateInternal(bool)
{
	if (m_movementStarted)
		return;

	Angle targetAngle = calculateTargetAngle();
	getRobot().turn(targetAngle);
	m_movementStarted = true;
}

Angle DriveToDirectInitialRotation::calculateTargetAngle() const
{
	Pose pose = getRobot().getPose();
	return Angle(pose.getPosition(), m_target.getPosition());
}
