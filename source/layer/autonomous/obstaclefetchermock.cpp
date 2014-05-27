#include "layer/autonomous/obstaclefetchermock.h"
#include "common/geometry/circle.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;
using namespace std;

ObstacleFetcherMock::ObstacleFetcherMock()
{ }

void ObstacleFetcherMock::addSource(const ObstacleSource &)
{ }

void ObstacleFetcherMock::defineBall(const ObstacleSource &)
{ }

vector<Circle> ObstacleFetcherMock::getAllObstacles() const
{
	return m_allObstacles;
}

vector<Circle> ObstacleFetcherMock::getAllObstaclesButMe(const ObstacleSource &) const
{
	return m_allObstaclesButMe;
}

vector<Circle> ObstacleFetcherMock::getAllObstaclesButMeInRange(
		const ObstacleSource &, const Point &, double) const
{
	return m_allObstaclesButMeInRange;
}

vector<Circle> ObstacleFetcherMock::getAllObstaclesButMeAndBallInRange(const ObstacleSource &, const Point &, double) const
{
	return m_allObstaclesButMeAndBallInRange;
}

void ObstacleFetcherMock::setAllObstacles(const vector<Circle> &obstacles)
{
	m_allObstacles = obstacles;
}

void ObstacleFetcherMock::setAllObstaclesButMe(const vector<Circle> &obstacles)
{
	m_allObstaclesButMe = obstacles;
}

void ObstacleFetcherMock::setAllObstaclesButMeInRange(const vector<Circle> &obstacles)
{
	m_allObstaclesButMeInRange = obstacles;
}

void ObstacleFetcherMock::setAllObstaclesButMeAndBallInRange(const vector<Circle> &obstacles)
{
	m_allObstaclesButMeAndBallInRange = obstacles;
}
