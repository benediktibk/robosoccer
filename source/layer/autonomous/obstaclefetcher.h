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
	class Point;
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

		virtual void addSource(ObstacleSource const &source) = 0;
		virtual std::vector<Common::Geometry::Circle> getAllObstacles() const = 0;
		virtual std::vector<Common::Geometry::Circle> getAllObstaclesButMe(ObstacleSource const &me) const = 0;
		/*!
		 * Returns all obstacles except the own one which are closer than the distance. The distance
		 * is interpreted as distance to the edge of an obstacle, therefore the radius of other objects
		 * do not have to be included in this param.
		 */
		virtual std::vector<Common::Geometry::Circle> getAllObstaclesButMeInRange(
				ObstacleSource const &me, Common::Geometry::Point const &ownPosition, double distance) const = 0;
		/*!
		 * The same as the function above, but it ignores the specified ball.
		 */
		virtual std::vector<Common::Geometry::Circle> getAllObstaclesButMeAndBallInRange(
				ObstacleSource const &me, Common::Geometry::Point const &ownPosition, double distance) const = 0;
	};
}
}
}

#endif