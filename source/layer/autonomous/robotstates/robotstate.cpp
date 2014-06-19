#include "layer/autonomous/robotstates/robotstate.h"
#include "layer/abstraction/controllablerobot.h"
#include "common/logging/logger.h"
#include "common/geometry/pose.h"
#include "common/routing/route.h"
#include <sstream>
#include <string>

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::Routing;
using namespace std;

RobotState::RobotState(Abstraction::ControllableRobot &robot, Logger &logger, Logger::LogFileType logFileType) :
	m_robot(robot),
	m_logger(logger),
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

Logger& RobotState::getLogger()
{
	return m_logger;
}

void RobotState::log(const string &message)
{
	m_logger.logToLogFileOfType(m_logFileType, message);
}

void RobotState::log(const string &message, size_t value)
{
	stringstream stream;
	stream << message << ": " << value;
	log(stream.str());
}

Logger::LogFileType RobotState::getLogFileType() const
{
	return m_logFileType;
}

Route RobotState::getCurrentRoute() const
{
	Route route(ControllableRobot::getWidth());
	Pose pose = m_robot.getPose();
	route.addPoint(pose.getPosition());
	return route;
}
