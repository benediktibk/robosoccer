#ifndef ROBOSOCCER_LAYER_ABSTRACTION_CONTROLLABLEROBOTMOCK_H
#define ROBOSOCCER_LAYER_ABSTRACTION_CONTROLLABLEROBOTMOCK_H

#include "layer/abstraction/controllablerobot.h"
#include "common/geometry/pose.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Abstraction
{
	class ControllableRobotMock :
			public ControllableRobot
	{
	public:
		ControllableRobotMock();

		virtual Common::Geometry::Pose getPose() const;
		virtual Common::Geometry::Pose getPoseRaw() const;
		virtual Common::Geometry::Circle getObstacle() const;
		virtual void gotoPositionImprecise(const Common::Geometry::Point &position);
		virtual void gotoPositionPrecise(Common::Geometry::Point const &position);
		virtual void kick(Common::Geometry::Point const &ballPosition);
		virtual void turn(Common::Geometry::Angle const &absoluteAngle);
		virtual void stop();
		virtual void updateSensors();
		virtual bool isMoving() const;

		unsigned int getCallsToStop() const;
		unsigned int getCallsToGoToPositionImprecise() const;
		unsigned int getCallsToGoToPositionPrecise() const;
		unsigned int getCallsToGoToCombined() const;
		unsigned int getCallsToTurn() const;
		unsigned int getCallsToKick() const;
		unsigned int getCallsToUpdate() const;
		Common::Geometry::Angle const& getLastAngleToTurnTo() const;
		Common::Geometry::Point const& getLastPointToDriveTo() const;
		void setPose(Common::Geometry::Pose const &pose);
		void setIsMoving(bool value);
		void setObstacle(Common::Geometry::Circle const &obstacle);

	private:
		unsigned int m_callsToStop;
		unsigned int m_callsToGoToPositionImprecise;
		unsigned int m_callsToGoToPositionPrecise;
		unsigned int m_callsToTurn;
		unsigned int m_callsToKick;
		unsigned int m_callsToUpdate;
		Common::Geometry::Pose m_pose;
		Common::Geometry::Angle m_lastAngleToTurnTo;
		Common::Geometry::Point m_lastPointToDriveTo;
		bool m_isMoving;
	};
}
}
}

#endif


