#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATEDRIVETODIRECT_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATEDRIVETODIRECT_H

#include "layer/autonomous/robotstate.h"
#include "common/geometry/pose.h"

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
	class RobotStateDriveToDirect :
			public RobotState
	{
	public:
		RobotStateDriveToDirect(
				Abstraction::ControllableRobot &robot,
				Common::Geometry::Pose const &target,
				Common::Time::Watch const &watch);
		virtual ~RobotStateDriveToDirect();

		virtual bool reachedTarget() const;
		virtual bool cantReachTarget() const;
		virtual RobotState* nextState();
		virtual bool isEquivalentToDriveToDirect(const Common::Geometry::Pose &target) const;
		virtual void update();
		virtual std::string getName() const;

	private:
		bool m_initialRotationReached;
		bool m_initialRotationStarted;
		bool m_positionReached;
		bool m_driveStarted;
		bool m_finalRotationReached;
		bool m_finalRotationStarted;
		Common::Geometry::Pose m_target;
		Common::Time::StopWatch *m_watchDog;
	};
}
}
}

#endif
