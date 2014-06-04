#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_ROBOTSTATEDRIVETODIRECTFINALROTATION_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_ROBOTSTATEDRIVETODIRECTFINALROTATION_H

#include "layer/autonomous/robotstates/robotstate.h"
#include "common/geometry/pose.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Autonomous
{
	class DriveToDirectFinalRotation :
			public RobotState
	{
	public:
		DriveToDirectFinalRotation(
				Abstraction::ControllableRobot &robot,
				Common::Geometry::Pose const &target,
				Common::Logging::Logger &logger,
				Common::Logging::Logger::LogFileType logFileType);

		virtual bool reachedTarget() const;
		virtual bool cantReachTarget() const;
		virtual RobotState* nextState(bool movementStopped);
		virtual bool isEquivalentToDriveToDirect(const Common::Geometry::Pose &target) const;
		virtual bool isEquivalentToDriveTo(Common::Geometry::Pose const &target) const;
		virtual std::string getName() const;

	protected:
		virtual void updateInternal(bool movementStopped);

	private:
		const Common::Geometry::Pose m_target;
		const double m_precision;
		bool m_movementStarted;
	};
}
}
}

#endif