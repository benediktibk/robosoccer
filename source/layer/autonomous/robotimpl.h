#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTIMPL_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTIMPL_H

#include "layer/autonomous/robot.h"
#include "common/logging/logger.h"
#include <string>

namespace RoboSoccer
{
namespace Common
{
namespace Time
{
	class Watch;
}
namespace Routing
{
	class Router;
	class Route;
}
namespace Geometry
{
	class Point;
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
	class RobotState;

	class RobotImpl :
			public Robot
	{
	public:
		RobotImpl(Abstraction::ControllableRobot &robot, const Common::Routing::Router &router,
				  Common::Time::Watch const &watch, Common::Logging::Logger &logger, unsigned int robotIndex);
		virtual ~RobotImpl();

		virtual void goTo(Common::Geometry::Pose const &position);
		virtual void goToDirect(Common::Geometry::Pose const &position);
		virtual void stop();
		virtual Common::Geometry::Pose getCurrentPose() const;
		virtual Common::Geometry::Circle getObstacle() const;
		virtual bool targetReached() const;
		virtual bool cantReachTarget() const;
		virtual void kick(unsigned int force, IntelligentBall const &ball);
		virtual void update();

	private:
		void switchIntoState(RobotState *state);
		void log(std::string const &message);
		void logPosition(std::string const &message, Common::Geometry::Point const &position);

	private:
		Abstraction::ControllableRobot &m_robot;
		Common::Routing::Router const &m_router;
		Common::Time::Watch const &m_watch;
		Common::Logging::Logger &m_logger;
		Common::Routing::Route *m_currentRoute;
		RobotState *m_currentState;
		Common::Logging::Logger::LogFileType m_logFileType;
	};
}
}
}

#endif


