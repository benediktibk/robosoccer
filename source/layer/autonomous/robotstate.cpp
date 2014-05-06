#include "layer/autonomous/robotstate.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;

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