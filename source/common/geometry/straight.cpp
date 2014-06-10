#include "common/geometry/straight.h"
#include "common/geometry/circle.h"

using namespace std;
using namespace RoboSoccer::Common::Geometry;

Straight::Straight(const Point &referencePoint, const Angle &direction) :
	m_referencePoint(referencePoint),
	m_direction(direction)
{ }

Point Straight::getPerpendicularPoint(const Point &point) const
{
	Point target = point - m_referencePoint;
	target.rotate(Angle() - m_direction);

	Point result(target.getX(), 0);
	result.rotate(m_direction);
	result = result + m_referencePoint;

	return result;
}

bool Straight::isTargetPointRightOfLine(const Point &target) const
{
	Point point = target - m_referencePoint;
	point.rotate(Angle() - m_direction);

	return point.getY() < 0;
}
