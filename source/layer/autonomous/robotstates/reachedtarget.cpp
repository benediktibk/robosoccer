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

bool ReachedTarget::isEquivalentToDriveTo(const vector<Pose> &targets)
{
	for(unsigned int i = 0; i < targets.size(); i++)
	{
		if (isEquivalentToInternal(targets[i], 0.05, 0.5))
			return true;
	}
	return false;
}

bool ReachedTarget::isEquivalentToDriveToDirect(const Pose &target)
{
	return isEquivalentToInternal(target, 0.02, 0.5);
}

void ReachedTarget::update()
{
	getRobot().stop();
}

string ReachedTarget::getName() const
{
	return string("reached target");
}

bool ReachedTarget::isEquivalentToInternal(const Pose &target, double precisionPosition, double precisionOrientation)
{
	Compare positionCompare(precisionPosition);
	Compare orientationCompare(precisionOrientation);
	Pose currentPose = getRobot().getPose();

	if (!positionCompare.isFuzzyEqual(currentPose.getPosition(), target.getPosition()))
	{
		log("position is not equal");
		return false;
	}

	if (!orientationCompare.isFuzzyEqual(currentPose.getOrientation(), target.getOrientation()))
	{
		log("rotation is not equal");
		return false;
	}

	return true;
}
