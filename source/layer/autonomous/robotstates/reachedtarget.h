#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_REACHEDTARGET_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_REACHEDTARGET_H

#include "layer/autonomous/robotstates/robotstate.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Autonomous
{
	class ReachedTarget :
			public RobotState
	{
	public:
		ReachedTarget(
				Abstraction::ControllableRobot &robot, Common::Logging::Logger &logger,
				Common::Logging::Logger::LogFileType logFileType);

		virtual bool reachedTarget() const;
		virtual RobotState* nextState(bool movementStopped);
		virtual bool isEquivalentToDriveTo(Common::Geometry::Pose const &target);
		virtual bool isEquivalentToDriveToDirect(Common::Geometry::Pose const &target);
		virtual std::string getName() const;
		virtual void update();

	private:
		bool isEquivalentToInternal(Common::Geometry::Pose const &target, double precisionPosition, double precisionOrientation);
	};
}
}
}

#endif
