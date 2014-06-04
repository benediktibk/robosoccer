#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_ROBOTSTATEREACHEDTARGET_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_ROBOTSTATEREACHEDTARGET_H

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
		virtual bool cantReachTarget() const;
		virtual RobotState* nextState(bool movementStopped);
		virtual bool isEquivalentToDriveTo(Common::Geometry::Pose const &target) const;
		virtual bool isEquivalentToDriveToDirect(Common::Geometry::Pose const &target) const;
		virtual std::string getName() const;

	protected:
		virtual void updateInternal(bool movementStopped);
	};
}
}
}

#endif
