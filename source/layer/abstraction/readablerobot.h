#ifndef ROBOSOCCER_LAYER_ABSTRACTION_READABLEROBOT_H
#define ROBOSOCCER_LAYER_ABSTRACTION_READABLEROBOT_H

namespace RoboSoccer
{
namespace Common
{
namespace Geometry
{
	class Pose;
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

		virtual Common::Geometry::Pose getPose() const = 0;
		virtual Common::Geometry::Circle getObstacle() const = 0;
		virtual void updateSensors() = 0;

		static double getWidth();

	};
}
}
}

#endif


