#include "layer/autonomous/robotstates/reachedtarget.h"
#include "layer/abstraction/controllablerobot.h"
#include "common/geometry/compare.h"
#include "common/geometry/pose.h"

using namespace std;
using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;

ReachedTarget::ReachedTarget(
		Abstraction::ControllableRobot &robot, Logger &logger, Logger::LogFileType logFileType) :
	RobotState(robot, logger, logFileType)
{ }

bool ReachedTarget::reachedTarget() const
{
	return true;
}

RobotState *ReachedTarget::nextState(bool)
{
	return 0;
}

bool ReachedTarget::isEquivalentToDriveTo(const Pose &target) const
{
	Compare compare(0.02);
	Pose currentPose = getRobot().getPose();
	return compare.isFuzzyEqual(currentPose, target);
}

bool ReachedTarget::isEquivalentToDriveToDirect(const Pose &target) const
{
	return isEquivalentToDriveTo(target);
}

void ReachedTarget::update(bool)
{
	getRobot().stop();
}

string ReachedTarget::getName() const
{
	return string("reached target");
}
