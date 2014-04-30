#include "layer/autonomous/robotstatereachedtarget.h"
#include "layer/abstraction/controllablerobot.h"

using namespace RoboSoccer::Layer::Autonomous;

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

void RobotStateReachedTarget::update()
{
	getRobot().stop();
}