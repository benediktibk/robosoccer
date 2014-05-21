#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATE_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATE_H

#include "common/logging/logger.h"
#include <string>

namespace RoboSoccer
{
namespace Common
{
namespace Geometry
{
	class Point;
	class Pose;
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
		virtual bool cantReachTarget() const = 0;
		virtual RobotState* nextState() = 0;
		virtual bool isEquivalentToDriveTo(Common::Geometry::Pose const &target) const;
		virtual bool isEquivalentToDriveToDirect(Common::Geometry::Pose const &target) const;
		virtual std::string getName() const = 0;

		void update();
		Abstraction::ControllableRobot& getRobot();
		Abstraction::ControllableRobot const& getRobot() const;
		Common::Logging::Logger &getLogger();
		Common::Logging::Logger::LogFileType getLogFileType() const;
		bool hasMovementStopped() const;

	protected:
		virtual void updateInternal() = 0;
		void log(std::string const &message);
		void log(std::string const &message, size_t value);

	private:
		void updateMovementStopped();

	private:
		//forbid copies
		RobotState(RobotState const &rhs) : m_robot(rhs.m_robot), m_logger(rhs.m_logger) { }
		void operator=(RobotState const&) { }

	private:
		Abstraction::ControllableRobot &m_robot;
		Common::Logging::Logger &m_logger;
		bool m_lastMovementState;
		bool m_currentMovementState;
		bool m_movementStopped;
		Common::Logging::Logger::LogFileType m_logFileType;
	};
}
}
}

#endif
