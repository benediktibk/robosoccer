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

DriveToDriving::DriveToDriving(ControllableRobot &robot, const std::vector<Pose> &targets, const Router &router, Logger &logger,
		Logger::LogFileType logFileType, ObstacleFetcher const &obstacleFetcher,
		ObstacleSource const &ownObstacleSource, DriveMode driveMode, const Route &oldRoute) :
	DriveTo(robot, targets, router, logger, logFileType, obstacleFetcher,
			ownObstacleSource, driveMode),
	m_movementStarted(false)
{
	setRoute(oldRoute);
}

RobotState *DriveToDriving::nextState(bool movementStopped)
{
	RobotState *state = nextStateWithRouteUpdate();

	if (state != 0)
		return state;

	Compare compare = getPositionCompare();
	Pose const& currentPose = getRobot().getPose();
	Route currentRoute = getCurrentRoute();

	if (	compare.isFuzzyEqual(currentPose.getPosition(), currentRoute.getSecondPoint()) ||
			(movementStopped && m_movementStarted))
	{
		if (currentRoute.getPointCount() > 2)
		{
			log("position reached, turning to next point");
			currentRoute.removeFirstPoint();
			return new DriveToInitialRotation(
						getRobot(), getTargets(), getRouter(), getLogger(), getLogFileType(),
						getObstacleFetcher(), getOwnObstacleSource(), getDriveMode(), currentRoute);
		}
		else
		{
			log("position reached, turning to final orientation");
			return new DriveToFinalRotation(
						getRobot(), getTargets(), getRouter(), getLogger(), getLogFileType(),
						getObstacleFetcher(), getOwnObstacleSource(), getDriveMode(), currentRoute);
		}
	}

	return 0;
}

string DriveToDriving::getName() const
{
	return string("drive to - driving");
}

void DriveToDriving::update()
{
	Route const& currentRoute = getCurrentRoute();

	if (m_movementStarted || !currentRoute.isValid())
		return;

	Point const& nextPoint = currentRoute.getSecondPoint();
	if (currentRoute.getPointCount() == 2 && getDriveMode() == DriveModeDriveSlowlyAtTheEnd)
		getRobot().gotoPositionPrecise(nextPoint);
	else
		getRobot().gotoPositionImprecise(nextPoint);

	m_movementStarted = true;
}
