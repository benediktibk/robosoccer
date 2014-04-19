#ifndef ROBOSOCCER_LAYER_ABSTRACTION_READABLEROBOT_H
#define ROBOSOCCER_LAYER_ABSTRACTION_READABLEROBOT_H

namespace RoboSoccer
{
namespace Common
{
namespace Geometry
{
	class OrientedPosition;
	class Circle;
}
}
namespace Layer
{
namespace Abstraction
{
	class ReadableRobot
	{
	public:
		virtual ~ReadableRobot() {}

		virtual Common::Geometry::OrientedPosition getPosition() = 0;
		virtual Common::Geometry::Circle createObstacle() = 0;

	};
}
}
}

#endif


