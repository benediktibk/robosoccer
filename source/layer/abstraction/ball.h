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

		virtual Common::Geometry::Point getPosition() = 0;
		virtual Common::Geometry::Circle getObstacle() = 0;
	};
}
}
}

#endif

