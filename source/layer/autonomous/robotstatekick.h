#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATEKICK_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATEKICK_H

#include "layer/autonomous/robotstate.h"

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
	class RobotStateKick :
			public RobotState
	{
	public:
		RobotStateKick(Abstraction::ControllableRobot &robot, unsigned int force, Common::Time::Watch const &watch);
		virtual ~RobotStateKick();

		virtual bool reachedTarget() const;
		virtual bool cantReachTarget() const;
		virtual RobotState* nextState();
		virtual std::string getName() const;

	protected:
		virtual void updateInternal();

	private:
		Common::Time::StopWatch *m_stopWatch;
		unsigned int m_force;
		bool m_alreadyKicked;
		bool m_stopWatchRestarted;
	};
}
}
}

#endif
