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

void ObstacleFetcherMock::defineOwnTeam(const ObstacleSource &)
{ }

vector<Circle> ObstacleFetcherMock::getAllObstacles() const
{
	return m_allObstacles;
}

vector<Circle> ObstacleFetcherMock::getAllObstaclesButMe(const ObstacleSource &, double) const
{
	return m_allObstaclesButMe;
}

vector<Circle> ObstacleFetcherMock::getAllObstaclesButMeAndBall(const ObstacleSource &, double) const
{
	return m_allObstaclesButMeAndBall;
}

vector<Circle> ObstacleFetcherMock::getAllObstaclesButMeAndGoalObstacles(const ObstacleSource &, double) const
{
	return m_allObstaclesButMeAndGoalObstacles;
}

vector<Circle> ObstacleFetcherMock::getAllObstaclesButMeInRange(const ObstacleSource &, const Point &, double, double) const
{
	return m_allObstaclesButMeInRange;
}

vector<Circle> ObstacleFetcherMock::getAllObstaclesButMeAndBallInRange(const ObstacleSource &, const Point &, double, double ) const
{
	return m_allObstaclesButMeAndBallInRange;
}

vector<Circle> ObstacleFetcherMock::getAllObstaclesButMeAndGoalObstaclesInRange(const ObstacleSource &, const Point &, double, double ) const
{
	return m_allObstaclesButMeAndGoalObstaclesInRange;
}

vector<Circle> ObstacleFetcherMock::getAllObstaclesButMeInRangeDependentOnDriveMode(const ObstacleSource &, const Point &, double, DriveMode, double) const
{
	return m_allObstaclesButMeDependentOnDriveMode;
}

vector<Circle> ObstacleFetcherMock::getAllObstaclesButOwnTeamAndGoalObstacles() const
{
	return vector<Circle>();
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

void ObstacleFetcherMock::setAllObstaclesButMeInRangeDependentOnDriveMode(const std::vector<Circle> &obstacles)
{
	m_allObstaclesButMeDependentOnDriveMode = obstacles;
}
