#include "layer/autonomous/robotstates/robotstatereachedtarget.h"
#include "layer/abstraction/controllablerobot.h"
#include "common/geometry/compare.h"
#include "common/geometry/pose.h"

using namespace std;
using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;

RobotStateReachedTarget::RobotStateReachedTarget(
		Abstraction::ControllableRobot &robot, Logger &logger, Logger::LogFileType logFileType) :
	RobotState(robot, logger, logFileType)
{ }

bool RobotStateReachedTarget::reachedTarget() const
{
	return true;
}

bool RobotStateReachedTarget::cantReachTarget() const
{
	return false;
}

RobotState *RobotStateReachedTarget::nextState(bool)
{
	return 0;
}

bool RobotStateReachedTarget::isEquivalentToDriveTo(const Pose &target) const
{
	Compare compare(0.02);
	Pose currentPose = getRobot().getPose();
	return compare.isFuzzyEqual(currentPose.getPosition(), target);
}

bool RobotStateReachedTarget::isEquivalentToDriveToDirect(const Pose &target) const
{
	return isEquivalentToDriveTo(target);
}

void RobotStateReachedTarget::updateInternal(bool)
{
	getRobot().stop();
}

string RobotStateReachedTarget::getName() const
{
	return string("reached target");
}
