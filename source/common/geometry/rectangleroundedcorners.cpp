#include "rectangleroundedcorners.h"

using namespace RoboSoccer::Common::Geometry;

RectangleRoundedCorners::RectangleRoundedCorners(const Point &one, const Point &two, const double cornerRadius):
	Rectangle(one, two),
	m_radius(cornerRadius)
{ }

