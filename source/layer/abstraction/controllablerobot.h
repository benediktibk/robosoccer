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
		virtual bool kick(unsigned int force) = 0;
		virtual void turn(Common::Geometry::Angle const &absoluteAngle) = 0;
		virtual void drive(Common::Geometry::Point const &targetPoint) = 0;
		virtual void stop() = 0;
		virtual void update() = 0;
		virtual void measure() = 0;
	};
}
}
}

#endif


