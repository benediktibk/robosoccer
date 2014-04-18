#ifndef ROBOSOCCER_COMMON_GEOMETRY_CIRCLE_H
#define ROBOSOCCER_COMMON_GEOMETRY_CIRCLE_H

#include "common/geometry/point.h"
#include "common/geometry/rectangle.h"
#include <vector>

namespace RoboSoccer
{
namespace Common
{
namespace Other
{
	class Compare;
}
namespace Geometry
{
	class Circle
	{
	public:
		Circle();
		Circle(const Point &center, double diameter);

		void setCenter(const Point &point);
		const Point& getCenter() const;
		void setDiameter(double value);
		double getDiameter() const;
		Rectangle getBoundingRectangle() const;
		double getDistanceTo(const Point &position) const;
		bool overlapsWith(const Circle &circle) const;
		bool overlapsWith(const std::vector<Circle> &circles) const;
		std::vector<Point> getIntersectionPoints(const Circle &circle) const;
		bool isOnCircle(const Point &point, const Other::Compare &compare) const;
		bool isInside(const Point &point) const;

		bool operator==(const Circle &circle) const;

	private:
		Point m_center;
		double m_diameter;
	};
}
}
}

std::ostream& operator<<(std::ostream &stream, const RoboSoccer::Common::Geometry::Circle &circle);

#endif
