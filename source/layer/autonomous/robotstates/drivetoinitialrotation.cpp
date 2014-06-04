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

DriveToInitialRotation::DriveToInitialRotation(
		ControllableRobot &robot, const Pose &target, const Router &router, Logger &logger,
		Logger::LogFileType logFileType, ObstacleFetcher const &obstacleFetcher,
		ObstacleSource const &ownObstacleSource, bool ignoreBall, bool driveSlowlyAtTheEnd,
		bool ignoreGoalObstacles) :
	DriveTo(robot, target, router, logger, logFileType, obstacleFetcher,
			ownObstacleSource, ignoreBall, driveSlowlyAtTheEnd, ignoreGoalObstacles),
	m_movementStarted(false)
{ }

Angle DriveToInitialRotation::calculateTargetOrientation(Route const &currentRoute) const
{
	Point const &nextPoint = currentRoute.getSecondPoint();
	Pose currentPose = getRobot().getPose();
	return Angle(currentPose.getPosition(), nextPoint);
}

RobotState *DriveToInitialRotation::nextState(bool movementStopped)
{
	bool routeUpdated = updateRouteIfNecessary();
	Route const &currentRoute = getCurrentRoute();

	if (!currentRoute.isValid())
		return new DriveToInvalidRoute(
					getRobot(), getTarget(), getRouter(), getLogger(), getLogFileType(),
					getObstacleFetcher(), getOwnObstacleSource(), ignoreBall(), driveSlowlyAtTheEnd(),
					ignoreGoalObstacles());

	if (routeUpdated)
		return new DriveToInitialRotation(
					getRobot(), getTarget(), getRouter(), getLogger(), getLogFileType(),
					getObstacleFetcher(), getOwnObstacleSource(), ignoreBall(), driveSlowlyAtTheEnd(),
					ignoreGoalObstacles());

	Compare compare = getInitialRotationCompare();
	Pose currentPose = getRobot().getPose();
	Angle targetOrientation = calculateTargetOrientation(currentRoute);

	if (compare.isFuzzyEqual(currentPose.getOrientation(), targetOrientation) || movementStopped)
		return new DriveToDriving(
					getRobot(), getTarget(), getRouter(), getLogger(), getLogFileType(),
					getObstacleFetcher(), getOwnObstacleSource(), ignoreBall(), driveSlowlyAtTheEnd(),
					ignoreGoalObstacles());

	return 0;
}

string DriveToInitialRotation::getName() const
{
	return string("drive to - initial rotation");
}

void DriveToInitialRotation::update(bool)
{
	Route const &currentRoute = getCurrentRoute();

	if (m_movementStarted || !currentRoute.isValid())
		return;

	Angle targetOrientation = calculateTargetOrientation(currentRoute);
	getRobot().turn(targetOrientation);
	m_movementStarted = true;
}
