#ifndef ROBOSOCCER_COMMON_GEOMETRY_LINE_H
#define ROBOSOCCER_COMMON_GEOMETRY_LINE_H

#include "common/geometry/point.h"
#include "vector"

namespace  RoboSoccer
{
namespace Common
{
namespace Geometry
{
	class Circle;

	class Line
	{
	public:
		Line(const Point &start, const Point &end);

		std::vector<Point> getIntersectPoints(const Circle &circle) const;
		Point getPerpendicularPoint(Point point) const;
		Point getPointOnDirectionOfLine(double percentOfLenghtOfLine) const;
		bool isTargetPointRightOfLine(const Point &target) const;
		bool isOnePointLeftAndOneRightOfLine(const Point &one, const Point &two) const;
		void shiftParallel(const Point &point);
		Point getStart() const;
		Point getEnd() const;

	private:
		Point m_start;
		Point m_end;
	};
}
}
}

#endif
