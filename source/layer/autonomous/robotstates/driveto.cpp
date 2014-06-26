#include "layer/autonomous/robotstates/driveto.h"
#include "layer/autonomous/robotstates/reachedtarget.h"
#include "layer/autonomous/robotstates/drivetoinitialrotation.h"
#include "layer/autonomous/robotstates/drivetoinvalidroute.h"
#include "layer/abstraction/controllablerobot.h"
#include "common/geometry/compare.h"
#include "common/routing/route.h"
#include "common/routing/router.h"
#include "layer/autonomous/obstaclefetcher.h"
#include "layer/abstraction/readablerobot.h"
#include "layer/abstraction/fieldpositionchecker.h"
#include <assert.h>
#include <sstream>

using namespace std;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Time;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common;

DriveTo::DriveTo(ControllableRobot &robot, const vector<Pose> &targets, const Pose &currentTarget, const Routing::Router &router,
		Logger &logger, Logger::LogFileType logFileType, ObstacleFetcher const &obstacleFetcher,
		ObstacleSource const &ownObstacleSource, DriveMode driveMode, FieldPositionChecker const &fieldPositionChecker) :
	RobotState(robot, logger, logFileType),
	m_precisionPosition(0.02),
	m_precisionOrientationInitial(0.2),
	m_precisionOrientationFinal(0.1),
	m_driveMode(driveMode),
	m_targets(targets),
	m_currentTarget(currentTarget),
	m_router(router),
	m_obstacleFetcher(obstacleFetcher),
	m_ownObstacleSource(ownObstacleSource),
	m_currentRoute(new Routing::Route(ControllableRobot::getWidth())),
	m_proposalRoute(new Routing::Route(ControllableRobot::getWidth())),
	m_fieldPositionChecker(fieldPositionChecker)
{ }

DriveTo::~DriveTo()
{
	clearRoute();
	clearProposalRoute();
}

bool DriveTo::reachedTarget() const
{
	return false;
}

bool DriveTo::isEquivalentToDriveTo(const vector<Pose> &targets)
{
	Compare comparePosition(m_precisionPosition*4);

	if (!comparePosition.isFuzzyEqualWithCorrectOrder(m_targets, targets, 4*m_precisionOrientationFinal))
	{
		log("position or orientation is not equal");
		return false;
	}

	return true;
}

bool DriveTo::isEquivalentToDriveToDirect(const Pose &)
{
	return false;
}

void DriveTo::clearRoute()
{
	delete m_currentRoute;
	m_currentRoute = 0;
}

void DriveTo::clearProposalRoute()
{
	delete m_proposalRoute;
	m_proposalRoute = 0;
}

