#include "common/geometry/pathintersectpoints.h"

using namespace RoboSoccer::Common::Geometry;
using namespace std;

PathIntersectPoints::PathIntersectPoints(vector<Point> intersectPoints, IntersectType intersectFrom) :
	m_intersectPoints(intersectPoints),
	m_intersectFrom(intersectFrom)
{ }

vector<Point> PathIntersectPoints::getIntersectPoints()
{
	return m_intersectPoints;
}

PathIntersectPoints::IntersectType PathIntersectPoints::getIntersectTypeFrom()
{
	return m_intersectFrom;
}

size_t PathIntersectPoints::getCount()
{
	return m_intersectPoints.size();
}

Point PathIntersectPoints::front()
{
	return m_intersectPoints.front();
}

Point PathIntersectPoints::back()
{
	return m_intersectPoints.back();
}

