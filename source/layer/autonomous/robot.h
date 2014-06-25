#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_ROBOT_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_ROBOT_H

#include "layer/autonomous/obstaclesource.h"
#include "layer/autonomous/robotstates/drivemode.h"

namespace RoboSoccer
{
namespace Common
{
namespace Geometry
{
	class Pose;
	class Circle;
}
namespace Routing
{
	class Route;
}
}
namespace Layer
{
namespace Autonomous
{
	class IntelligentBall;

	class Robot :
			public ObstacleSource
	{
	public:
		virtual ~Robot() { }

		virtual void goTo(std::vector<Common::Geometry::Pose> const &positions, DriveMode driveMode) = 0;
		virtual void goToDirect(Common::Geometry::Pose const &position) = 0;
		virtual void stop() = 0;
		virtual Common::Geometry::Pose getCurrentPose() const = 0;
		virtual Common::Geometry::Circle getObstacle() const = 0;
		virtual std::vector<Common::Geometry::Circle> getObstacles() const = 0;
		virtual bool reachedTarget() const = 0;
		virtual void kick(IntelligentBall const &ball) = 0;
		virtual void update() = 0;
		virtual Common::Routing::Route getCurrentRoute() const = 0;
		virtual std::vector<Common::Geometry::Pose> getCurrentTargets() const = 0;
	};
}
}
}

#endif
