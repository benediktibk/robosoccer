#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTMOCK_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTMOCK_H

#include "layer/autonomous/robot.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Autonomous
{
	class RobotMock :
			public Robot
	{
	public:
		RobotMock();
		virtual ~RobotMock();

		virtual void goTo(Common::Geometry::Point const &position);
		virtual void stop();
		virtual Common::Geometry::Pose getCurrentPose() const;
		virtual bool targetReached() const;
		virtual bool kick(unsigned int force, IntelligentBall const &ball);
		virtual void update();
	};
}
}
}

#endif


