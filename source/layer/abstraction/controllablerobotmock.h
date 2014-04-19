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
		virtual Common::Geometry::OrientedPosition getPosition();
		virtual Common::Geometry::Circle createObstacle();
		virtual void gotoPositionImprecise(Common::Geometry::Point const &position);
		virtual void gotoPositionPrecise(Common::Geometry::Point const &position);
		virtual bool kick(unsigned int force, double distanceToBall);
		virtual void turn(Common::Geometry::Angle const &absoluteAngle);
	};
}
}
}

#endif


