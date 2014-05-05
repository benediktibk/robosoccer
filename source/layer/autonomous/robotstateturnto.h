#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATETURNTO_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATETURNTO_H

#include "layer/autonomous/robotstate.h"
#include "common/geometry/point.h"

namespace RoboSoccer
{
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
				RobotState *followingState);
		virtual ~RobotStateTurnTo();

		virtual bool reachedTarget() const;
		virtual bool cantReachTarget() const;
		virtual RobotState* nextState();
		virtual bool isEquivalentToDriveTo(Common::Geometry::Point const &target) const;
		virtual void update();

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
