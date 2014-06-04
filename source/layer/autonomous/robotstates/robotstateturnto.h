#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_ROBOTSTATETURNTO_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_ROBOTSTATETURNTO_H

#include "layer/autonomous/robotstates/robotstate.h"
#include "common/geometry/point.h"

namespace RoboSoccer
{
namespace Common
{
namespace Time
{
	class Watch;
	class StopWatch;
}
}
namespace Layer
{
namespace Autonomous
{
	class RobotStateTurnTo :
			public RobotState
	{
	public:
		RobotStateTurnTo(
				Abstraction::ControllableRobot &robot, Common::Geometry::Point const &target,
				RobotState *followingState, Common::Logging::Logger &logger,
				Common::Logging::Logger::LogFileType logFileType);
		virtual ~RobotStateTurnTo();

		virtual bool reachedTarget() const;
		virtual bool cantReachTarget() const;
		virtual bool isEquivalentToDriveTo(Common::Geometry::Pose const &target) const;
		virtual bool isEquivalentToDriveToDirect(Common::Geometry::Pose const &target) const;
		virtual RobotState* nextState(bool movementStopped);
		virtual std::string getName() const;

	protected:
		virtual void updateInternal(bool movementStopped);

	private:
		Common::Geometry::Angle calculateTargetOrientation() const;

	private:
		Common::Geometry::Point m_target;
		RobotState *m_followingState;
		bool m_targetAlreadySet;
	};
}
}
}

#endif
