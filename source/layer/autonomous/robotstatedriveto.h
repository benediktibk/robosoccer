#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATEDRIVETO_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATEDRIVETO_H

#include "layer/autonomous/robotstate.h"
#include "common/geometry/point.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Autonomous
{
	class RobotStateDriveTo :
			public RobotState
	{
	public:
		RobotStateDriveTo(
				Abstraction::ControllableRobot &robot, Common::Geometry::Point const &target,
				RobotState *followingState, bool precise);
		virtual ~RobotStateDriveTo();

		virtual bool reachedTarget() const;
		virtual bool cantReachTarget() const;
		virtual RobotState* nextState();
		virtual void update();

	private:
		Common::Geometry::Point const &m_target;
		RobotState *m_followingState;
		bool m_precise;
	};
}
}
}

#endif