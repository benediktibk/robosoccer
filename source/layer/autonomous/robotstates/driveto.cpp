#include "layer/autonomous/robotstates/driveto.h"
#include "layer/autonomous/robotstates/reachedtarget.h"
#include "layer/abstraction/controllablerobot.h"
#include "common/geometry/compare.h"
#include "common/time/stopwatch.h"
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

DriveTo::DriveTo(Abstraction::ControllableRobot &robot, Pose const &target, const Router &router,
		Watch const &watch, Logger &logger, Logger::LogFileType logFileType, ObstacleFetcher &obstacleFetcher,
		ObstacleSource &autonomousRobot, bool ignoreBall, bool driveSlowlyAtTheEnd, bool ignoreGoalObstacles) :
	RobotState(robot, logger, logFileType),
	m_precisionPosition(0.02),
	m_precisionOrientationInitial(0.2),
	m_precisionOrientationFinal(0.1),
	m_initialRotationReached(false),
	m_initialRotationStarted(false),
	m_driveStarted(false),
	m_finalRotationReached(false),
	m_finalRotationStarted(false),
	m_movementStopUsed(false),
	m_ignoreBall(ignoreBall),
	m_driveSlowlyAtTheEnd(driveSlowlyAtTheEnd),
	m_ignoreGoalObstacles(ignoreGoalObstacles),
	m_target(target),
	m_router(router),
	m_watchDog(new StopWatch(watch)),
	m_currentRoute(0),
	m_obstacleFetcher(obstacleFetcher),
	m_autonomousRobot(autonomousRobot)
{
	m_watchDog->getTimeAndRestart();
}

DriveTo::~DriveTo()
{
	delete m_watchDog;
	m_watchDog = 0;
	clearRoute();
}

bool DriveTo::reachedTarget() const
{
	return false;
}