void DriveTo::prepareLastRouteSegmentForDrivingSlowly(Routing::Route &route)
{
	double lengthOfLastSegment = 0.15;

	if(route.getLengthOfLastSegment() > lengthOfLastSegment)
		route.splitLastSegment(lengthOfLastSegment);
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

const vector<Pose> &DriveTo::getTargets() const
{
	return m_targets;
}

const Pose &DriveTo::getCurrentTarget() const
{
	return m_currentTarget;
}

const Routing::Router &DriveTo::getRouter() const
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

DriveMode DriveTo::getDriveMode() const
{
	return m_driveMode;
}

Routing::Route DriveTo::getCurrentRoute() const
{
	assert(m_currentRoute != 0);
	return *m_currentRoute;
}

vector<Pose> DriveTo::getCurrentTargets() const
{
	return m_targets;
}

const FieldPositionChecker &DriveTo::getFieldPositionChecker() const
{
	return m_fieldPositionChecker;
}

bool DriveTo::updateRouteIfNecessary()
{
	Pose currentPose = getRobot().getPose();
	Point const &currentPosition = currentPose.getPosition();
	DriveMode driveMode = getDriveModeOverriden();
	vector<Circle> obstacles = m_obstacleFetcher.getAllObstaclesButMeInRangeDependentOnDriveMode(
				m_ownObstacleSource, currentPosition, 1, driveMode, 0.9);
	vector<Circle> filteredObstacles = m_router.filterObstacles(obstacles, currentPosition);

	if (m_currentRoute != 0 && m_currentRoute->isValid())
		m_currentRoute->replaceFirstPoint(currentPosition);

	if (isRouteFeasible(filteredObstacles))
	{
		if(m_currentRoute->getLength() < 0.2)
			return false;
		if(!existsBetterRoute())
			return false;
		else
		{
			delete m_currentRoute;
			m_currentRoute = m_proposalRoute;
			m_proposalRoute = 0;
			log("current route is to long so we take a better one");
		}
	}
	else
	{
		log("current route is not feasible anymore we try to create a new one");
		clearRoute();
		m_currentRoute = new Routing::Route(ReadableRobot::getWidth());
		calculateNewRoute(*m_currentRoute);
	}
	return true;
}

void DriveTo::setRoute(const Routing::Route &route)
{
	assert(m_currentRoute != 0);
	*m_currentRoute = route;
}

RobotState *DriveTo::nextStateWithRouteUpdate()
{
	bool routeUpdated = updateRouteIfNecessary();
	Routing::Route const &currentRoute = getCurrentRoute();

	if (!currentRoute.isValid())
	{
		log("route is invalid");
		return new DriveToInvalidRoute(
					getRobot(), getTargets(), getCurrentTarget(), getRouter(), getLogger(), getLogFileType(),
					getObstacleFetcher(), getOwnObstacleSource(), getDriveMode(), getFieldPositionChecker());
	}

	if (routeUpdated)
	{
		log("created new route, starting with initial rotation");
		return new DriveToInitialRotation(
					getRobot(), getTargets(), getCurrentTarget(), getRouter(), getLogger(), getLogFileType(),
					getObstacleFetcher(), getOwnObstacleSource(), getDriveMode(), currentRoute, getFieldPositionChecker());
	}

	return 0;
}

DriveMode DriveTo::getDriveModeOverriden() const
{
	Pose currentPose = 	getRobot().getPose();
	Point const &currentPosition = currentPose.getPosition();
	DriveMode driveMode = m_driveMode;

	if (m_fieldPositionChecker.isPointInsideGoalZone(currentPosition))
		driveMode = DriveModeIgnoreGoalObstacles;

	return driveMode;
}

void DriveTo::calculateNewRoute(Routing::Route &route)
{
	Pose currentPose = 	getRobot().getPose();
	Point const &currentPosition = currentPose.getPosition();
	DriveMode driveMode = getDriveModeOverriden();

	for (unsigned int i = 0; i < m_targets.size(); ++i)
	{
		Point target = m_targets[i].getPosition();
		vector<Circle> obstacles = m_obstacleFetcher.getAllObstaclesButMeInRangeDependentOnDriveMode(
				m_ownObstacleSource, currentPosition, 1, driveMode, 2);

		route = m_router.calculateRoute(currentPosition, target, obstacles);

		if (route.isValid())
			break;
	}

	if((driveMode == DriveModeDriveSlowlyAtTheEnd || driveMode == DriveModeIgnoreGoalObstacles
		|| driveMode == DriveModeIgnoreBallAndDriveSlowlyAtTheEnd) && route.isValid())
		prepareLastRouteSegmentForDrivingSlowly(route);

	logRoute();
}

bool DriveTo::existsBetterRoute()
{
	clearProposalRoute();
	m_proposalRoute = new Routing::Route(ReadableRobot::getWidth());
	calculateNewRoute(*m_proposalRoute);

	if(!m_proposalRoute->isValid())
		return false;

	double reducedLenghtOfCurrentRoute = 0.8*m_currentRoute->getLength();
	return m_proposalRoute->getLength() < reducedLenghtOfCurrentRoute;
}

const Point &DriveTo::getNextTargetPoint() const
{
	assert(m_currentRoute->getPointCount() >= 2);
	return m_currentRoute->getSecondPoint();
}

bool DriveTo::isRouteFeasible(const vector<Circle> &obstacles) const
{
	if (m_currentRoute == 0)
			return false;

	return	m_currentRoute->isValid() && !m_currentRoute->intersectsWith(obstacles);
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
