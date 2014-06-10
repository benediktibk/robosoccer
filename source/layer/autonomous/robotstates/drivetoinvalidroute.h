#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_DRIVETOINVALIDROUTE_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_DRIVETOINVALIDROUTE_H

#include "layer/autonomous/robotstates/driveto.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Autonomous
{
	class DriveToInvalidRoute :
			public DriveTo
	{
	public:
		DriveToInvalidRoute(
				Abstraction::ControllableRobot &robot,
				const std::vector<Common::Geometry::Pose> &targets,
				const Common::Geometry::Pose &currentTarget,
				const Common::Routing::Router &router,
				Common::Logging::Logger &logger, Common::Logging::Logger::LogFileType logFileType,
				ObstacleFetcher const &obstacleFetcher, ObstacleSource const &ownObstacleSource, DriveMode driveMode);

		virtual RobotState* nextState(bool movementStopped);
		virtual std::string getName() const;
		virtual void update();
	};
}
}
}

#endif
