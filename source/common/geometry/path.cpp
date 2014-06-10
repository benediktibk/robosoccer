#include "common/geometry/path.h"
#include "common/geometry/circle.h"
#include "common/geometry/line.h"
#include "common/geometry/angle.h"
#include "common/geometry/pathintersectpoints.h"
#include <math.h>

using namespace std;
using namespace RoboSoccer::Common::Geometry;

Path::Path(const Point &start, const Point &end, double width) :
	m_start(start),
	m_end(end),
	m_width(width)
{ }

bool Path::intersectsWith(const Circle &circle) const
{
	if(isCircleCenterOnPath(circle))
		return true;

	PathIntersectPoints intersectPoints = getIntersectPoints(circle);
	if (intersectPoints.getCount() != 0)
		return true;

	return false;
}

bool Path::isCircleCenterOnPath(const Circle &circle) const
{
	Point circleCenter = circle.getCenter();
	Angle angleBetweenPoints(m_start, m_end);

	circleCenter = circleCenter - m_start;
	circleCenter.rotate(Angle::getFullRotation() - angleBetweenPoints);
	if (circleCenter.getX() > -0.5*m_width && circleCenter.getX() < (m_start.distanceTo(m_end) + 0.5*m_width) && fabs(circleCenter.getY()) < 0.5*m_width)
		return true;
	else
		return false;
}

PathIntersectPoints Path::getIntersectPoints(const Circle &circle) const
{
	Angle angleBetweenPoints(m_start, m_end);
	double halfWidth = m_width/2;
	double diagonalHalfWidth = sqrt(2)*halfWidth;
	Point startLeft(m_start + Point(diagonalHalfWidth, Angle::getQuarterRotation() + Angle::getEighthRotation() + angleBetweenPoints));
	Point startRight(m_start + Point(diagonalHalfWidth, angleBetweenPoints - Angle::getQuarterRotation() - Angle::getEighthRotation()));
	Point endLeft(m_end + Point(diagonalHalfWidth, Angle::getEighthRotation() + angleBetweenPoints));
	Point endRight(m_end + Point(diagonalHalfWidth, angleBetweenPoints - Angle::getEighthRotation()));
	Line leftOutline(startLeft, endLeft);
	Line rightOutline(startRight, endRight);
	Line startOutline(startLeft, startRight);
	Line endOutline(endLeft, endRight);

	PathIntersectPoints intersectPointsLeft(leftOutline.getIntersectPoints(circle), PathIntersectPoints::IntersectTypeFromLeft);
	if(intersectPointsLeft.getCount() != 0)
		return intersectPointsLeft;
	PathIntersectPoints intersectPointsRight(rightOutline.getIntersectPoints(circle), PathIntersectPoints::IntersectTypeFromRight);
	if(intersectPointsRight.getCount() != 0)
		return intersectPointsRight;
	PathIntersectPoints intersectPointsStart(startOutline.getIntersectPoints(circle), PathIntersectPoints::IntersectTypeFromStart);
	if(intersectPointsStart.getCount() != 0)
		return intersectPointsStart;
	PathIntersectPoints intersectPointsEnd(endOutline.getIntersectPoints(circle), PathIntersectPoints::IntersectTypeFromEnd);
	if(intersectPointsEnd.getCount() != 0)
		return intersectPointsEnd;

	return PathIntersectPoints(vector<Point>(), PathIntersectPoints::IntersectTypeNoIntersect);
}

Angle Path::getAngleBetweenStartAndEnd() const
{
	return Angle(m_start, m_end);
}

Point Path::getLeftPerpendicularPoint(const Point &point) const
{
	Angle angleBetweenPoints(m_start, m_end);
	Point startLeft(m_start + Point(sqrt(2)*0.5*m_width, Angle::getQuarterRotation() + Angle::getEighthRotation() + angleBetweenPoints));
	Point endLeft(m_end + Point(sqrt(2)*0.5*m_width, Angle::getEighthRotation() + angleBetweenPoints));
	Line leftOutline(startLeft, endLeft);

	return leftOutline.getPerpendicularPoint(point);
}

Point Path::getRightPerpendicularPoint(const Point &point) const
{
	Angle angleBetweenPoints(m_start, m_end);
	Point startRight(m_start + Point(sqrt(2)*0.5*m_width, angleBetweenPoints - Angle::getQuarterRotation() - Angle::getEighthRotation()));
	Point endRight(m_end + Point(sqrt(2)*0.5*m_width, angleBetweenPoints - Angle::getEighthRotation()));
	Line rightOutline(startRight, endRight);

	return rightOutline.getPerpendicularPoint(point);
}

double Path::getDistanceToLeftPerpendicularPoint(const Point &point) const
{
	return point.distanceTo(getLeftPerpendicularPoint(point));
}

double Path::getDistanceToRightPerpendicularPoint(const Point &point) const
{
	return point.distanceTo(getRightPerpendicularPoint(point));
}

Line Path::getCenterLine() const
{
	return Line(m_start, m_end);
}
