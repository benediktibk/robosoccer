#include "common/routing/routerimpl.h"
#include "common/routing/fieldpositionchecker.h"
#include "common/routing/route.h"
#include "common/routing/routelengthcompare.h"
#include "common/routing/routingobstacle.h"
#include "common/routing/routingresult.h"
#include "common/geometry/path.h"
#include "common/geometry/pathintersectpoints.h"
#include "common/geometry/angle.h"
#include "common/geometry/line.h"
#include "common/geometry/orientedposition.h"
#include "common/geometry/compare.h"
#include <math.h>
#include <assert.h>
#include <algorithm>
#include <limits>

using namespace std;
using namespace RoboSoccer::Common::Routing;
using namespace RoboSoccer::Common::Geometry;

RouterImpl::RouterImpl(double robotWidth) :
	m_maximumSearchDepth(7),
	m_robotWidth(robotWidth)
{ }

Route RouterImpl::calculateRoute(const Point &start, const Point &end, const FieldPositionChecker &field,
		const vector<Circle> &obstacles) const
{
	if (!field.isPointInsideField(end))
		return Route();

	Circle endCircle(end, sqrt(2)*m_robotWidth);
	if (endCircle.overlapsWith(obstacles))
		return Route();

	vector<Circle> allObstacles = filterObstacles(obstacles, start);

	bool startInsideField = field.isPointInsideField(start);
	list<RoutingObstacle> consideredObstacles;
	vector<RoutingResult> routingResults = calculateStartParts(
				start, end, field, allObstacles, 0, consideredObstacles,
				startInsideField);
	vector<Route> routes;
	for (vector<RoutingResult>::const_iterator i = routingResults.begin(); i != routingResults.end(); ++i)
		routes.push_back(i->getRoute());

	if (routes.size() == 0)
		return Route();
	else
	{
		RouteLengthCompare lengthCompare;
		sort(routes.begin(), routes.end(), lengthCompare);
		return routes.front();
	}
}

vector<Point> RouterImpl::getPointsBesideObstacle(const Path &path, const Circle &obstacle) const
{
	vector<Point> pointsBesideObstacle;
	PathIntersectPoints intersectionPoints = path.getIntersectPoints(obstacle);
	Point shortPointBesideObstacle;
	Point longPointBesideObstacle;
	double offsetDistanceLongPoint = 0.51*sqrt(2)*m_robotWidth + obstacle.getDiameter()/2;
	Angle offsetAngleShortPoint = path.getAngleBetweenStartAndEnd();

	if((intersectionPoints.getIntersectTypeFrom() == PathIntersectPoints::IntersectTypeFromStart) ||
		(intersectionPoints.getIntersectTypeFrom() == PathIntersectPoints::IntersectTypeFromEnd))
		return pointsBesideObstacle;

	if(intersectionPoints.getIntersectTypeFrom() != PathIntersectPoints::IntersectTypeNoIntersect)
	{
		Point centerBetweenIntersectPoints = (intersectionPoints.front() + intersectionPoints.back())/2;
		offsetDistanceLongPoint -= centerBetweenIntersectPoints.distanceTo(obstacle.getCenter());
		double offsetDistanceShortPoint = offsetDistanceLongPoint;
		Line line(path.getCenterLine());
		line.shiftParallel(intersectionPoints.front());

		if(!path.isCircleCenterOnPath(obstacle))
			offsetDistanceLongPoint += 2*centerBetweenIntersectPoints.distanceTo(obstacle.getCenter());
		else
			offsetDistanceShortPoint += 2*centerBetweenIntersectPoints.distanceTo(obstacle.getCenter());
		if(intersectionPoints.getIntersectTypeFrom() == PathIntersectPoints::IntersectTypeFromLeft)
		{
			offsetAngleShortPoint = offsetAngleShortPoint + Angle::getThreeQuarterRotation();
			if(line.isTargetPointRightOfLine(obstacle.getCenter()) && !path.isCircleCenterOnPath(obstacle))
				offsetAngleShortPoint = offsetAngleShortPoint - Angle::getHalfRotation();
		}
		else
		{
			offsetAngleShortPoint = offsetAngleShortPoint + Angle::getQuarterRotation();
			if(!line.isTargetPointRightOfLine(obstacle.getCenter()) && !path.isCircleCenterOnPath(obstacle))
				offsetAngleShortPoint = offsetAngleShortPoint - Angle::getHalfRotation();
		}
		shortPointBesideObstacle = centerBetweenIntersectPoints + Point(offsetDistanceShortPoint, offsetAngleShortPoint);
		longPointBesideObstacle = centerBetweenIntersectPoints + Point(offsetDistanceLongPoint, offsetAngleShortPoint + Angle::getHalfRotation());
	}
	else
	{
		shortPointBesideObstacle = obstacle.getCenter() + Point(offsetDistanceLongPoint, offsetAngleShortPoint + Angle::getQuarterRotation());
		longPointBesideObstacle = obstacle.getCenter() + Point(offsetDistanceLongPoint, offsetAngleShortPoint + Angle::getThreeQuarterRotation());
	}

	pointsBesideObstacle.push_back(shortPointBesideObstacle);
	pointsBesideObstacle.push_back(longPointBesideObstacle);
	return pointsBesideObstacle;
}

