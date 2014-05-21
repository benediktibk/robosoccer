#include "layer/autonomous/robotstate.h"
#include "layer/abstraction/controllablerobot.h"
#include "common/logging/logger.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;
using namespace std;

RobotState::RobotState(Abstraction::ControllableRobot &robot, Logger &logger, Logger::LogFileType logFileType) :
	m_robot(robot),
	m_logger(logger),
	m_lastMovementState(false),
	m_currentMovementState(false),
	m_movementStopped(false),
	m_logFileType(logFileType)
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
		log("movement stopped");
	}
	else if (m_currentMovementState)
	{
		if (m_movementStopped)
			log("movement not stopped anymore");
		m_movementStopped = false;
	}
}

Logger& RobotState::getLogger()
{
	return m_logger;
}

void RobotState::log(const string &message)
{
	m_logger.logToLogFileOfType(Logger::LogFileTypeAutonomousRobotOne, message);
}

Logger::LogFileType RobotState::getLogFileType() const
{
	return m_logFileType;
}
