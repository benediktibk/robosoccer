#include "layer/autonomous/robotstates/driveto.h"
#include "layer/autonomous/robotstates/reachedtarget.h"
#include "layer/abstraction/controllablerobot.h"
#include "common/geometry/compare.h"
#include "common/routing/route.h"
#include "common/routing/router.h"
#include "layer/autonomous/obstaclefetcher.h"
#include "layer/abstraction/readablerobot.h"
#include <assert.h>
#include <sstream>

using namespace std;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Time;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::Routing;

DriveTo::DriveTo(
		ControllableRobot &robot, Pose const &target, const Router &router,
		Logger &logger, Logger::LogFileType logFileType, ObstacleFetcher const &obstacleFetcher,
		ObstacleSource const &ownObstacleSource, bool ignoreBall, bool driveSlowlyAtTheEnd,
		bool ignoreGoalObstacles) :
	RobotState(robot, logger, logFileType),
	m_precisionPosition(0.02),
	m_precisionOrientationInitial(0.2),
	m_precisionOrientationFinal(0.1),
	m_ignoreBall(ignoreBall),
	m_driveSlowlyAtTheEnd(driveSlowlyAtTheEnd),
	m_ignoreGoalObstacles(ignoreGoalObstacles),
	m_target(target),
	m_router(router),
	m_obstacleFetcher(obstacleFetcher),
	m_ownObstacleSource(ownObstacleSource),
	m_currentRoute(new Route(ControllableRobot::getWidth()))
{ }

DriveTo::~DriveTo()
{
	clearRoute();
}

bool DriveTo::reachedTarget() const
{
	return false;
}

bool DriveTo::isEquivalentToDriveTo(const Pose &target) const
{
	Compare comparePosition(m_precisionPosition);
	Compare compareAngle(m_precisionOrientationInitial);

	return	comparePosition.isFuzzyEqual(m_target.getPosition(), target.getPosition()) &&
			compareAngle.isFuzzyEqual(m_target.getOrientation(), target.getOrientation());
}

bool DriveTo::isEquivalentToDriveToDirect(const Pose &) const
{
	return false;
}

vector<Circle> DriveTo::getAllObstaclesButMeInRangeDependentOnFlags(const Point &robotPoint, double distance) const
{
	if(m_ignoreBall)
		return m_obstacleFetcher.getAllObstaclesButMeAndBallInRange(m_ownObstacleSource, robotPoint, distance);
	else if(m_ignoreGoalObstacles)
		return m_obstacleFetcher.getAllObstaclesButMeAndGoalObstaclesInRange(m_ownObstacleSource, robotPoint, distance);
	else
		return m_obstacleFetcher.getAllObstaclesButMeInRange(m_ownObstacleSource, robotPoint, distance);
}

void DriveTo::clearRoute()
{
	delete m_currentRoute;
	m_currentRoute = 0;
}

void DriveTo::prepareLastRouteSegmentForDrivingSlowly()
{
	double lengthOfLastSegment = 0.15;

	if(m_currentRoute->getLengthOfLastSegment() > lengthOfLastSegment)
		m_currentRoute->splitLastSegment(lengthOfLastSegment);
}

size_t DriveTo::getRoutePointsCount() const
{
	return m_currentRoute->getPointCount();
}

Compare DriveTo::getPositionCompare() const
{
	return Compare(m_precisionPosition);
}

Compare DriveTo::getInitialRotationCompare() const
{
	return Compare(m_precisionOrientationInitial);
}

Compare DriveTo::getFinalRotationCompare() const
{
	return Compare(m_precisionOrientationFinal);
}

const Pose &DriveTo::getTarget() const
{
	return m_target;
}

const Router &DriveTo::getRouter() const
{
	return m_router;
}

const ObstacleFetcher &DriveTo::getObstacleFetcher() const
{
	return m_obstacleFetcher;
}

const ObstacleSource &DriveTo::getOwnObstacleSource() const
{
	return m_ownObstacleSource;
}

bool DriveTo::ignoreBall() const
{
	return m_ignoreBall;
}

bool DriveTo::driveSlowlyAtTheEnd() const
{
	return m_driveSlowlyAtTheEnd;
}

bool DriveTo::ignoreGoalObstacles() const
{
	return m_ignoreGoalObstacles;
}

const Route &DriveTo::getCurrentRoute() const
{
	assert(m_currentRoute != 0);
	return *m_currentRoute;
}

bool DriveTo::updateRouteIfNecessary()
{
	Point robotPoint = getRobot().getPose().getPosition();
	vector<Circle> obstacles = getAllObstaclesButMeInRangeDependentOnFlags(robotPoint, 1);
	vector<Circle> modifiedObstacles = modifyObstacles(obstacles, 0.9);

	if (isRouteFeasible(modifiedObstacles))
		return false;

	log("current route is not feasible anymore we try to create a new one");
	clearRoute();
	m_currentRoute = new Route(ReadableRobot::getWidth());
	calculateNewRoute();
	return true;
}

void DriveTo::setRoute(const Route &route)
{
	assert(m_currentRoute != 0);
	*m_currentRoute = route;
}

void DriveTo::calculateNewRoute()
{
	Point robotPoint = getRobot().getPose().getPosition();
	Point target = m_target.getPosition();
	vector<Circle> obstacles = getAllObstaclesButMeInRangeDependentOnFlags(robotPoint, 1);
	vector<Circle> modifiedObstacles = modifyObstacles(obstacles, 2);

	*m_currentRoute = m_router.calculateRoute(robotPoint, target, modifiedObstacles);

	if((m_driveSlowlyAtTheEnd || m_ignoreGoalObstacles) && m_currentRoute->isValid())
		prepareLastRouteSegmentForDrivingSlowly();

	logRoute();
}

const Point &DriveTo::getNextTargetPoint() const
{
	assert(m_currentRoute->getPointCount() >= 2);
	return m_currentRoute->getSecondPoint();
}

bool DriveTo::isRouteFeasible(const std::vector<Circle> &obstacles) const
{
	if (m_currentRoute == 0)
			return false;

	return	m_currentRoute->isValid() && !m_currentRoute->intersectsWith(obstacles);
}

vector<Circle> DriveTo::modifyObstacles(const vector<Circle> &obstacles, double growFactor) const
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

void DriveTo::logRoute()
{
	log("point count of route", m_currentRoute->getPointCount());
	stringstream stream;
	stream << "points: " << *m_currentRoute;
	log(stream.str());
}

void DriveTo::logCurrentPose()
{
	stringstream stream;
	stream << "current pose: " << getRobot().getPose();
	log(stream.str());
}