vector<Circle> RouterImpl::filterObstacles(
		const vector<Circle> &obstacles,
		const Point &position) const
{
	vector<Circle> fileredObstacles;
	fileredObstacles.reserve(obstacles.size());
	Circle startCircle(position, sqrt(2)*m_robotWidth);

	for (vector<Circle>::const_iterator i = obstacles.begin(); i != obstacles.end(); ++i)
	{
		Circle obstacle = *i;
		const Point &center = obstacle.getCenter();

		if (startCircle.isInside(center))
			continue;

		if (startCircle.overlapsWith(obstacle))
		{
			double distanceToCenter = startCircle.getDistanceTo(center);
			double diameter = distanceToCenter*2*0.9;
			obstacle.setDiameter(diameter);
		}

		fileredObstacles.push_back(obstacle);
	}

	return fileredObstacles;
}

vector<RoutingResult> RouterImpl::calculateStartParts(const Point &start, const Point &end, const FieldPositionChecker &field,
		const vector<Circle> &obstacles, unsigned int searchDepth,
		const list<RoutingObstacle> &consideredObstacles,
		bool startInsideField) const
{
	++searchDepth;
	if (searchDepth > m_maximumSearchDepth)
		return vector<RoutingResult>();

	Circle endCircle(end, sqrt(2)*m_robotWidth);
	bool endCovered = endCircle.overlapsWith(obstacles);
	if (endCovered)
		return calculateStartPartsWithCoveredEnd(
				start, end, field, obstacles, searchDepth, consideredObstacles, startInsideField);
	else
		return calculateStartPartsWithFreeEnd(
				start, end, field, obstacles, searchDepth, consideredObstacles, startInsideField);
}

vector<RoutingResult> RouterImpl::calculateStartPartsWithFreeEnd(const Point &start, const Point &end, const FieldPositionChecker &field,
		const vector<Circle> &obstacles, unsigned int searchDepth,
		const list<RoutingObstacle> &consideredObstacles,
		bool startInsideField) const
{
	Path directPath(start, end, m_robotWidth);
	vector<Circle> realObstacles = findRealObstacles(obstacles, directPath);

	if (realObstacles.size() == 0)
		return calculateStartPartsWithFreeDirectPath(
					start, end, consideredObstacles);
	else
	{
		Circle closestObstacle = findClosestObstacle(realObstacles, start);
		vector<RoutingResult> startParts = calculateRoutesToPointsBesideObstacle(
					closestObstacle, start, end, field, obstacles,
					searchDepth, consideredObstacles, startInsideField);
		return calculateEndParts(
					startParts, end, field, obstacles, searchDepth);
	}
}

vector<RoutingResult> RouterImpl::calculateStartPartsWithCoveredEnd(const Point &start, const Point &end, const FieldPositionChecker &field, const vector<Circle> &obstacles,
		unsigned int searchDepth, const list<RoutingObstacle> &consideredObstacles,
		bool startInsideField) const
{
	Path path(start, end, m_robotWidth);
	vector<Circle> obstaclesTillEnd = findRealObstacles(obstacles, path);

	if (obstaclesTillEnd.size() == 0)
		return calculateStartPartsWithFreeDirectPath(
					start, end, consideredObstacles);
	else
	{
		Circle obstacle = findClosestObstacle(obstaclesTillEnd, start);
		double diameter = obstacle.getDiameter();
		Point direction = end - start;
		double directionLength = start.distanceTo(end);
		double desiredLength = directionLength + 2*diameter;
		Point directionModified = direction/directionLength*desiredLength;
		Point extendedEnd = start + directionModified;
		return calculateRoutesToPointsBesideObstacle(
					obstacle, start, extendedEnd, field, obstacles,
					searchDepth, consideredObstacles, startInsideField);
	}
}

vector<RoutingResult> RouterImpl::calculateStartPartsWithFreeDirectPath(const Point &start, const Point &end,
		const list<RoutingObstacle> &consideredObstacles) const
{
	vector<RoutingResult> result;
	Route directRoute(m_robotWidth);
	directRoute.addPoint(start);
	directRoute.addPoint(end);
	result.push_back(RoutingResult(directRoute, consideredObstacles));
	return result;
}

