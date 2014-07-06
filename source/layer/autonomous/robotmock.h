#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTMOCK_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOTMOCK_H

#include "layer/autonomous/robot.h"
#include "common/geometry/pose.h"

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

		virtual void goTo(std::vector<Common::Geometry::Pose> const &positions, DriveMode driveMode);
		virtual void goToDirect(Common::Geometry::Pose const &position);
		virtual void stop();
		virtual Common::Geometry::Pose getCurrentPose() const;
		virtual Common::Geometry::Circle getObstacle() const;
		virtual std::vector<Common::Geometry::Circle> getObstacles() const;
		virtual bool reachedTarget() const;
		virtual void kick(IntelligentBall const &ball);
		virtual void updateSensors();
		virtual void updateActuators();
		virtual Common::Routing::Route getCurrentRoute() const;
		virtual std::vector<Common::Geometry::Pose> getCurrentTargets() const;

		unsigned int getCallsToStop() const;
		unsigned int getCallsToGoTo() const;
		unsigned int getCallsToGoToDirect() const;
		unsigned int getCallsToGoToCombined() const;
		unsigned int getCallsToKick() const;
		DriveMode getLastGoToDriveMode() const;
		void setTargetReached(bool value);
		void setObstacle(Common::Geometry::Circle const &obstacle);
		void setCurrentPose(Common::Geometry::Pose const &pose);

	private:
		unsigned int m_callsToStop;
		unsigned int m_callsToGoTo;
		unsigned int m_callsToGoToDirect;
		unsigned int m_callsToKick;
		DriveMode m_lastGoToDriveMode;
		bool m_targetReached;
		Common::Geometry::Circle m_obstacle;
		Common::Geometry::Pose m_pose;
	};
}
}
}

#endif


