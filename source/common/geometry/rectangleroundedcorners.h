#ifndef ROBOSOCCER_COMMON_GEOMETRY_RECTANGLEROUNDEDCORNERS_H
#define ROBOSOCCER_COMMON_GEOMETRY_RECTANGLEROUNDEDCORNERS_H

#include "common/geometry/rectangle.h"

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
	class RectangleRoundedCorners :
			public Rectangle
	{
	public:
		RectangleRoundedCorners(const Point &one, const Point &two, const double cornerRadius);


	private:
		double m_radius;

	};
}
}
}

#endif
