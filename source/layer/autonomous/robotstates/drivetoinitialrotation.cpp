#include "layer/autonomous/robotstates/drivetoinitialrotation.h"
#include "layer/autonomous/robotstates/drivetoinvalidroute.h"
#include "layer/autonomous/robotstates/drivetodriving.h"
#include "layer/abstraction/controllablerobot.h"
#include "common/routing/route.h"
#include "common/geometry/point.h"
#include "common/geometry/angle.h"
#include "common/geometry/compare.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::Routing;
using namespace std;

DriveToInitialRotation::DriveToInitialRotation(ControllableRobot &robot, const Pose &target, const Router &router, Logger &logger,
		Logger::LogFileType logFileType, ObstacleFetcher const &obstacleFetcher,
		ObstacleSource const &ownObstacleSource, DriveMode driveMode) :
	DriveTo(robot, target, router, logger, logFileType, obstacleFetcher, ownObstacleSource, driveMode),
	m_movementStarted(false)
{
	updateRouteIfNecessary();
}

DriveToInitialRotation::DriveToInitialRotation(ControllableRobot &robot, const Pose &target, const Router &router, Logger &logger,
		Logger::LogFileType logFileType, ObstacleFetcher const &obstacleFetcher,
		ObstacleSource const &ownObstacleSource, DriveMode driveMode, const Route &oldRoute) :
	DriveTo(robot, target, router, logger, logFileType, obstacleFetcher, ownObstacleSource, driveMode),
	m_movementStarted(false)
{
	setRoute(oldRoute);
}

Angle DriveToInitialRotation::calculateTargetOrientation(Route const &currentRoute) const
{
	Point const &nextPoint = currentRoute.getSecondPoint();
	Pose currentPose = getRobot().getPose();
	return Angle(currentPose.getPosition(), nextPoint);
}

RobotState *DriveToInitialRotation::nextState(bool movementStopped)
{
	RobotState *state = nextStateWithRouteUpdate();

	if (state != 0)
		return state;

	Compare compare = getInitialRotationCompare();
	Pose currentPose = getRobot().getPose();
	Route const &currentRoute = getCurrentRoute();
	Angle targetOrientation = calculateTargetOrientation(currentRoute);

	if (	compare.isFuzzyEqual(currentPose.getOrientation(), targetOrientation) ||
			(movementStopped && m_movementStarted))
	{
		log("reached initial orientation, driving to next point");
		return new DriveToDriving(
					getRobot(), getTarget(), getRouter(), getLogger(), getLogFileType(),
					getObstacleFetcher(), getOwnObstacleSource(), getDriveMode(), currentRoute);
	}

	return 0;
}

string DriveToInitialRotation::getName() const
{
	return string("drive to - initial rotation");
}

void DriveToInitialRotation::update()
{
	Route const &currentRoute = getCurrentRoute();

	if (m_movementStarted || !currentRoute.isValid())
		return;

	Angle targetOrientation = calculateTargetOrientation(currentRoute);
	getRobot().turn(targetOrientation);
	m_movementStarted = true;
}