RobotState *DriveTo::nextState(bool)
{
	Compare comparePosition(m_precisionPosition);
	Compare compareAngle(m_precisionOrientationFinal);
	Pose pose = getRobot().getPose();

	if (	(	comparePosition.isFuzzyEqual(pose.getPosition(), m_target.getPosition()) &&
				compareAngle.isFuzzyEqual(pose.getOrientation(), m_target.getOrientation())) ||
			 m_finalRotationReached)
		return new ReachedTarget(getRobot(), getLogger(), getLogFileType());
	else if (m_watchDog->getTime() > 10)
		return new ReachedTarget(getRobot(), getLogger(), getLogFileType());
	else
		return 0;
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

void DriveTo::updateInternal(bool movementStopped)
{
	Pose robotPose = getRobot().getPose();
	m_movementStopUsed = false;

	updateRoute();

	if (!m_currentRoute->isValid())
		return;

	if(m_currentRoute->getPointCount() >= 2)
	{
		if(setOrdersForIntermediatePointAndGetOrderSet(movementStopped))
			return;

		resetAllMovementFlags();

		if(m_currentRoute->getPointCount() >= 2)
		{
			if(setOrdersForIntermediatePointAndGetOrderSet(movementStopped))
				return;
		}
	}

	if (!m_finalRotationReached && m_currentRoute->getPointCount() < 2)
	{
		Compare compareAngle(m_precisionOrientationFinal);
		if (compareAngle.isFuzzyEqual(robotPose.getOrientation(), m_target.getOrientation()))
		{
			log("final rotation reached");
			m_finalRotationReached = true;
			m_movementStopUsed = true;
		}
		else if (movementStopped && !m_movementStopUsed)
		{
			log("final rotation not really reached, but movement stopped");
			m_movementStopUsed = true;
			m_finalRotationReached = true;
		}
		else
		{
			if (!m_finalRotationStarted)
				getRobot().turn(m_target.getOrientation());

			m_finalRotationStarted = true;
			return;
		}
	}
}

bool DriveTo::setOrdersForIntermediatePointAndGetOrderSet(bool movementStopped)
{
	Pose robotPose = getRobot().getPose();

	const Point &target = getNextTargetPoint();

	if (!m_initialRotationReached)
	{
		Compare compareAngle(m_precisionOrientationInitial);
		Angle targetAngle(robotPose.getPosition(), target);
		if (compareAngle.isFuzzyEqual(robotPose.getOrientation(), targetAngle))
		{
			log("inital rotation reached");
			logCurrentPose();
			m_initialRotationReached = true;
			m_movementStopUsed = true;
		}
		else if (movementStopped && !m_movementStopUsed)
		{
			log("inital rotation not really reached, but movement stopped");
			logCurrentPose();
			m_movementStopUsed = true;
			m_initialRotationReached = true;
		}
		else
		{
			if (!m_initialRotationStarted)
				getRobot().turn(targetAngle);

			m_initialRotationStarted = true;
			return true;
		}
	}

	Compare comparePosition(m_precisionPosition);
	if ((comparePosition.isFuzzyEqual(robotPose.getPosition(), target)))
	{
		log("position reached");
		logCurrentPose();
		m_movementStopUsed = true;
		m_currentRoute->removeFirstPoint();
		logRoute();
	}
	else if (movementStopped && !m_movementStopUsed)
	{
		log("position not really reached, but movement stopped");
		logCurrentPose();
		m_movementStopUsed = true;
		m_currentRoute->removeFirstPoint();
		logRoute();
	}
	else
	{
		if (!m_driveStarted)
		{
			if(m_currentRoute->getPointCount() == 2 && m_driveSlowlyAtTheEnd)
				getRobot().gotoPositionPrecise(target);
			else
				getRobot().gotoPositionImprecise(target);
		}

		m_driveStarted = true;
		return true;
	}

	return false;
}

void DriveTo::updateRoute()
{
	Point robotPoint = getRobot().getPose().getPosition();
	vector<Circle> obstacles = getAllObstaclesButMeInRangeDependentOnFlags(robotPoint, 1);
	vector<Circle> modifiedObstacles = modifyObstacles(obstacles,0.9);

	if (!isRouteFeasible(modifiedObstacles))
	{
		log("current route is not feasible anymore we try to create a new one");
		clearRoute();
		m_currentRoute = new Route(ReadableRobot::getWidth());
		updateRouteForTarget();
	}
}

void DriveTo::updateRouteForTarget()
{
	Point robotPoint = getRobot().getPose().getPosition();
	Point target = m_target.getPosition();
	vector<Circle> obstacles = getAllObstaclesButMeInRangeDependentOnFlags(robotPoint, 1);
	vector<Circle> modifiedObstacles = modifyObstacles(obstacles, 2);

	*m_currentRoute = m_router.calculateRoute(robotPoint, target, modifiedObstacles);

	if((m_driveSlowlyAtTheEnd || m_ignoreGoalObstacles) && m_currentRoute->isValid())
		prepareLastRouteSegmentForDrivingSlowly();

	resetAllMovementFlags();
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

vector<Circle> DriveTo::getAllObstaclesButMeInRangeDependentOnFlags(const Point &robotPoint, double distance) const
{
	if(m_ignoreBall)
		return m_obstacleFetcher.getAllObstaclesButMeAndBallInRange(m_autonomousRobot, robotPoint, distance);
	else if(m_ignoreGoalObstacles)
		return m_obstacleFetcher.getAllObstaclesButMeAndGoalObstaclesInRange(m_autonomousRobot, robotPoint, distance);
	else
		return m_obstacleFetcher.getAllObstaclesButMeInRange(m_autonomousRobot, robotPoint, distance);
}

void DriveTo::clearRoute()
{
	delete m_currentRoute;
	m_currentRoute = 0;
}

void DriveTo::resetAllMovementFlags()
{
	m_initialRotationReached = false;
	m_initialRotationStarted = false;
	m_finalRotationReached = false;
	m_finalRotationStarted = false;
	m_driveStarted = false;
}

void DriveTo::prepareLastRouteSegmentForDrivingSlowly()
{
	double lengthOfLastSegment = 0.15;

	if(m_currentRoute->getLengthOfLastSegment() > lengthOfLastSegment)
		m_currentRoute->splitLastSegment(lengthOfLastSegment);
}

string DriveTo::getName() const
{
	return string("drive to");
}

size_t DriveTo::getRoutePointsCount() const
{
	return m_currentRoute->getPointCount();
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
