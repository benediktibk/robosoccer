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
	class Straight
	{
	public:
		Straight(const Point &referencePoint, const Angle &direction);
//		Straight(const Point &pointOnStraight1, const Point &pointOnStraight2);

		Point getPerpendicularPoint(const Point &point) const;
		bool isTargetPointRightOfLine(const Point &target) const;

	private:
		Point m_referencePoint;
		Angle m_direction;

	};
}
}
}

#endif
