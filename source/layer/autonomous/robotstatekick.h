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
	class IntelligentBall;

	class RobotStateKick :
			public RobotState
	{
	public:
		RobotStateKick(
				Abstraction::ControllableRobot &robot, IntelligentBall const &ball,
				Common::Time::Watch const &watch, Common::Logging::Logger &logger,
				Common::Logging::Logger::LogFileType logFileType);
		virtual ~RobotStateKick();

		virtual bool reachedTarget() const;
		virtual bool cantReachTarget() const;
		virtual RobotState* nextState();
		virtual std::string getName() const;

	protected:
		virtual void updateInternal();

	private:
		Common::Time::StopWatch *m_stopWatch;
		IntelligentBall const &m_ball;
		bool m_alreadyKicked;
		bool m_stopWatchRestarted;
	};
}
}
}

#endif
