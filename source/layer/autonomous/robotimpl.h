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
	class ObstacleFetcher;

	class RobotImpl :
			public Robot
	{
	public:
		RobotImpl(Abstraction::ControllableRobot &robot, const Common::Routing::Router &router,
				  Common::Time::Watch const &watch, Common::Logging::Logger &logger, unsigned int robotIndex,
				  ObstacleFetcher &obstacleFetcher);
		virtual ~RobotImpl();

		virtual void goTo(std::vector<Common::Geometry::Pose> const &position, DriveMode driveMode);
		virtual void goToDirect(Common::Geometry::Pose const &position);
		virtual void stop();
		virtual Common::Geometry::Pose getCurrentPose() const;
		virtual Common::Geometry::Circle getObstacle() const;
		virtual std::vector<Common::Geometry::Circle> getObstacles() const;
		virtual bool reachedTarget() const;
		virtual void kick(IntelligentBall const &ball);
		virtual void update();

		RobotState const& getCurrentState() const;
		bool movementStopped() const;

	private:
		void switchIntoState(RobotState *state);
		void log(std::string const &message);
		void logPositions(std::string const &message, std::vector<Common::Geometry::Pose> const &positions);
		void logPosition(std::string const &message, Common::Geometry::Point const &position);
		void updateMovementStopped();

	private:
		Abstraction::ControllableRobot &m_robot;
		Common::Routing::Router const &m_router;
		Common::Time::Watch const &m_watch;
		Common::Logging::Logger &m_logger;
		RobotState *m_currentState;
		Common::Logging::Logger::LogFileType m_logFileType;
		ObstacleFetcher &m_obstacleFetcher;
		bool m_lastMovementState;
		bool m_currentMovementState;
		bool m_movementStopped;
	};
}
}
}

#endif


