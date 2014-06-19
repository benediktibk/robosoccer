#ifndef ROBOSOCCER_COMMON_GEOMETRY_STRAIGHT_H
#define ROBOSOCCER_COMMON_GEOMETRY_STRAIGHT_H

#include "common/geometry/point.h"
#include "common/geometry/angle.h"
#include <vector>

namespace RoboSoccer
{
namespace Common
{
namespace Geometry
{
	class Circle;
	class Line;

	class Straight
	{
	public:
		Straight(const Point &referencePoint, const Angle &direction);

		std::vector<Point> getIntersectPoint(const Straight &straight) const;
		std::vector<Point> getIntersectPoint(const Line &line) const;
		Point getPerpendicularPoint(const Point &point) const;
		bool isTargetPointRightOfLine(const Point &target) const;
		void shiftParallel(const Point &point);
		Point getNormalizedDirectionVector() const;
		Point getReferencePoint() const;

	private:
		Point m_referencePoint;
		Angle m_direction;

	};
}
}
}

#endif
