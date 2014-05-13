#include "layer/autonomous/robotstate.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;

RobotState::RobotState(Abstraction::ControllableRobot &robot) :
	m_robot(robot)
{ }

RobotState::~RobotState()
{ }

ControllableRobot &RobotState::getRobot()
{
	return m_robot;
}

ControllableRobot const &RobotState::getRobot() const
{
	return m_robot;
}

bool RobotState::isEquivalentToDriveTo(const Point &) const
{
	return false;
}

bool RobotState::isEquivalentToDriveToDirect(const Pose &) const
{
	return false;
}
