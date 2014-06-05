#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_DRIVETODRIVING_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_DRIVETODRIVING_H

#include "layer/autonomous/robotstates/driveto.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Autonomous
{
	class DriveToDriving :
			public DriveTo
	{
	public:
		DriveToDriving(
				Abstraction::ControllableRobot &robot,
				const Common::Geometry::Pose &target,
				const Common::Routing::Router &router,
				Common::Logging::Logger &logger, Common::Logging::Logger::LogFileType logFileType,
				ObstacleFetcher const &obstacleFetcher, ObstacleSource const &ownObstacleSource,
				bool ignoreBall, bool driveSlowlyAtTheEnd, bool ignoreGoalObstacles);
		DriveToDriving(
				Abstraction::ControllableRobot &robot,
				const Common::Geometry::Pose &target,
				const Common::Routing::Router &router,
				Common::Logging::Logger &logger, Common::Logging::Logger::LogFileType logFileType,
				ObstacleFetcher const &obstacleFetcher, ObstacleSource const &ownObstacleSource,
				bool ignoreBall, bool driveSlowlyAtTheEnd, bool ignoreGoalObstacles,
				const Common::Routing::Route &oldRoute);

		virtual RobotState* nextState(bool movementStopped);
		virtual std::string getName() const;
		virtual void update();

	private:
		bool m_movementStarted;
	};
}
}
}

#endif