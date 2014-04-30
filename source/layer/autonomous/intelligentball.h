#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_INTELLIGENTBALL_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_INTELLIGENTBALL_H

#include "layer/abstraction/fieldside.h"

namespace RoboSoccer
{
namespace Common
{
namespace Geometry
{
	class Angle;
	class Circle;
	class Point;
}
}
namespace Layer
{
namespace Abstraction
{
	class Ball;
}
namespace Autonomous
{
	class IntelligentBall
	{
	public:
		virtual ~IntelligentBall() { }

		virtual Common::Geometry::Angle getRotation() const = 0;
		virtual Common::Geometry::Circle getObstacle() const = 0;
		virtual Common::Geometry::Point getPosition() const = 0;
		virtual double getVelocity() const = 0;
		virtual bool isMoving() const = 0;
		virtual Abstraction::FieldSide getMovingDirection() const = 0;
		virtual Abstraction::FieldSide getCurrentFieldSide() const = 0;
	};
}
}
}
#endif
