#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_KICK_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTSTATES_KICK_H

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
		virtual bool isEquivalentToDriveTo(Common::Geometry::Pose const &target);
		virtual bool isEquivalentToDriveToDirect(Common::Geometry::Pose const &target);
		virtual RobotState* nextState(bool movementStopped);
		virtual std::string getName() const;
		virtual void update();

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
