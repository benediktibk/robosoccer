#ifndef ROBOSOCCER_LAYER_AUTONOMOUS_OBSTACLEFETCHER_H
#define ROBOSOCCER_LAYER_AUTONOMOUS_OBSTACLEFETCHER_H

#include <vector>

namespace RoboSoccer
{
namespace Common
{
namespace Geometry
{
	class Circle;
}
}
namespace Layer
{
namespace Autonomous
{
	class ObstacleSource;

	class ObstacleFetcher
	{
	public:
		virtual ~ObstacleFetcher() { }

		virtual std::vector<Common::Geometry::Circle> getAllObstacles() const = 0;
		virtual std::vector<Common::Geometry::Circle> getAllObstaclesButMe(ObstacleSource const &me) const = 0;
	};
}
}
}

#endif