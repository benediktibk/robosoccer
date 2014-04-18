#ifndef ROBOSOCCER_COMMON_GEOMETRY_POINTDISTANCECOMPARE_H
#define ROBOSOCCER_COMMON_GEOMETRY_POINTDISTANCECOMPARE_H

#include "common/geometry/point.h"

namespace RoboSoccer
{
namespace Common
{
namespace Geometry
{
	class PointDistanceCompare
	{
		public:
			PointDistanceCompare(const Point &position);

			bool operator() (const Point &one, const Point &two) const;

		private:
			Point m_position;
	};
}
}
}

#endif


