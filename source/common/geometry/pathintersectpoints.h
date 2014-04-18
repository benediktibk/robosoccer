#ifndef ROBOSOCCER_COMMON_GEOMETRY_PATHINTERSECTPOINTS_H
#define ROBOSOCCER_COMMON_GEOMETRY_PATHINTERSECTPOINTS_H

#include <vector>
#include "common/geometry/point.h"

namespace RoboSoccer
{
namespace Common
{
namespace Geometry
{
class PathIntersectPoints
{
public:
	enum IntersectType { IntersectTypeFromLeft,
						 IntersectTypeFromRight,
						 IntersectTypeFromEnd,
						 IntersectTypeFromStart,
						 IntersectTypeNoIntersect
					   };

public:
	PathIntersectPoints(std::vector<Point> intersectPoints, IntersectType intersectFrom);

	std::vector<Point> getIntersectPoints();
	IntersectType getIntersectTypeFrom();
	std::size_t getIntersectPointsCount();
	Point front();
	Point back();

private:
	std::vector<Point> m_intersectPoints;
	IntersectType m_intersectFrom;

};
}
}
}

#endif


