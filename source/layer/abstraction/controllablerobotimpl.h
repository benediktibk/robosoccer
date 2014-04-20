#ifndef ROBOSOCCER_LAYER_ABSTRACTION_CONTROLLABLEROBOTIMPL_H
#define ROBOSOCCER_LAYER_ABSTRACTION_CONTROLLABLEROBOTIMPL_H

#include "layer/abstraction/controllablerobot.h"

namespace RoboSoccer
{
namespace Layer
{
namespace Abstraction
{
	class ControllableRobotImpl :
			public ControllableRobot
	{
	public:
		ControllableRobotImpl();

		virtual Common::Geometry::OrientedPosition getPosition();
		virtual Common::Geometry::Circle createObstacle();
		virtual void gotoPositionImprecise(Common::Geometry::Point const &position);
		virtual void gotoPositionPrecise(Common::Geometry::Point const &position);
		virtual bool kick(unsigned int force, double distanceToBall);
		virtual void turn(Common::Geometry::Angle const &absoluteAngle);

	private:
	};
}
}
}

#endif

