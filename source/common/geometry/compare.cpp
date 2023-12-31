#include "common/geometry/compare.h"
#include "common/geometry/point.h"
#include "common/geometry/circle.h"
#include "common/geometry/pose.h"
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

bool Compare::isFuzzyEqual(const Pose &one, const Pose &two) const
{
	return	isFuzzyEqual(one.getPosition(), two.getPosition()) &&
			isFuzzyEqual(one.getOrientation(), two.getOrientation());
}

bool Compare::isFuzzyEqual(const list<Point> &one, const list<Point> &two) const
{
	if (one.size() != two.size())
		return false;

	list<Point>::const_iterator i = one.begin();
	list<Point>::const_iterator j = two.begin();

	for (; i != one.end() && j != two.end(); ++i, ++j)
		if (!isFuzzyEqual(*i, *j))
			return false;

	return true;
}

bool Compare::isFuzzyEqualWithCorrectOrder(const vector<Pose> &one, const vector<Pose> &two) const
{
	vector<Pose>::const_iterator j = two.begin();
	if(one.size() != two.size())
		return false;

	for(vector<Pose>::const_iterator i = one.begin(); i != one.end(); ++i, ++j)
		if(!isFuzzyEqual((*i), (*j)))
			return false;

	return true;
}

bool Compare::isFuzzyEqualWithCorrectOrder(const std::vector<Pose> &one, const std::vector<Pose> &two, double angleCompare) const
{
	Compare angle(angleCompare);
	vector<Pose>::const_iterator j = two.begin();
	if(one.size() != two.size())
		return false;

	for(vector<Pose>::const_iterator i = one.begin(); i != one.end(); ++i, ++j)
	{
		const Pose &poseOne = *i;
		const Pose &poseTwo = *j;

		if(!(isFuzzyEqual(poseOne.getPosition(), poseTwo.getPosition()) &&
				angle.isFuzzyEqual(poseOne.getOrientation(), poseTwo.getOrientation())))
			return false;
	}
	return true;
}
