#include "layer/autonomous/robotstates/drivetodriving.h"
#include "layer/autonomous/robotstates/drivetoinvalidroute.h"
#include "layer/autonomous/robotstates/drivetoinitialrotation.h"
#include "layer/autonomous/robotstates/drivetofinalrotation.h"
#include "layer/abstraction/controllablerobot.h"
#include "common/geometry/point.h"
#include "common/geometry/compare.h"
#include "common/routing/route.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::Routing;
using namespace std;

DriveToDriving::DriveToDriving(
		ControllableRobot &robot, const Pose &target, const Router &router,
		Logger &logger, Logger::LogFileType logFileType, ObstacleFetcher const &obstacleFetcher,
		ObstacleSource const &ownObstacleSource, bool ignoreBall, bool driveSlowlyAtTheEnd,
		bool ignoreGoalObstacles) :
	DriveTo(robot, target, router, logger, logFileType, obstacleFetcher,
			ownObstacleSource, ignoreBall, driveSlowlyAtTheEnd, ignoreGoalObstacles),
	m_movementStarted(false)
{ }

DriveToDriving::DriveToDriving(
		ControllableRobot &robot, const Pose &target, const Router &router, Logger &logger,
		Logger::LogFileType logFileType, ObstacleFetcher const &obstacleFetcher,
		ObstacleSource const &ownObstacleSource, bool ignoreBall, bool driveSlowlyAtTheEnd,
		bool ignoreGoalObstacles, const Route &oldRoute) :
	DriveTo(robot, target, router, logger, logFileType, obstacleFetcher,
			ownObstacleSource, ignoreBall, driveSlowlyAtTheEnd, ignoreGoalObstacles),
	m_movementStarted(false)
{
	setRoute(oldRoute);
}

RobotState *DriveToDriving::nextState(bool movementStopped)
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

	Compare compare = getPositionCompare();
	Pose const& currentPose = getRobot().getPose();

	if (compare.isFuzzyEqual(currentPose.getPosition(), currentRoute.getSecondPoint()) || movementStopped)
	{
		if (currentRoute.getPointCount() > 2)
			return new DriveToInitialRotation(
						getRobot(), getTarget(), getRouter(), getLogger(), getLogFileType(),
						getObstacleFetcher(), getOwnObstacleSource(), ignoreBall(), driveSlowlyAtTheEnd(),
						ignoreGoalObstacles(), currentRoute);
		else
			return new DriveToFinalRotation(
						getRobot(), getTarget(), getRouter(), getLogger(), getLogFileType(),
						getObstacleFetcher(), getOwnObstacleSource(), ignoreBall(), driveSlowlyAtTheEnd(),
						ignoreGoalObstacles());
	}

	return 0;
}

string DriveToDriving::getName() const
{
	return string("drive to - driving");
}

void DriveToDriving::update(bool)
{
	Route const& currentRoute = getCurrentRoute();

	if (m_movementStarted || !currentRoute.isValid())
		return;

	Point const& nextPoint = currentRoute.getSecondPoint();
	if (currentRoute.getPointCount() == 2 && driveSlowlyAtTheEnd())
		getRobot().gotoPositionPrecise(nextPoint);
	else
		getRobot().gotoPositionImprecise(nextPoint);

	m_movementStarted = true;
}
