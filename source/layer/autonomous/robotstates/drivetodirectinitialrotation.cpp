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
	DriveToDirect(robot, target, logger, logFileType)
{ }

RobotState *DriveToDirectInitialRotation::nextState(bool movementStopped)
{
	Pose pose = getRobot().getPose();
	Compare compareAngle(getPrecisionInitialRotation());
	Angle targetAngle = calculateTargetAngle();
	const Pose &target = getTarget();

	if (compareAngle.isFuzzyEqual(pose.getOrientation(), targetAngle))
	{
		log("inital rotation reached");
		return new DriveToDirectDriving(getRobot(), target, getLogger(), getLogFileType());
	}
	else if (movementStopped && hasMovementStarted())
	{
		log("inital rotation not really reached, but movement stopped");
		return new DriveToDirectDriving(getRobot(), target, getLogger(), getLogFileType());
	}
	else
		return 0;
}

string DriveToDirectInitialRotation::getName() const
{
	return string("drive to direct - inital rotation");
}

void DriveToDirectInitialRotation::updateInternal()
{
	Angle targetAngle = calculateTargetAngle();
	getRobot().turn(targetAngle);
}

Angle DriveToDirectInitialRotation::calculateTargetAngle() const
{
	Pose pose = getRobot().getPose();
	const Pose &target = getTarget();
	return Angle(pose.getPosition(), target.getPosition());
}
