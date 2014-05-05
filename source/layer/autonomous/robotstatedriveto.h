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
				Abstraction::ControllableRobot &robot,
				Common::Geometry::Point const &target);

		virtual bool reachedTarget() const;
		virtual bool cantReachTarget() const;
		virtual RobotState* nextState();
		virtual bool isEquivalentToDriveTo(Common::Geometry::Point const &target) const;
		virtual void update();

	private:
		bool m_currentTargetValid;
		Common::Geometry::Point m_target;
	};
}
}
}

#endif