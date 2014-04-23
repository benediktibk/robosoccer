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
	};
}
}
}

#endif


