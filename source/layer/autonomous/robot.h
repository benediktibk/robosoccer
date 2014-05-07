#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOT_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOT_H

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
namespace Autonomous
{
	class IntelligentBall;

	class Robot
	{
	public:
		virtual ~Robot() { }

		virtual void goTo(Common::Geometry::Pose const &position) = 0;
		virtual void stop() = 0;
		virtual Common::Geometry::Pose getCurrentPose() const = 0;
		virtual Common::Geometry::Circle getObstacle() const = 0;
		virtual bool targetReached() const = 0;
		virtual bool cantReachTarget() const = 0;
		virtual void kick(unsigned int force, IntelligentBall const &ball) = 0;
		virtual void update() = 0;
		virtual void measure() = 0;
	};
}
}
}

#endif
