#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATEDRIVETO_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATEDRIVETO_H

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
	class RobotStateDriveTo :
			public RobotState
	{
	public:
		RobotStateDriveTo(Abstraction::ControllableRobot &robot,
				const Common::Geometry::Pose &target,
				Common::Time::Watch const &watch);
		virtual ~RobotStateDriveTo();

		virtual bool reachedTarget() const;
		virtual bool cantReachTarget() const;
		virtual RobotState* nextState();
		virtual bool isEquivalentToDriveTo(Common::Geometry::Pose const &target) const;
		virtual std::string getName() const;

	protected:
		virtual void updateInternal();

	private:
		const double m_precisionPosition;
		const double m_precisionOrientation;
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
