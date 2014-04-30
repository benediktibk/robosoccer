#include "layer/autonomous/robotstatereachedtarget.h"
#include "layer/abstraction/controllablerobot.h"

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

bool RobotStateReachedTarget::isEquivalentToDriveTo(const Point &) const
{
	return false;
}

void RobotStateReachedTarget::update()
{
	getRobot().stop();
}