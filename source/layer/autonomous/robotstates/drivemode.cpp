#include "layer/autonomous/robotstates/drivemode.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace std;

ostream& operator<<(ostream &stream, const DriveMode &driveMode)
{
	stream << "drive Mode: ";
	switch(driveMode)
	{
	case DriveModeIgnoreAllObstacles:
		stream << "ignore all Obstacles";
	case DriveModeIgnoreBall:
		stream << "ignore Ball";
		break;
	case DriveModeDriveSlowlyAtTheEnd:
		stream << "drive slowly at the end";
		break;
	case DriveModeIgnoreBallAndDriveSlowlyAtTheEnd:
		stream << "ignore ball and drive slowly at the end";
		break;
	case DriveModeIgnoreGoalObstacles:
		stream << "ignore goal obstacles";
		break;
	case DriveModeDefault:
		stream << "default";
		break;
	}

	return stream;
}
