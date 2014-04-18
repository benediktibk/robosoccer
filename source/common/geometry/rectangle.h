#ifndef ROBOSOCCER_COMMON_GEOMETRY_RECTANGLE_H
#define ROBOSOCCER_COMMON_GEOMETRY_RECTANGLE_H

#include "common/geometry/point.h"

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
	class Circle;

	class Rectangle
	{
	public:
		Rectangle(const Point &one, const Point &two);

		const Point &getLeftLower() const;
		const Point &getRightUpper() const;
		double getWidth() const;
		double getHeight() const;
		bool isInside(const Point &point, const Other::Compare &compare) const;
		bool overlapsApproximately(const Circle &circle, const Other::Compare &compare) const;
		bool overlaps(const Rectangle &rectangle, const Other::Compare &compare) const;

	private:
		Point m_leftLower;
		Point m_rightUpper;
	};
}
}
}

#endif
