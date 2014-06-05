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

vector<Circle> ObstacleFetcherMock::getAllObstaclesButMeAndBall(const ObstacleSource &) const
{
	return m_allObstaclesButMeAndBall;
}

vector<Circle> ObstacleFetcherMock::getAllObstaclesButMeAndGoalObstacles(const ObstacleSource &) const
{
	return m_allObstaclesButMeAndGoalObstacles;
}

vector<Circle> ObstacleFetcherMock::getAllObstaclesButMeInRange(const ObstacleSource &, const Point &, double) const
{
	return m_allObstaclesButMeInRange;
}

vector<Circle> ObstacleFetcherMock::getAllObstaclesButMeAndBallInRange(const ObstacleSource &, const Point &, double) const
{
	return m_allObstaclesButMeAndBallInRange;
}

vector<Circle> ObstacleFetcherMock::getAllObstaclesButMeAndGoalObstaclesInRange(const ObstacleSource &, const Point &, double) const
{
	return m_allObstaclesButMeAndGoalObstaclesInRange;
}

vector<Circle> ObstacleFetcherMock::getAllObstaclesButMeInRangeDependentOnDriveMode(const ObstacleSource &, const Point &, double, bool , bool) const
{
	return m_allObstaclesButMeDependentOnDriveMode;
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

void ObstacleFetcherMock::setAllObstaclesButMeAndGoalObstaclesInRange(const std::vector<Circle> &obstacles)
{
	m_allObstaclesButMeAndGoalObstaclesInRange = obstacles;
}

void ObstacleFetcherMock::setAllObstaclesButMeDependentOn(const std::vector<Circle> &obstacles)
{
	m_allObstaclesButMeDependentOnDriveMode = obstacles;
}
