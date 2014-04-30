#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATEREACHEDTARGET_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATEREACHEDTARGET_H

#include "layer/autonomous/robotstate.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Autonomous
{
	class RobotStateReachedTarget :
			public RobotState
	{
	public:
		RobotStateReachedTarget(Abstraction::ControllableRobot &robot);

		virtual bool reachedTarget() const;
		virtual bool cantReachTarget() const;
		virtual RobotState* nextState();
		virtual bool isEquivalentToDriveTo(Common::Geometry::Point const &target) const;
		virtual void update();
	};
}
}
}

#endif