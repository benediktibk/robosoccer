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
		virtual void goToDirect(Common::Geometry::Pose const &position);
		virtual void stop();
		virtual Common::Geometry::Pose getCurrentPose() const;
		virtual Common::Geometry::Circle getObstacle() const;
		virtual std::vector<Common::Geometry::Circle> getObstacles() const;
		virtual bool targetReached() const;
		virtual bool cantReachTarget() const;
		virtual void kick(IntelligentBall const &ball);
		virtual void update();

		unsigned int getCallsToStop() const;
		unsigned int getCallsToGoTo() const;
		unsigned int getCallsToGoToDirect() const;
		unsigned int getCallsToGoToCombined() const;
		unsigned int getCallsToKick() const;
		void setTargetReached(bool value);
		void setObstacle(Common::Geometry::Circle const &obstacle);

	private:
		unsigned int m_callsToStop;
		unsigned int m_callsToGoTo;
		unsigned int m_callsToGoToDirect;
		unsigned int m_callsToKick;
		bool m_targetReached;
		Common::Geometry::Circle m_obstacle;
	};
}
}
}

#endif


