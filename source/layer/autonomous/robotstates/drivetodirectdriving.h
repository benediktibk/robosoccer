#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_DRIVETODIRECTDRIVING_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_DRIVETODIRECTDRIVING_H

#include "layer/autonomous/robotstates/drivetodirect.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Autonomous
{
	class DriveToDirectDriving :
			public DriveToDirect
	{
	public:
		DriveToDirectDriving(
				Abstraction::ControllableRobot &robot,
				Common::Geometry::Pose const &target,
				Common::Logging::Logger &logger,
				Common::Logging::Logger::LogFileType logFileType);

		virtual RobotState* nextState(bool movementStopped);
		virtual std::string getName() const;

	protected:
		virtual void updateInternal();
	};
}
}
}

#endif