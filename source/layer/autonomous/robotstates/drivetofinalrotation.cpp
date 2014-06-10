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

DriveToFinalRotation::DriveToFinalRotation(ControllableRobot &robot, const std::vector<Pose> &targets, const Pose &currentTarget, const Router &router, Logger &logger,
		Logger::LogFileType logFileType, ObstacleFetcher const &obstacleFetcher,
		ObstacleSource const &ownObstacleSource, DriveMode driveMode, const Route &oldRoute, FieldPositionChecker const &fieldPositionChecker) :
	DriveTo(robot, targets, currentTarget, router, logger, logFileType, obstacleFetcher, ownObstacleSource, driveMode, fieldPositionChecker),
	m_movementStarted(false)
{
	setRoute(oldRoute);
}

RobotState *DriveToFinalRotation::nextState(bool movementStopped)
{
	RobotState *state = nextStateWithRouteUpdate();

	if (state != 0)
		return state;

	Compare compare = getFinalRotationCompare();
	Pose const& currentPose = getRobot().getPose();
	Pose const& target = getTargets().front();

	if (	compare.isFuzzyEqual(currentPose.getOrientation(), target.getOrientation()) ||
			(movementStopped && m_movementStarted))
	{
		log("reached final orientation");
		return new ReachedTarget(getRobot(), getLogger(), getLogFileType());
	}

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

	Pose const& target = getCurrentTarget();
	Angle const& targetOrientaton = target.getOrientation();
	getRobot().turn(targetOrientaton);
	m_movementStarted = true;
}
