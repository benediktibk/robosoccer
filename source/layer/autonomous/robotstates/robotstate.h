#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_ROBOTSTATE_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_ROBOTSTATE_H

#include "common/logging/logger.h"
#include <string>
#include <vector>

namespace RoboSoccer
{
namespace Common
{
namespace Geometry
{
	class Point;
	class Pose;
}
namespace Routing
{
	class Route;
}
}
namespace Layer
{
namespace Abstraction
{
	class ControllableRobot;
}
namespace Autonomous
{
	class RobotState
	{
	public:
		RobotState(Abstraction::ControllableRobot &robot, Common::Logging::Logger &logger,
				   Common::Logging::Logger::LogFileType logFileType);
		virtual ~RobotState();

		virtual bool reachedTarget() const = 0;
		virtual RobotState* nextState(bool movementStopped) = 0;
		virtual bool isEquivalentToDriveTo(const std::vector<Common::Geometry::Pose> &targets) = 0;
		virtual bool isEquivalentToDriveToDirect(Common::Geometry::Pose const &target) = 0;
		virtual std::string getName() const = 0;
		virtual void update() = 0;
		virtual Common::Routing::Route getCurrentRoute() const;
		virtual std::vector<Common::Geometry::Pose> getCurrentTargets() const;

		Abstraction::ControllableRobot& getRobot();
		Abstraction::ControllableRobot const& getRobot() const;
		Common::Logging::Logger &getLogger();
		Common::Logging::Logger::LogFileType getLogFileType() const;

	protected:
		void log(std::string const &message);
		void log(std::string const &message, size_t value);

	private:
		//forbid copies
		RobotState(RobotState const &rhs) : m_robot(rhs.m_robot), m_logger(rhs.m_logger) { }
		void operator=(RobotState const&) { }

	private:
		Abstraction::ControllableRobot &m_robot;
		Common::Logging::Logger &m_logger;
		Common::Logging::Logger::LogFileType m_logFileType;
	};
}
}
}

#endif
