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
		virtual Common::Geometry::Circle getObstacle() const;
		virtual void gotoPositionImprecise(const Common::Geometry::Point &position);
		virtual void gotoPositionPrecise(Common::Geometry::Point const &position);
		virtual bool kick(unsigned int force);
		virtual void turn(Common::Geometry::Angle const &absoluteAngle);
		virtual void drive(Common::Geometry::Point const &targetPoint);
		virtual void stop();
		virtual void update();
		virtual void measure();

		unsigned int getCallsToStop() const;
		unsigned int getCallsToGoToPositionImprecise() const;
		unsigned int getCallsToGoToPositionPrecise() const;
		unsigned int getCallsToTurn() const;
		unsigned int getCallsToDrive() const;
		unsigned int getCallsToKick() const;
		unsigned int getCallsToUpdate() const;
		unsigned int getCallsToMeasure() const;
		Common::Geometry::Angle const& getLastAngleToTurnTo() const;
		void setPose(Common::Geometry::Pose const &pose);

	private:
		unsigned int m_callsToStop;
		unsigned int m_callsToGoToPositionImprecise;
		unsigned int m_callsToGoToPositionPrecise;
		unsigned int m_callsToTurn;
		unsigned int m_callsToKick;
		unsigned int m_callsToUpdate;
		unsigned int m_callsToDrive;
		unsigned int m_callsToMeasure;
		Common::Geometry::Pose m_pose;
		Common::Geometry::Angle m_lastAngleToTurnTo;
		Common::Geometry::Point m_lastPointToDriveTo;
	};
}
}
}

#endif


