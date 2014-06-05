#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_DRIVETOINITIALROTATION_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_DRIVETOINITIALROTATION_H

#include "layer/autonomous/robotstates/driveto.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Autonomous
{
	class DriveToInitialRotation :
			public DriveTo
	{
	public:
		DriveToInitialRotation(
				Abstraction::ControllableRobot &robot,
				const Common::Geometry::Pose &target,
				const Common::Routing::Router &router,
				Common::Logging::Logger &logger, Common::Logging::Logger::LogFileType logFileType,
				ObstacleFetcher const &obstacleFetcher, ObstacleSource const &ownObstacleSource,
				bool ignoreBall, bool driveSlowlyAtTheEnd, bool ignoreGoalObstacles);
		DriveToInitialRotation(
				Abstraction::ControllableRobot &robot,
				const Common::Geometry::Pose &target,
				const Common::Routing::Router &router,
				Common::Logging::Logger &logger, Common::Logging::Logger::LogFileType logFileType,
				ObstacleFetcher const &obstacleFetcher, ObstacleSource const &ownObstacleSource,
				bool ignoreBall, bool driveSlowlyAtTheEnd, bool ignoreGoalObstacles,
				Common::Routing::Route oldRoute);

		virtual RobotState* nextState(bool movementStopped);
		virtual std::string getName() const;
		virtual void update();
		Common::Geometry::Angle calculateTargetOrientation(Common::Routing::Route const &currentRoute) const;

	private:
		bool m_movementStarted;
	};
}
}
}

#endif