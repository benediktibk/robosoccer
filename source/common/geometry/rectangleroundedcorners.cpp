#include "common/geometry/rectangleroundedcorners.h"
#include "common/geometry/circle.h"
#include "common/other/compare.h"

using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Other;

RectangleRoundedCorners::RectangleRoundedCorners(const Point &one, const Point &two, const double cornerRadius):
	Rectangle(one, two),
	m_radius(cornerRadius)
{ }

bool RectangleRoundedCorners::isInside(const Point &point, const Compare &compare) const
{
	Rectangle outsideRectangle(m_leftLower, m_rightUpper);

	if (!outsideRectangle.isInside(point, compare))
		return false;

	Rectangle insideRectangleX(m_leftLower + Point(m_radius, 0), m_rightUpper - Point(m_radius, 0));
	Rectangle insideRectangleY(m_leftLower + Point(0, m_radius), m_rightUpper - Point(0, m_radius));

	if (insideRectangleX.isInside(point, compare) || insideRectangleY.isInside(point, compare))
		return true;

	Point innerLowerLeft = m_leftLower + Point(m_radius, m_radius);
	Point innerUpperRight = m_rightUpper - Point(m_radius, m_radius);

	Point innerUpperLeft = innerLowerLeft + Point(0, getHeight() - 2.0*m_radius);
	Point innerLowerRight = innerUpperRight - Point(0, getHeight() - 2.0*m_radius);

	Circle innerLowerLeftCircle(innerLowerLeft, 0.5*m_radius);
	Circle innerLowerRightCircle(innerLowerRight, 0.5*m_radius);
	Circle innerUpperLeftCircle(innerUpperLeft, 0.5*m_radius);
	Circle innerUpperRightCircle(innerUpperRight, 0.5*m_radius);

	if (innerLowerLeftCircle.isInside(point)
			|| innerLowerRightCircle.isInside(point)
			|| innerUpperLeftCircle.isInside(point)
			|| innerUpperRightCircle.isInside(point))
		return true;

	return false;
}
