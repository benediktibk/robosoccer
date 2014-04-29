#ifndef ROBOSOCCER_LAYER_ABSTRACTION_CONTROLLABLEROBOTMOCK_H
#define ROBOSOCCER_LAYER_ABSTRACTION_CONTROLLABLEROBOTMOCK_H

#include "layer/abstraction/controllablerobot.h"

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
		virtual Common::Geometry::Circle createObstacle() const;
		virtual void gotoPositionImprecise(const Common::Geometry::Point &position);
		virtual void gotoPositionPrecise(Common::Geometry::Point const &position);
		virtual bool kick(unsigned int force);
		virtual void turn(Common::Geometry::Angle const &absoluteAngle);
		virtual void stop();

		unsigned int getCallsToStop() const;

	private:
		unsigned int m_callsToStop;
	};
}
}
}

#endif


