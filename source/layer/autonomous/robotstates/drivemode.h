#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_DRIVEMODE_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_DRIVEMODE_H

#include <ostream>

namespace RoboSoccer
{
namespace Layer
{
namespace Autonomous
{
	enum DriveMode
	{
		DriveModeIgnoreBall,
		DriveModeDriveSlowlyAtTheEnd,
		DriveModeIgnoreGoalObstacles,
		DriveModeIgnoreBallAndDriveSlowlyAtTheEnd,
		DriveModeIgnoreBallAndIgnoreGoalObstacles,
		DriveMoveDefault
	};
}
}
}

std::ostream& operator<<(std::ostream &stream, const RoboSoccer::Layer::Autonomous::DriveMode &driveMode);

#endif


