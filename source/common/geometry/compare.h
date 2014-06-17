#ifndef ROBOSOCCER_COMMON_GEOMETRY_COMPARE_H
#define ROBOSOCCER_COMMON_GEOMETRY_COMPARE_H

#include <vector>
#include "common/other/compare.h"

namespace RoboSoccer
{
namespace Common
{
namespace Geometry
{
	class Point;
	class Circle;
	class Pose;
	class Angle;

	class Compare
	{
	public:
		Compare(double epsilon);

		bool isFuzzyEqual(const Angle &one, const Angle &two) const;
		bool isFuzzyEqual(const Point &one, const Point &two) const;
		bool isFuzzyEqual(const Circle &one, const Circle &two) const;
		bool isFuzzyEqual(const Pose &one, const Pose &two) const;
		bool isFuzzyEqualWithCorrectOrder(const std::vector<Pose> &one, const std::vector<Pose> &two) const;

	private:
		 Other::Compare m_internalCompare;
	};
}
}
}

#endif
