#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_DRIVETOFINALROTATION_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_DRIVETOFINALROTATION_H

#include "layer/autonomous/robotstates/driveto.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Autonomous
{
	class DriveToFinalRotation :
			public DriveTo
	{
	public:
		DriveToFinalRotation(
				Abstraction::ControllableRobot &robot,
				const std::vector<Common::Geometry::Pose> &targets,
				const Common::Routing::Router &router,
				Common::Logging::Logger &logger, Common::Logging::Logger::LogFileType logFileType,
				ObstacleFetcher const &obstacleFetcher, ObstacleSource const &ownObstacleSource,
				DriveMode driveMode, const Common::Routing::Route &oldRoute);

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
