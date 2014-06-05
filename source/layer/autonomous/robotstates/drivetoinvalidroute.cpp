#include "layer/autonomous/robotstates/drivetoinvalidroute.h"
#include "layer/autonomous/robotstates/drivetoinitialrotation.h"
#include "layer/abstraction/controllablerobot.h"
#include "common/routing/route.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Logging;
using namespace RoboSoccer::Common::Routing;
using namespace std;

DriveToInvalidRoute::DriveToInvalidRoute(
		ControllableRobot &robot, const Pose &target, const Router &router, Logger &logger,
		Logger::LogFileType logFileType, ObstacleFetcher const &obstacleFetcher,
		ObstacleSource const &ownObstacleSource, bool ignoreBall, bool driveSlowlyAtTheEnd,
		bool ignoreGoalObstacles) :
	DriveTo(robot, target, router, logger, logFileType, obstacleFetcher,
			ownObstacleSource, ignoreBall, driveSlowlyAtTheEnd, ignoreGoalObstacles)
{ }

RobotState *DriveToInvalidRoute::nextState(bool)
{
	updateRouteIfNecessary();
	Route const &currentRoute = getCurrentRoute();

	if (currentRoute.isValid())
		return new DriveToInitialRotation(
					getRobot(), getTarget(), getRouter(), getLogger(), getLogFileType(),
					getObstacleFetcher(), getOwnObstacleSource(), ignoreBall(), driveSlowlyAtTheEnd(),
					ignoreGoalObstacles());

	return 0;
}

string DriveToInvalidRoute::getName() const
{
	return string("drive to - invalid route");
}

void DriveToInvalidRoute::update()
{
	getRobot().stop();
}
