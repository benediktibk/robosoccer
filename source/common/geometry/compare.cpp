#include "common/geometry/compare.h"
#include "common/geometry/point.h"
#include "common/geometry/circle.h"
#include "common/geometry/orientedposition.h"
#include <math.h>

using namespace RoboSoccer::Common::Geometry;
using namespace std;

Compare::Compare(double epsilon) :
	m_internalCompare(epsilon)
{ }

bool Compare::isFuzzyEqual(const Angle &one, const Angle &two) const
{
	return	m_internalCompare.isFuzzyEqual(one.getValueBetweenMinusPiAndPi(), two.getValueBetweenMinusPiAndPi()) ||
			m_internalCompare.isFuzzyEqual(one.getValueBetweenZeroAndTwoPi(), two.getValueBetweenZeroAndTwoPi());
}

bool Compare::isFuzzyEqual(const Point &one, const Point &two) const
{
	return	m_internalCompare.isFuzzyEqual(one.getX(), two.getX()) &&
			m_internalCompare.isFuzzyEqual(one.getY(), two.getY());
}

bool Compare::isFuzzyEqual(const Circle &one, const Circle &two) const
{
	return	isFuzzyEqual(one.getCenter(), two.getCenter()) &&
			m_internalCompare.isFuzzyEqual(one.getDiameter(), two.getDiameter());
}

bool Compare::isFuzzyEqual(const OrientedPosition &one, const OrientedPosition &two) const
{
	return	isFuzzyEqual(one.getPosition(), two.getPosition()) &&
			isFuzzyEqual(one.getOrientation(), two.getOrientation());
}

bool Compare::isFuzzyEqual(const list<OrientedPosition> &one, const list<OrientedPosition> &two) const
{
	list<OrientedPosition>::const_iterator j = two.begin();
	if(one.size() != two.size())
		return false;

	for(list<OrientedPosition>::const_iterator i = one.begin(); i != one.end(); ++i, ++j)
		if(!isFuzzyEqual((*i), (*j)))
			return false;

	return true;
}