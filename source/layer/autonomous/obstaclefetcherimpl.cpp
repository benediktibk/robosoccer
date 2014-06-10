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
{
	double xCoordinateRightSide = 1.45 - 0.125;
	double diameterAndDistanceToNextObstacle = 0.25;

	m_routingObstaclesInGoalZones.push_back(Circle(Point(xCoordinateRightSide,0),diameterAndDistanceToNextObstacle));
	m_routingObstaclesInGoalZones.push_back(Circle(Point(-xCoordinateRightSide,0),diameterAndDistanceToNextObstacle));
	m_routingObstaclesInGoalZones.push_back(Circle(Point(xCoordinateRightSide,diameterAndDistanceToNextObstacle),diameterAndDistanceToNextObstacle));
	m_routingObstaclesInGoalZones.push_back(Circle(Point(-xCoordinateRightSide,diameterAndDistanceToNextObstacle),diameterAndDistanceToNextObstacle));
	m_routingObstaclesInGoalZones.push_back(Circle(Point(xCoordinateRightSide,-diameterAndDistanceToNextObstacle),diameterAndDistanceToNextObstacle));
	m_routingObstaclesInGoalZones.push_back(Circle(Point(-xCoordinateRightSide,-diameterAndDistanceToNextObstacle),diameterAndDistanceToNextObstacle));
}

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
	vector<Circle> result = m_routingObstaclesInGoalZones;

	for (vector<ObstacleSource const *>::const_iterator i = m_sources.begin(); i != m_sources.end(); ++i)
	{
		ObstacleSource const &source = **i;
		vector<Circle> resultPart = source.getObstacles();
		result.insert(result.end(), resultPart.begin(), resultPart.end());
	}

	return result;
}

vector<Circle> ObstacleFetcherImpl::getAllObstaclesButMe(const ObstacleSource &me, double growFactor) const
{
	vector<Circle> result = m_routingObstaclesInGoalZones;

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

vector<Circle> ObstacleFetcherImpl::getAllObstaclesButMeAndBall(const ObstacleSource &me, double growFactor) const
{
	vector<Circle> result = m_routingObstaclesInGoalZones;

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

vector<Circle> ObstacleFetcherImpl::getAllObstaclesButMeAndGoalObstacles(const ObstacleSource &me, double growFactor) const
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
		const ObstacleSource &me, const Point &ownPosition, double distance, double growFactor) const
{
	vector<Circle> candidates = getAllObstaclesButMe(me, growFactor);
	return filterByDistance(candidates, ownPosition, distance);
}

vector<Circle> ObstacleFetcherImpl::getAllObstaclesButMeAndBallInRange(
		const ObstacleSource &me, const Point &ownPosition, double distance, double growFactor) const
{
	vector<Circle> candidates = getAllObstaclesButMeAndBall(me, growFactor);
	return filterByDistance(candidates, ownPosition, distance);
}

vector<Circle> ObstacleFetcherImpl::getAllObstaclesButMeAndGoalObstaclesInRange(const ObstacleSource &me, const Point &ownPosition, double distance, double growFactor) const
{
	vector<Circle> candidates = getAllObstaclesButMeAndGoalObstacles(me, growFactor);
	return filterByDistance(candidates, ownPosition, distance);
}

vector<Circle> ObstacleFetcherImpl::getAllObstaclesButMeInRangeDependentOnDriveMode(const ObstacleSource &me, const Point &ownPosition, double distance, DriveMode driveMode, double growFactor) const
{
	switch (driveMode)
	{
	case DriveModeIgnoreBall:
	case DriveModeIgnoreBallAndDriveSlowlyAtTheEnd:
		return getAllObstaclesButMeAndBallInRange(me, ownPosition, distance, growFactor);
	case DriveModeIgnoreGoalObstacles:
		return getAllObstaclesButMeAndGoalObstaclesInRange(me, ownPosition, distance, growFactor);
	case DriveModeDriveSlowlyAtTheEnd:
	case DriveMoveDefault:
		break;
	}
	return getAllObstaclesButMeInRange(me, ownPosition, distance, growFactor);
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

vector<Circle> ObstacleFetcherImpl::modifyObstacles(const vector<Circle> &obstacles, double growFactor) const
{
	vector<Circle> result;
	result.reserve(obstacles.size());

	for (vector<Circle>::const_iterator i = obstacles.begin(); i != obstacles.end(); ++i)
	{
		Circle circle = *i;
		double diameter = circle.getDiameter();
		circle.setDiameter(diameter*growFactor);
		result.push_back(circle);
	}

	return result;
}
