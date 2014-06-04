#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_ROBOTSTATEKICK_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_ROBOTSTATEKICK_H

#include "layer/autonomous/robotstates/robotstate.h"

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

	class Kick :
			public RobotState
	{
	public:
		Kick(
				Abstraction::ControllableRobot &robot, IntelligentBall const &ball,
				Common::Time::Watch const &watch, Common::Logging::Logger &logger,
				Common::Logging::Logger::LogFileType logFileType);
		virtual ~Kick();

		virtual bool reachedTarget() const;
		virtual bool cantReachTarget() const;
		virtual bool isEquivalentToDriveTo(Common::Geometry::Pose const &target) const;
		virtual bool isEquivalentToDriveToDirect(Common::Geometry::Pose const &target) const;
		virtual RobotState* nextState(bool movementStopped);
		virtual std::string getName() const;

	protected:
		virtual void updateInternal(bool movementStopped);

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
