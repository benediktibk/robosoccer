#include "common/geometry/rectangle.h"
#include "common/geometry/compare.h"
#include "common/geometry/circle.h"
#include <algorithm>
#include <math.h>

using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Other;
using namespace std;

Rectangle::Rectangle(const Point &one, const Point &two) :
	m_leftLower(min(one.getX(), two.getX()), min(one.getY(), two.getY())),
	m_rightUpper(max(one.getX(), two.getX()), max(one.getY(), two.getY()))
{ }

const Point &Rectangle::getLeftLower() const
{
	return m_leftLower;
}

const Point &Rectangle::getRightUpper() const
{
	return m_rightUpper;
}

double Rectangle::getWidth() const
{
	return m_rightUpper.getX() - m_leftLower.getX();
}

double Rectangle::getHeight() const
{
	return m_rightUpper.getY() - m_leftLower.getY();
}

bool Rectangle::isInside(const Point &point, const Other::Compare &compare) const
{
	return	compare.isFuzzyGreater(point.getX(), m_leftLower.getX()) &&
			compare.isFuzzyGreater(point.getY(), m_leftLower.getY()) &&
			compare.isFuzzySmaller(point.getX(), m_rightUpper.getX()) &&
			compare.isFuzzySmaller(point.getY(), m_rightUpper.getY());
}

bool Rectangle::overlapsApproximately(const Circle &circle, const Other::Compare &compare) const
{
	return overlaps(circle.getBoundingRectangle(), compare);
}

bool Rectangle::overlaps(const Rectangle &rectangle, const Other::Compare &compare) const
{
	const double widthSum = getWidth() + rectangle.getWidth();
	const double horizontalDifference = fabs((2*m_leftLower.getX() + getWidth()) - (2*rectangle.getLeftLower().getX() + rectangle.getWidth()));

	if (compare.isStrictFuzzySmaller(horizontalDifference, widthSum))
	{
		const double heightSum = getHeight() + rectangle.getHeight();
		const double verticalDifference = fabs((2*m_leftLower.getY() + getHeight()) - (2*rectangle.getLeftLower().getY() + rectangle.getHeight()));
		return compare.isStrictFuzzySmaller(verticalDifference, heightSum);
	}
	else
		return false;
}
