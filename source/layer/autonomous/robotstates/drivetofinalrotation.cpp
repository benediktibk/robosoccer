#include "layer/autonomous/robotstates/drivetofinalrotation.h"
#include "layer/autonomous/robotstates/drivetoinitialrotation.h"
#include "layer/autonomous/robotstates/drivetoinvalidroute.h"
#include "layer/autonomous/robotstates/reachedtarget.h"
#include "layer/abstraction/controllablerobot.h"
#include "common/routing/route.h"
#include "common/geometry/pose.h"
#include "common/geometry/angle.h"
#include "common/geometry/point.h"
#include "common/geometry/compare.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::Routing;
using namespace std;

DriveToFinalRotation::DriveToFinalRotation(
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

RobotState *DriveToFinalRotation::nextState(bool movementStopped)
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

	Compare compare = getFinalRotationCompare();
	Pose const& currentPose = getRobot().getPose();
	Pose const& target = getTarget();

	if (compare.isFuzzyEqual(currentPose.getOrientation(), target.getOrientation()) || movementStopped)
		return new ReachedTarget(getRobot(), getLogger(), getLogFileType());

	return 0;
}

string DriveToFinalRotation::getName() const
{
	return string("drive to - final rotation");
}

void DriveToFinalRotation::update()
{
	Route const& currentRoute = getCurrentRoute();

	if (m_movementStarted || !currentRoute.isValid())
		return;

	Pose const& target = getTarget();
	Angle const& targetOrientaton = target.getOrientation();
	getRobot().turn(targetOrientaton);
	m_movementStarted = true;
}
