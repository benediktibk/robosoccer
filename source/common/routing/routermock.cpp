#include "common/routing/routermock.h"
#include "common/geometry/pose.h"

using namespace std;
using namespace RoboSoccer::Common::Routing;
using namespace RoboSoccer::Common::Geometry;

RouterMock::RouterMock() :
	m_chessMode(false),
	m_routeSet(false)
{ }

Route RouterMock::calculateRoute(
		const Point &start, const Point &end, const vector<Circle> &) const
{
	if (m_routeSet)
		return m_route;

	Route route(0.38);
	route.addPoint(start);
	if (m_chessMode)
		route.addPoint(Point(start.getX(), end.getY()));
	route.addPoint(end);
	return route;
}

vector<Circle> RouterMock::filterObstacles(const vector<Circle> &obstacles, const Point &) const
{
	return obstacles;
}

void RouterMock::setChessMode(bool value)
{
	m_chessMode = value;
}

void RouterMock::setRoute(const Point &one, const Point &two, const Point &three)
{
	m_routeSet = true;
	m_route = Route(0.38);
	m_route.addPoint(one);
	m_route.addPoint(two);
	m_route.addPoint(three);
}

void RouterMock::setInvalidRoute()
{
	m_routeSet = true;
	m_route = Route(0.38);
}
