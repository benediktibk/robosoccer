#include "layer/autonomous/robotstates/drivetodirectfinalrotation.h"
#include "layer/autonomous/robotstates/reachedtarget.h"
#include "layer/abstraction/controllablerobot.h"
#include "common/geometry/compare.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;
using namespace std;

DriveToDirectFinalRotation::DriveToDirectFinalRotation(
		ControllableRobot &robot, const Pose &target, Logger &logger, Logger::LogFileType logFileType) :
	DriveToDirect(robot, target, logger, logFileType)
{ }

RobotState *DriveToDirectFinalRotation::nextState(bool movementStopped)
{
	Pose pose = getRobot().getPose();
	const Pose &target = getTarget();
	Compare compare(getPrecisionFinalRotation());

	if (compare.isFuzzyEqual(pose.getOrientation(), target.getOrientation()))
	{
		log("final rotation reached");
		return new ReachedTarget(getRobot(), getLogger(), getLogFileType());
	}
	else if (movementStopped && hasMovementStarted())
	{
		log("final rotation not really reached, but movement stopped");
		return new ReachedTarget(getRobot(), getLogger(), getLogFileType());
	}
	else
		return 0;
}

string DriveToDirectFinalRotation::getName() const
{
	return string("drive to direct - final rotation");
}

void DriveToDirectFinalRotation::updateInternal()
{
	const Pose &target = getTarget();
	getRobot().turn(target.getOrientation());
}
