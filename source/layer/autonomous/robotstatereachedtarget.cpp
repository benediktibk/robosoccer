#include "layer/autonomous/robotstatereachedtarget.h"
#include "layer/abstraction/controllablerobot.h"
#include "common/geometry/compare.h"
#include "common/geometry/pose.h"

using namespace std;
using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;

RobotStateReachedTarget::RobotStateReachedTarget(Abstraction::ControllableRobot &robot) :
	RobotState(robot)
{ }

bool RobotStateReachedTarget::reachedTarget() const
{
	return true;
}

bool RobotStateReachedTarget::cantReachTarget() const
{
	return false;
}

RobotState *RobotStateReachedTarget::nextState()
{
	return 0;
}

bool RobotStateReachedTarget::isEquivalentToDriveTo(const Pose &target) const
{
	Compare compare(0.02);
	Pose currentPose = getRobot().getPose();
	return compare.isFuzzyEqual(currentPose.getPosition(), target);
}

void RobotStateReachedTarget::updateInternal()
{
	getRobot().stop();
}

string RobotStateReachedTarget::getName() const
{
	return string("reached target");
}
