#include "layer/autonomous/obstaclefetcherimpl.h"
#include "layer/autonomous/enemyteam.h"
#include "layer/autonomous/team.h"
#include "layer/autonomous/intelligentball.h"
#include "layer/autonomous/robot.h"
#include "layer/autonomous/obstaclesource.h"
#include "common/geometry/circle.h"
#include "layer/abstraction/readablerobot.h"
#include <assert.h>

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;
using namespace std;

ObstacleFetcherImpl::ObstacleFetcherImpl(const Team &team, const EnemyTeam &enemyTeam, const IntelligentBall &ball)
{
	const size_t sourceCount = 5;
	m_sources.reserve(sourceCount);
	m_sources.push_back(&enemyTeam);
	m_sources.push_back(&ball);

	for (unsigned int i = 0; i < 3; i++)
	{
		Robot const &robot = team.getRobotByNumber(i);
		m_sources.push_back(&robot);
	}

	assert(m_sources.size() == sourceCount);
}

ObstacleFetcherImpl::~ObstacleFetcherImpl()
{
	m_sources.clear();
}

vector<Circle> ObstacleFetcherImpl::getAllObstacles() const
{
	vector<Circle> result;

	for (vector<ObstacleSource const *>::const_iterator i = m_sources.begin(); i != m_sources.end(); ++i)
	{
		ObstacleSource const &source = **i;
		vector<Circle> resultPart = source.getObstacles();
		result.insert(result.end(), resultPart.begin(), resultPart.end());
	}

	return result;
}

vector<Circle> ObstacleFetcherImpl::getAllObstaclesButMe(const ObstacleSource &me) const
{
	vector<Circle> result;

	for (vector<ObstacleSource const *>::const_iterator i = m_sources.begin(); i != m_sources.end(); ++i)
	{
		ObstacleSource const &source = **i;

		if (&source == &me)
			continue;

		vector<Circle> resultPart = source.getObstacles();
		result.insert(result.end(), resultPart.begin(), resultPart.end());
	}

	return result;
}

vector<Circle> ObstacleFetcherImpl::getAllObstaclesButMeInRange(
		const ObstacleSource &me, const Point &ownPosition, double distance) const
{
	vector<Circle> candidates = getAllObstaclesButMe(me);
	vector<Circle> result;
	result.reserve(candidates.size());

	for (vector<Circle>::const_iterator i = candidates.begin(); i != candidates.end(); ++i)
	{
		Circle const &circle = *i;
		double distanceToCenter = ownPosition.distanceTo(circle.getCenter());
		double distanceToEdge = distanceToCenter - circle.getDiameter();

		if (distanceToEdge <= distance)
			result.push_back(circle);
	}

	return result;
}
