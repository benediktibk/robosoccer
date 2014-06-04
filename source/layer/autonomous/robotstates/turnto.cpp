#include "layer/autonomous/robotstates/turnto.h"
#include "layer/abstraction/controllablerobot.h"
#include "common/geometry/pose.h"
#include "common/geometry/compare.h"
#include "common/time/stopwatch.h"

using namespace std;
using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Time;
using namespace RoboSoccer::Common::Logging;

TurnTo::TurnTo(
		Abstraction::ControllableRobot &robot, Point const &target,
		RobotState *followingState, Logger &logger, Logger::LogFileType logFileType) :
	RobotState(robot, logger, logFileType),
	m_target(target),
	m_followingState(followingState),
	m_targetAlreadySet(false)
{ }

TurnTo::~TurnTo()
{
	delete m_followingState;
	m_followingState = 0;
}

bool TurnTo::reachedTarget() const
{
	return false;
}

bool TurnTo::isEquivalentToDriveTo(const Pose &) const
{
	return false;
}

bool TurnTo::isEquivalentToDriveToDirect(const Pose &) const
{
	return false;
}

RobotState *TurnTo::nextState(bool movementStopped)
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

void TurnTo::updateInternal(bool)
{
	if (m_targetAlreadySet)
		return;

	Angle targetOrientation = calculateTargetOrientation();
	getRobot().turn(targetOrientation);
	m_targetAlreadySet = true;
}

Angle TurnTo::calculateTargetOrientation() const
{
	Pose currentPose = getRobot().getPose();
	Point const &currentPosition = currentPose.getPosition();
	return Angle(currentPosition, m_target);
}

string TurnTo::getName() const
{
	return string("turn to");
}
