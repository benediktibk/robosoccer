#ifndef ROBOSOCCER_COMMON_ROUTING_ROUTERIMPL_H
#define ROBOSOCCER_COMMON_ROUTING_ROUTERIMPL_H

#include "common/routing/router.h"
#include <vector>
#include <list>

namespace RoboSoccer
{
namespace Common
{
namespace Geometry
{
	class Path;
}
namespace Routing
{
	class RoutingResult;
	class RoutingObstacle;

	class RouterImpl :
			public Router
	{
	public:
		RouterImpl(double robotWidth, const FieldPositionChecker &field);

		virtual Route calculateRoute(
				const Geometry::Point &start, const Geometry::Point &end, const std::vector<Geometry::Circle> &obstacles) const;
		virtual std::vector<Geometry::Circle> filterObstacles(const std::vector<Geometry::Circle> &obstacles, const Geometry::Point &position) const;
		std::vector<Geometry::Point> getPointsBesideObstacle(const Geometry::Path &path, const Geometry::Circle &obstacle) const;
		bool detectLoopInConsideredObstacles(const std::list<RoutingObstacle> &obstacles) const;

	private:
		std::vector<RoutingResult> calculateStartParts(const Geometry::Point &start, const Geometry::Point &end,
				const std::vector<Geometry::Circle> &obstacles, unsigned int searchDepth,
				const std::list<RoutingObstacle> &consideredObstacles, bool startInsideField) const;
		std::vector<RoutingResult> calculateStartPartsWithFreeEnd(
				const Geometry::Point &start, const Geometry::Point &end,
				const std::vector<Geometry::Circle> &obstacles, unsigned int searchDepth,
				const std::list<RoutingObstacle> &consideredObstacles, bool startInsideField) const;
		std::vector<RoutingResult> calculateStartPartsWithCoveredEnd(
				const Geometry::Point &start, const Geometry::Point &end,
				const std::vector<Geometry::Circle> &obstacles, unsigned int searchDepth,
				const std::list<RoutingObstacle> &consideredObstacles, bool startInsideField) const;
		std::vector<RoutingResult> calculateStartPartsWithFreeDirectPath(const Geometry::Point &start, const Geometry::Point &end,
				const std::list<RoutingObstacle> &consideredObstacles) const;
		std::vector<RoutingResult> calculateEndParts(
				const std::vector<RoutingResult> &startRoutes, const Geometry::Point &end,
				const std::vector<Geometry::Circle> &obstacles, unsigned int searchDepth) const;
		std::vector<Geometry::Circle> findRealObstacles(const std::vector<Geometry::Circle> &obstacles, const Geometry::Path &path) const;
		Geometry::Circle findClosestObstacle(const std::vector<Geometry::Circle> &obstacles, const Geometry::Point &point) const;
		std::vector<RoutingResult> calculateRoutesToPointsBesideObstacle(
				const Geometry::Circle &obstacle, const Geometry::Point &start, const Geometry::Point &end,
				const std::vector<Geometry::Circle> &obstacles,
				unsigned int searchDepth, const std::list<RoutingObstacle> &consideredObstacles, bool startIsInsideField) const;

	private:
		const unsigned int m_maximumSearchDepth;
		const FieldPositionChecker &m_fieldPositionChecker;
		double m_robotWidth;
	};
}
}
}

#endif
