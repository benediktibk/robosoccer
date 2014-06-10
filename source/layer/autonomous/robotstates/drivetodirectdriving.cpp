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
	DriveToDirect(robot, target, logger, logFileType)
{ }

RobotState *DriveToDirectDriving::nextState(bool movementStopped)
{
	Pose pose = getRobot().getPose();
	Compare compare(getPrecisionDriving());
	const Pose &target = getTarget();

	if (compare.isFuzzyEqual(pose.getPosition(), target.getPosition()))
	{
		log("position reached");
		return new DriveToDirectFinalRotation(getRobot(), target, getLogger(), getLogFileType());
	}
	else if (movementStopped && hasMovementStarted())
	{
		log("position not really reached, but movement stopped");
		return new DriveToDirectFinalRotation(getRobot(), target, getLogger(), getLogFileType());
	}
	else
		return 0;
}

string DriveToDirectDriving::getName() const
{
	return string("drive to direct - driving");
}

void DriveToDirectDriving::updateInternal()
{
	const Pose &target = getTarget();
	getRobot().gotoPositionPrecise(target.getPosition());
}
