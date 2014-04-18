#include "common/geometry/pointdistancecompare.h"

using namespace RoboSoccer::Common::Geometry;


PointDistanceCompare::PointDistanceCompare(const Point &position) :
	m_position(position)
{ }

bool PointDistanceCompare::operator ()(const Point &one, const Point &two) const
{
	double distanceOne = one.distanceTo(m_position);
	double distanceTwo = two.distanceTo(m_position);
	return distanceOne < distanceTwo;
}

