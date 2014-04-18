#ifndef ROBOSOCCER_COMMON_GEOMETRY_PATH_H
#define ROBOSOCCER_COMMON_GEOMETRY_PATH_H

#include <vector>
#include "common/geometry/point.h"

namespace  RoboSoccer
{
namespace Common
{
namespace Geometry
{
	class Circle;
	class Angle;
	class PathIntersectPoints;
	class Line;

	class Path
	{
	public:
		Path(const Point &start, const Point &end, double width);

		bool intersectsWith(const Circle &circle) const;
		bool isCircleCenterOnPath(const Circle &circle) const;
		PathIntersectPoints getIntersectPoints(const Circle &circle) const;
		Angle getAngleBetweenStartAndEnd() const;
		Point getLeftPerpendicularPoint(const Point &point) const;
		Point getRightPerpendicularPoint(const Point &point) const;
		double getDistanceToLeftPerpendicularPoint(const Point &point) const;
		double getDistanceToRightPerpendicularPoint(const Point &point) const;
		Line getCenterLine() const;

	private:
		Point m_start;
		Point m_end;
		double m_width;
	};
}
}
}

#endif
