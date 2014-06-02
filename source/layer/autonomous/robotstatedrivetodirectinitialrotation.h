#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATEDRIVETODIRECTINITIALROTATION_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATEDRIVETODIRECTINITIALROTATION_H

#include "layer/autonomous/robotstate.h"
#include "common/geometry/pose.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Autonomous
{
	class RobotStateDriveToDirectInitialRotation :
			public RobotState
	{
	public:
		RobotStateDriveToDirectInitialRotation(
				Abstraction::ControllableRobot &robot,
				Common::Geometry::Pose const &target,
				Common::Logging::Logger &logger,
				Common::Logging::Logger::LogFileType logFileType);

		virtual bool reachedTarget() const;
		virtual bool cantReachTarget() const;
		virtual RobotState* nextState();
		virtual bool isEquivalentToDriveToDirect(const Common::Geometry::Pose &target) const;
		virtual bool isEquivalentToDriveTo(Common::Geometry::Pose const &target) const;
		virtual std::string getName() const;

	protected:
		virtual void updateInternal();

	private:
		Common::Geometry::Pose const m_target;

	};
}
}
}

#endif