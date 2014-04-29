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
	class RobotImpl :
			public Robot
	{
	public:
		RobotImpl(Abstraction::ControllableRobot &robot);
		virtual ~RobotImpl();

		virtual void goTo(Common::Geometry::Point const &position);
		virtual void stop();
		virtual Common::Geometry::Pose getCurrentPose() const;

	private:
		Abstraction::ControllableRobot &m_robot;
	};
}
}
}

#endif


