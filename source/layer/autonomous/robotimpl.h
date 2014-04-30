#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTIMPL_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTIMPL_H

#include "layer/autonomous/robot.h"

namespace RoboSoccer
{
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
		RobotImpl(Abstraction::ControllableRobot &robot);
		virtual ~RobotImpl();

		virtual void goTo(Common::Geometry::Point const &position);
		virtual void stop();
		virtual Common::Geometry::Pose getCurrentPose() const;
		virtual bool targetReached() const;
		virtual bool kick(unsigned int force, IntelligentBall const &ball);
		virtual void update();

	private:
		void switchIntoState(RobotState *state);

	private:
		Abstraction::ControllableRobot &m_robot;
		RobotState *m_currentState;
	};
}
}
}

#endif


