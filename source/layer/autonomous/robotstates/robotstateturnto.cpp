#include "layer/autonomous/robotstates/robotstateturnto.h"
#include "layer/abstraction/controllablerobot.h"
#include "common/geometry/pose.h"
#include "common/geometry/compare.h"
#include "common/time/stopwatch.h"

using namespace std;
using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Time;
using namespace RoboSoccer::Common::Logging;

RobotStateTurnTo::RobotStateTurnTo(
		Abstraction::ControllableRobot &robot, Point const &target,
		RobotState *followingState, Logger &logger, Logger::LogFileType logFileType) :
	RobotState(robot, logger, logFileType),
	m_target(target),
	m_followingState(followingState),
	m_targetAlreadySet(false)
{ }

RobotStateTurnTo::~RobotStateTurnTo()
{
	delete m_followingState;
	m_followingState = 0;
}

bool RobotStateTurnTo::reachedTarget() const
{
	return false;
}

bool RobotStateTurnTo::cantReachTarget() const
{
	return false;
}

bool RobotStateTurnTo::isEquivalentToDriveTo(const Pose &) const
{
	return false;
}

bool RobotStateTurnTo::isEquivalentToDriveToDirect(const Pose &) const
{
	return false;
}

RobotState *RobotStateTurnTo::nextState(bool movementStopped)
{
	Compare compare(0.1);
	Pose currentPose = getRobot().getPose();
	Angle targetOrientation = calculateTargetOrientation();
	RobotState *result = 0;

	if (compare.isFuzzyEqual(currentPose.getOrientation(), targetOrientation) || movementStopped)
	{
		result = m_followingState;
		m_followingState = 0;
	}

	return result;
}

void RobotStateTurnTo::updateInternal(bool)
{
	if (m_targetAlreadySet)
		return;

	Angle targetOrientation = calculateTargetOrientation();
	getRobot().turn(targetOrientation);
	m_targetAlreadySet = true;
}

Angle RobotStateTurnTo::calculateTargetOrientation() const
{
	Pose currentPose = getRobot().getPose();
	Point const &currentPosition = currentPose.getPosition();
	return Angle(currentPosition, m_target);
}

string RobotStateTurnTo::getName() const
{
	return string("turn to");
}
