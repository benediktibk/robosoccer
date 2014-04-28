#ifndef ROBOSOCCER_LAYER_ABSTRACTION_BALL_H
#define ROBOSOCCER_LAYER_ABSTRACTION_BALL_H


namespace RoboSoccer
{
namespace Common
{
namespace Geometry
{
	class Point;
	class Circle;
	class Angle;
	class OrientedPosition;
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
		virtual Common::Geometry::Angle getRotation() const = 0;
		virtual Common::Geometry::Circle getObstacle() const = 0;
		virtual double getVelocity() const = 0;
	};
}
}
}

#endif


