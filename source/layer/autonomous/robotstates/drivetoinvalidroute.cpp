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

DriveToInvalidRoute::DriveToInvalidRoute(ControllableRobot &robot, const std::vector<Pose> &targets, const Pose &currentTarget, const Router &router, Logger &logger,
		Logger::LogFileType logFileType, ObstacleFetcher const &obstacleFetcher,
		ObstacleSource const &ownObstacleSource, DriveMode driveMode, FieldPositionChecker const &fieldPositionChecker) :
	DriveTo(robot, targets, currentTarget, router, logger, logFileType, obstacleFetcher, ownObstacleSource, driveMode, fieldPositionChecker)
{ }

RobotState *DriveToInvalidRoute::nextState(bool)
{
	updateRouteIfNecessary();
	Route const &currentRoute = getCurrentRoute();

	if (currentRoute.isValid())
	{
		log("found again a valid route, starting with initial rotation");
		return new DriveToInitialRotation(
					getRobot(), getTargets(), getCurrentTarget(), getRouter(), getLogger(), getLogFileType(),
					getObstacleFetcher(), getOwnObstacleSource(), getDriveMode(), currentRoute, getFieldPositionChecker());
	}

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
