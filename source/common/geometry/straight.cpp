#include "common/geometry/straight.h"
#include "common/geometry/circle.h"

using namespace std;
using namespace RoboSoccer::Common::Geometry;

Straight::Straight(const Point &referencePoint, const Angle &direction) :
	m_referencePoint(referencePoint),
	m_direction(direction)
{ }

vector<Point> Straight::getIntersectPoint(const Straight &straight) const
{
	vector<Point> intersectPoint;
	intersectPoint.reserve(1);
	Point vectorOne = getNormalizedDirectionVector();
	Point vectorTwo = straight.getNormalizedDirectionVector();
	double determinantSolutionMatrix = vectorTwo.getX()*(-vectorOne.getY()) + vectorTwo.getY()*vectorOne.getX();

	if (determinantSolutionMatrix != 0)
	{
		double percentOfLineOne = (-vectorTwo.getY()*(m_referencePoint.getX()-straight.getReferencePoint().getX()) +
								   vectorTwo.getX()*(m_referencePoint.getY()-straight.getReferencePoint().getY())) / determinantSolutionMatrix;

		intersectPoint.push_back(m_referencePoint + vectorOne*percentOfLineOne);
	}

	return intersectPoint;
}

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
	point.rotate(m_direction * -1.0);

	return point.getY() < 0;
}

Point Straight::getNormalizedDirectionVector() const
{
	return Point(1,m_direction);
}

Point Straight::getReferencePoint() const
{
	return m_referencePoint;
}
