#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOT_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOT_H

namespace RoboSoccer
{
namespace Common
{
namespace Geometry
{
	class Point;
	class Pose;
}
}
namespace Layer
{
namespace Autonomous
{
	class Robot
	{
	public:
		virtual ~Robot() { }

		virtual void goTo(Common::Geometry::Point const &position) = 0;
		virtual void stop() = 0;
		virtual Common::Geometry::Pose getCurrentPose() const = 0;
		virtual bool targetReached() const = 0;
	};
}
}
}

#endif
