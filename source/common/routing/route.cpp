#include "common/routing/route.h"
#include "common/geometry/path.h"
#include "common/geometry/angle.h"
#include "common/geometry/pose.h"
#include "common/other/signum.h"
#include "common/geometry/line.h"
#include <assert.h>
#include <math.h>
#include <algorithm>

using namespace std;
using namespace RoboSoccer::Common::Routing;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Other;


Route::Route() :
	m_width(0)
{ }

Route::Route(double width) :
	m_width(width)
{
	assert(m_width > 0);
}

void Route::addPoint(const Point &point)
{
	m_points.push_back(point);
}

void Route::add(const Route &route)
{
	assert(getLastPoint() == route.getFirstPoint());

	list<Point>::const_iterator begin = route.m_points.begin();
	++begin;
	m_points.insert(m_points.end(), begin, route.m_points.end());
}

size_t Route::getPointCount() const
{
	return m_points.size();
}

bool Route::isValid() const
{
	return getPointCount() >= 1 && m_width > 0;
}

const Point &Route::getLastPoint() const
{
	assert(getPointCount() > 0);
	return m_points.back();
}

const Point &Route::getNextToLastPoint() const
{
	assert(getPointCount() > 1);
	list<Point>::const_reverse_iterator iterator = m_points.rbegin();
	++iterator;
	return *iterator;
}

const Point &Route::getSecondPoint() const
{
	assert(getPointCount() > 1);
	list<Point>::const_iterator iterator = m_points.begin();
	++iterator;
	return *iterator;
}

const Point &Route::getFirstPoint() const
{
	assert(getPointCount() > 0);
	return m_points.front();
}

const Point &Route::getThirdPoint() const
{
	assert(getPointCount() >= 3);
	list<Point>::const_iterator iterator = m_points.begin();
	++iterator;
	++iterator;
	return *iterator;
}

list<Point> Route::getAllPoints() const
{
	return m_points;
}

void Route::removeFirstPoint()
{
	assert(getPointCount() > 0);
	m_points.pop_front();
}

double Route::getWidth() const
{
	return m_width;
}

bool Route::intersectsWith(const vector<Circle> &objects) const
{
	list<Point>::const_iterator pointsEnd = m_points.end();
	--pointsEnd;

	for(list<Point>::const_iterator k = m_points.begin(); k != pointsEnd; ++k)
	{
		list<Point>::const_iterator nextElement = k;
		++nextElement;
		Path currentPath(*k,*nextElement, m_width);
		for(vector<Circle>::const_iterator i = objects.begin(); i != objects.end(); ++i)
			if(currentPath.intersectsWith(*i))
				return true;
	}

	return false;
}

void Route::replaceFirstPoint(const Point &point)
{
	assert(isValid());
	*(m_points.begin()) = point;
}

double Route::getLength() const
{
	double totalLength = 0;
	list<Point>::const_iterator end = m_points.end();
	--end;

	for (list<Point>::const_iterator i = m_points.begin(); i != end; ++i)
	{
		list<Point>::const_iterator next = i;
		++next;
		const Point &currentPoint = *i;
		const Point &nextPoint = *next;
		totalLength += currentPoint.distanceTo(nextPoint);
	}

	return totalLength;
}

double Route::getLengthOfLastSegment() const
{
	Point lastPoint = getLastPoint();
	Point nextToLastPoint = getNextToLastPoint();

	return lastPoint.distanceTo(nextToLastPoint);
}

void Route::splitLastSegment(double lengthOfLastSegment)
{
	Point lastPoint = getLastPoint();
	Point nextToLastPoint = getNextToLastPoint();
	Line lastSegment(lastPoint,nextToLastPoint);
	Point midPoint(lastSegment.getPointOnDirectionOfLine(lengthOfLastSegment/lastSegment.getLength()));

	m_points.pop_back();
	m_points.push_back(midPoint);
	m_points.push_back(lastPoint);
}

ostream& operator<<(ostream &stream, const Route &route)
{
	list<Point> points = route.getAllPoints();

	if (points.empty())
		return stream;

	stream << points.front();
	list<Point>::const_iterator i = points.begin();
	++i;
	for (; i != points.end(); ++i)
		stream << " - " << *i;

	return stream;
}
