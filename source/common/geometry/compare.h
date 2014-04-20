#ifndef ROBOSOCCER_COMMON_GEOMETRY_COMPARE_H
#define ROBOSOCCER_COMMON_GEOMETRY_COMPARE_H

#include <list>
#include "common/other/compare.h"

namespace RoboSoccer
{
namespace Common
{
namespace Geometry
{
	class Point;
	class Circle;
	class OrientedPosition;
	class Angle;

	class Compare
	{
	public:
		Compare(double epsilon);

		bool isFuzzyEqual(const Angle &one, const Angle &two) const;
		bool isFuzzyEqual(const Point &one, const Point &two) const;
		bool isFuzzyEqual(const Circle &one, const Circle &two) const;
		bool isFuzzyEqual(const OrientedPosition &one, const OrientedPosition &two) const;
		bool isFuzzyEqual(const std::list<OrientedPosition> &one, const std::list<OrientedPosition> &two) const;

	private:
		 Other::Compare m_internalCompare;
	};
}
}
}

#endif