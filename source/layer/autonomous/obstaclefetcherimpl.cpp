#include "layer/autonomous/obstaclefetcherimpl.h"
#include "layer/autonomous/robot.h"
#include "layer/autonomous/obstaclesource.h"
#include "common/geometry/circle.h"
#include "layer/abstraction/readablerobot.h"
#include <assert.h>

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;
using namespace std;

ObstacleFetcherImpl::ObstacleFetcherImpl() :
	m_ball(0)
{ }

ObstacleFetcherImpl::~ObstacleFetcherImpl()
{
	m_sources.clear();
	m_ball = 0;
}

void ObstacleFetcherImpl::addSource(const ObstacleSource &source)
{
	m_sources.push_back(&source);
}

void ObstacleFetcherImpl::defineBall(const ObstacleSource &source)
{
	m_ball = &source;
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

vector<Circle> ObstacleFetcherImpl::getAllObstaclesButMeAndBall(const ObstacleSource &me) const
{
	vector<Circle> result;

	for (vector<ObstacleSource const *>::const_iterator i = m_sources.begin(); i != m_sources.end(); ++i)
	{
		ObstacleSource const &source = **i;

		if (&source == &me || &source == m_ball)
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
	return filterByDistance(candidates, ownPosition, distance);
}

vector<Circle> ObstacleFetcherImpl::getAllObstaclesButMeAndBallInRange(
		const ObstacleSource &me, const Point &ownPosition, double distance) const
{
	vector<Circle> candidates = getAllObstaclesButMeAndBall(me);
	return filterByDistance(candidates, ownPosition, distance);
}

vector<Circle> ObstacleFetcherImpl::filterByDistance(
		const vector<Circle> &candidates, const Point &ownPosition, double distance) const
{
	vector<Circle> result;
	result.reserve(candidates.size());

	for (vector<Circle>::const_iterator i = candidates.begin(); i != candidates.end(); ++i)
	{
		Circle const &circle = *i;

		if (isInRange(ownPosition, distance, circle))
			result.push_back(circle);
	}

	return result;
}

bool ObstacleFetcherImpl::isInRange(const Point &ownPosition, double distance, const Circle &circle) const
{
	double distanceToCenter = ownPosition.distanceTo(circle.getCenter());
	double distanceToEdge = distanceToCenter - circle.getDiameter()/2;
	return distanceToEdge <= distance;
}
