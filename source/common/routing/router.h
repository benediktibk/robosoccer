#ifndef ROBOSOCCER_COMMON_ROUTING_ROUTER_H
#define ROBOSOCCER_COMMON_ROUTING_ROUTER_H

#include <vector>

namespace RoboSoccer
{
namespace Common
{
namespace Geometry
{
	class Pose;
	class Circle;
	class Point;
	class Angle;
}
namespace Routing
{
	class Route;
	class FieldPositionChecker;

	class Router
	{
	public:
		virtual ~Router() { }

		virtual Route calculateRoute(
				const Geometry::Point &start, const Geometry::Point &end, const std::vector<Geometry::Circle> &obstacles) const = 0;
		virtual std::vector<Geometry::Circle> filterObstacles(const std::vector<Geometry::Circle> &obstacles, const Geometry::Point &position) const = 0;
	};
}
}
}

#endif


