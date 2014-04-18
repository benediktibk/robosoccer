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
		RouterImpl(double robotWidth);

		virtual Route calculateRoute(
				const Geometry::OrientedPosition &start, const Geometry::OrientedPosition &end, const FieldPositionChecker &field,
				const Geometry::Angle &maximumRotation, double minimumStepAfterMaximumRotation, bool ignoreFinalOrientation,
				const std::vector<Geometry::Circle> &hardObstacles, const std::vector<Geometry::Circle> &softObstacles) const;
		std::vector<Geometry::Point> getPointsBesideObstacle(const Geometry::Path &path, const Geometry::Circle &obstacle) const;
		std::vector<Geometry::Circle> filterObstacles(const std::vector<Geometry::Circle> &softObstacles,
				const std::vector<Geometry::Circle> &hardObstacles, const Geometry::Point &position) const;
		bool detectLoopInConsideredObstacles(const std::list<RoutingObstacle> &obstacles) const;

	private:
		std::vector<RoutingResult> calculateStartParts(const Geometry::OrientedPosition &start, const Geometry::Point &end, const FieldPositionChecker &field,
				const std::vector<Geometry::Circle> &obstacles, unsigned int searchDepth,
				const std::list<RoutingObstacle> &consideredObstacles, const Geometry::Angle &maximumRotation,
				double minimumStepAfterMaximumRotation, bool startInsideField) const;
		std::vector<RoutingResult> calculateStartPartsWithFreeEnd(
				const Geometry::OrientedPosition &start, const Geometry::Point &end, const FieldPositionChecker &field,
				const std::vector<Geometry::Circle> &obstacles, unsigned int searchDepth,
				const std::list<RoutingObstacle> &consideredObstacles, const Geometry::Angle &maximumRotation,
				double minimumStepAfterMaximumRotation, bool startInsideField) const;
		std::vector<RoutingResult> calculateStartPartsWithCoveredEnd(
				const Geometry::OrientedPosition &start, const Geometry::Point &end, const FieldPositionChecker &field,
				const std::vector<Geometry::Circle> &obstacles, unsigned int searchDepth,
				const std::list<RoutingObstacle> &consideredObstacles, const Geometry::Angle &maximumRotation,
				double minimumStepAfterMaximumRotation, bool startInsideField) const;
		std::vector<RoutingResult> calculateStartPartsWithFreeDirectPath(
				const Geometry::OrientedPosition &start, const Geometry::Point &end, const FieldPositionChecker &field,
				const std::vector<Geometry::Circle> &obstacles, unsigned int searchDepth,
				const std::list<RoutingObstacle> &consideredObstacles,
				const Geometry::Angle &maximumRotation, double minimumStepAfterMaximumRotation, bool startInsideField) const;
		std::vector<RoutingResult> calculateEndParts(
				const std::vector<RoutingResult> &startRoutes, const Geometry::Point &end, const FieldPositionChecker &field,
				const std::vector<Geometry::Circle> &obstacles, unsigned int searchDepth, const Geometry::Angle &maximumRotation, double minimumStepAfterMaximumRotation) const;
		std::vector<Geometry::Circle> findRealObstacles(const std::vector<Geometry::Circle> &obstacles, const Geometry::Path &path) const;
		Geometry::Circle findClosestObstacle(const std::vector<Geometry::Circle> &obstacles, const Geometry::Point &point) const;
		std::vector<RoutingResult> calculateRoutesToPointsBesideObstacle(
				const Geometry::Circle &obstacle, const Geometry::OrientedPosition &start, const Geometry::Point &end,
				const FieldPositionChecker &field, const std::vector<Geometry::Circle> &obstacles,
				unsigned int searchDepth, const std::list<RoutingObstacle> &consideredObstacles,
				const Geometry::Angle &maximumRotation, double minimumStepAfterMaximumRotation, bool startIsInsideField) const;
		std::vector<Route> fixRotationOfFinalStep(
				const std::vector<RoutingResult> &routes, const Geometry::Angle &startOrientation,
				const Geometry::Angle &finalOrientation, const Geometry::Angle &maximumRotation,
				double minimumStepAfterMaximumRotation,	const std::vector<Geometry::Circle> &obstacles,
				bool ignoreFinalOrientation) const;

	private:
		const unsigned int m_maximumSearchDepth;
		double m_robotWidth;
	};
}
}
}

#endif
