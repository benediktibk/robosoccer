#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATETURNTO_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATETURNTO_H

#include "layer/autonomous/robotstate.h"
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
				Common::Time::Watch const &watch, RobotState *followingState);
		virtual ~RobotStateTurnTo();

		virtual bool reachedTarget() const;
		virtual bool cantReachTarget() const;
		virtual RobotState* nextState();
		virtual void update();
		virtual std::string getName() const;

	private:
		Common::Geometry::Angle calculateTargetOrientation() const;

	private:
		Common::Geometry::Point m_target;
		RobotState *m_followingState;
		bool m_targetAlreadySet;
		Common::Time::StopWatch *m_watchDog;
	};
}
}
}

#endif
