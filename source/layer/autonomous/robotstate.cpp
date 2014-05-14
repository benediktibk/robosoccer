#include "layer/autonomous/robotstate.h"
#include "layer/abstraction/controllablerobot.h"
#include "common/logging/logger.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;

RobotState::RobotState(Abstraction::ControllableRobot &robot, Logger &logger) :
	m_robot(robot),
	m_logger(logger),
	m_lastMovementState(false),
	m_currentMovementState(false),
	m_movementStopped(false)
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
	return m_movementStopped;
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
	updateMovementStopped();
	updateInternal();
}

void RobotState::updateMovementStopped()
{
	m_lastMovementState = m_currentMovementState;
	m_currentMovementState = m_robot.isMoving();
	if (m_lastMovementState && !m_currentMovementState)
	{
		m_movementStopped = true;
		m_logger.logToLogFileOfType(Logger::LogFileTypeRobot, "movement stopped");
	}
	else if (m_currentMovementState)
	{
		m_movementStopped = false;
		m_logger.logToLogFileOfType(Logger::LogFileTypeRobot, "movement not stopped anymore");
	}
}

Logger& RobotState::getLogger()
{
	return m_logger;
}
