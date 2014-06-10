#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_DRIVETODIRECTFINALROTATION_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_DRIVETODIRECTFINALROTATION_H

#include "layer/autonomous/robotstates/drivetodirect.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Autonomous
{
	class DriveToDirectFinalRotation :
			public DriveToDirect
	{
	public:
		DriveToDirectFinalRotation(
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