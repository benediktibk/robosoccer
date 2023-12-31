#ifndef ROBOSOCCER_LAYER_ABSTRACTION_CONTROLLABLEROBOT_H
#define ROBOSOCCER_LAYER_ABSTRACTION_CONTROLLABLEROBOT_H

#include "layer/abstraction/readablerobot.h"

namespace RoboSoccer
{
namespace Common
{
namespace Geometry
{
	class Point;
	class Angle;
}
}
namespace Layer
{
namespace Abstraction
{
	class ControllableRobot :
			public ReadableRobot
	{
	public:
		virtual ~ControllableRobot() {}

		virtual void gotoPositionImprecise(Common::Geometry::Point const &position) = 0;
		virtual void gotoPositionPrecise(Common::Geometry::Point const &position) = 0;
		virtual void kick(Common::Geometry::Point const &ballPosition) = 0;
		virtual void turn(Common::Geometry::Angle const &absoluteAngle) = 0;
		virtual void stop() = 0;
		virtual void updateActuators() = 0;
		virtual bool isMoving() const = 0;
	};
}
}
}

#endif


