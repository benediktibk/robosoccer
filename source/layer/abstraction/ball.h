#ifndef ROBOSOCCER_LAYER_ABSTRACTION_BALL_H
#define ROBOSOCCER_LAYER_ABSTRACTION_BALL_H

#include "layer/abstraction/fieldside.h"

namespace RoboSoccer
{
namespace Common
{
namespace Geometry
{
	class Point;
	class Circle;
	class Angle;
}
}
namespace Layer
{
namespace Abstraction
{
	class Ball
	{
	public:
		virtual ~Ball() {}

		virtual Common::Geometry::Point getPosition() const = 0;
		virtual Common::Geometry::Circle getObstacle() const = 0;
		virtual bool isMoving() const = 0;
		virtual Common::Geometry::Angle getDirection() const = 0;
		virtual FieldSide getMovingDirection() const = 0;
	};
}
}
}

#endif


