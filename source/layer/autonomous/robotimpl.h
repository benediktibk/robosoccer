#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTIMPL_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTIMPL_H

#include "layer/autonomous/robot.h"

namespace RoboSoccer
{
namespace Common
{
namespace Time
{
	class Watch;
}
namespace Logging
{
	class Logger;
}
}
namespace Layer
{
namespace Abstraction
{
	class ControllableRobot;
}

namespace Autonomous
{
	class RobotState;

	class RobotImpl :
			public Robot
	{
	public:
		RobotImpl(Abstraction::ControllableRobot &robot, Common::Time::Watch const &watch, Common::Logging::Logger &logger);
		virtual ~RobotImpl();

		virtual void goTo(Common::Geometry::Point const &position);
		virtual void stop();
		virtual Common::Geometry::Pose getCurrentPose() const;
		virtual bool targetReached() const;
		virtual bool cantReachTarget() const;
		virtual void kick(unsigned int force, IntelligentBall const &ball);
		virtual void update();

	private:
		void switchIntoState(RobotState *state);

	private:
		Abstraction::ControllableRobot &m_robot;
		Common::Time::Watch const &m_watch;
		Common::Logging::Logger &m_logger;
		RobotState *m_currentState;
	};
}
}
}

#endif


