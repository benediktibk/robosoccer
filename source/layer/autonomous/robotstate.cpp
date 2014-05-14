#include "layer/autonomous/robotstate.h"
#include "layer/abstraction/controllablerobot.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;

RobotState::RobotState(Abstraction::ControllableRobot &robot) :
	m_robot(robot),
	m_lastMovementState(false),
	m_currentMovementState(false)
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

bool RobotState::hasMovementStopped() const
{
	return m_lastMovementState && !m_currentMovementState;
}

bool RobotState::isEquivalentToDriveTo(const Pose &) const
{
	return false;
}

bool RobotState::isEquivalentToDriveToDirect(const Pose &) const
{
	return false;
}

void RobotState::update()
{
	m_lastMovementState = m_currentMovementState;
	m_currentMovementState = m_robot.isMoving();
	updateInternal();
}