vector<RoutingResult> RouterImpl::calculateEndParts(
		const vector<RoutingResult> &startRoutes, const Point &end, const FieldPositionChecker &field,
		const vector<Circle> &obstacles, unsigned int searchDepth) const
{
	vector<RoutingResult> result;
	result.reserve(startRoutes.size());

	for (vector<RoutingResult>::const_iterator i = startRoutes.begin(); i != startRoutes.end(); ++i)
	{
		const Route &startRoute = i->getRoute();
		const list<RoutingObstacle> &consideredObstacles = i->getObstacles();
		const Geometry::Point &lastPoint = startRoute.getLastPoint();
		const Geometry::Point &nextToLastPoint = startRoute.getNextToLastPoint();
		OrientedPosition start(lastPoint, Angle(nextToLastPoint, lastPoint));
		bool startInsideField = field.isPointInsideField(lastPoint);
		assert(!(lastPoint == end));

		list<RoutingObstacle> reducedConsideredObstacles;
		if (!consideredObstacles.empty())
			reducedConsideredObstacles.push_back(consideredObstacles.back());
		vector<RoutingResult> routes = calculateStartParts(
					start, end, field, obstacles, searchDepth, reducedConsideredObstacles, startInsideField);

		for (vector<RoutingResult>::const_iterator j = routes.begin(); j != routes.end(); ++j)
		{
			const Route &endRoute = j->getRoute();
			const list<RoutingObstacle> &endObstacles = j->getObstacles();
			Route completeRoute = startRoute;
			completeRoute.add(endRoute);
			result.push_back(RoutingResult(completeRoute, endObstacles));
		}
	}

	return result;
}

vector<Circle> RouterImpl::findRealObstacles(const vector<Circle> &obstacles, const Path &path) const
{
	vector<Circle> result;

	for (vector<Circle>::const_iterator i = obstacles.begin(); i != obstacles.end(); ++i)
		if (path.intersectsWith(*i))
			result.push_back(*i);

	return result;
}

Circle RouterImpl::findClosestObstacle(const vector<Circle> &obstacles, const Point &point) const
{
	assert(obstacles.size() > 0);

	double closestDistance = numeric_limits<double>::max();
	Circle closestObstacle;

	for (vector<Circle>::const_iterator i = obstacles.begin(); i != obstacles.end(); ++i)
	{
		const Circle &obstacle = *i;
		double distance = obstacle.getDistanceTo(point);

		if (distance < closestDistance)
		{
			closestDistance = distance;
			closestObstacle = obstacle;
		}
	}

	return closestObstacle;
}

vector<RoutingResult> RouterImpl::calculateRoutesToPointsBesideObstacle(
		const Circle &obstacle, const Point &start, const Point &end, const FieldPositionChecker &field,
		const vector<Circle> &obstacles, unsigned int searchDepth,
		const list<RoutingObstacle> &consideredObstacles, bool startIsInsideField) const
{
	Path path(start, end, m_robotWidth);
	vector<Point> pointsBesideObstacle = getPointsBesideObstacle(path, obstacle);
	vector<RoutingResult> result;

	if(pointsBesideObstacle.size() != 2)
		return result;

	Line line(start, end);
	assert(line.isOnePointLeftAndOneRightOfLine(pointsBesideObstacle[0], pointsBesideObstacle[1]));
	Point leftPoint;
	Point rightPoint;

	if (line.isTargetPointRightOfLine(pointsBesideObstacle.front()))
	{
		rightPoint = pointsBesideObstacle.front();
		leftPoint = pointsBesideObstacle.back();
	}
	else
	{
		rightPoint = pointsBesideObstacle.back();
		leftPoint = pointsBesideObstacle.front();
	}

	bool rightPointInsideField = field.isPointInsideField(rightPoint);
	if ((rightPointInsideField && startIsInsideField) || !startIsInsideField)
	{
		list<RoutingObstacle> extendedConsideredObstacles = consideredObstacles;
		extendedConsideredObstacles.push_back(RoutingObstacle(obstacle, true));

		if (!detectLoopInConsideredObstacles(extendedConsideredObstacles))
		{
			vector<RoutingResult> startParts = calculateStartParts(
						start, rightPoint, field, obstacles, searchDepth, extendedConsideredObstacles, rightPointInsideField);
			result.insert(result.end(), startParts.begin(), startParts.end());
		}
	}

	bool leftPointInsideField = field.isPointInsideField(leftPoint);
	if ((leftPointInsideField && startIsInsideField) || !startIsInsideField)
	{
		list<RoutingObstacle> extendedConsideredObstacles = consideredObstacles;
		extendedConsideredObstacles.push_back(RoutingObstacle(obstacle, false));

		if (!detectLoopInConsideredObstacles(extendedConsideredObstacles))
		{
			vector<RoutingResult> startParts = calculateStartParts(
						start, leftPoint, field, obstacles, searchDepth, extendedConsideredObstacles, leftPointInsideField);
			result.insert(result.end(), startParts.begin(), startParts.end());
		}
	}

	return result;
}

bool RouterImpl::detectLoopInConsideredObstacles(const list<RoutingObstacle> &obstacles) const
{
	if (obstacles.size() == 0)
		return false;

	const RoutingObstacle &lastObstacle = obstacles.back();
	size_t distance = 0;
	bool found = false;
	list<RoutingObstacle>::const_reverse_iterator i = obstacles.rbegin();
	++i;
	for (; i != obstacles.rend() && !found; ++i)
	{
		++distance;
		if (lastObstacle.getObstacle() == i->getObstacle())
		{
			if (i->wentRightBeside() != lastObstacle.wentRightBeside())
				return true;
			else
				found = true;
		}
	}

	if (found)
		return distance > 1;
	else
		return false;
}
