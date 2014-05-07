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

		virtual void goTo(Common::Geometry::Pose const &position);
		virtual void stop();
		virtual Common::Geometry::Pose getCurrentPose() const;
		virtual Common::Geometry::Circle getObstacle() const;
		virtual bool targetReached() const;
		virtual bool cantReachTarget() const;
		virtual void kick(unsigned int force, IntelligentBall const &ball);
		virtual void update();
		virtual void measure();

		unsigned int getCallsToStop() const;
		unsigned int getCallsToGoTo() const;
		unsigned int getCallsToKick() const;
		void setTargetReached(bool value);

	private:
		unsigned int m_callsToStop;
		unsigned int m_callsToGoTo;
		unsigned int m_callsToKick;
		bool m_targetReached;
	};
}
}
}

#endif


