#include "layer/autonomous/robotstateturnto.h"
#include "layer/abstraction/controllablerobot.h"
#include "common/geometry/pose.h"
#include "common/geometry/compare.h"
#include "common/time/stopwatch.h"

using namespace std;
using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Time;

RobotStateTurnTo::RobotStateTurnTo(
		Abstraction::ControllableRobot &robot, Point const &target, Watch const &watch,
		RobotState *followingState) :
	RobotState(robot),
	m_target(target),
	m_followingState(followingState),
	m_targetAlreadySet(false),
	m_watchDog(new StopWatch(watch))
{
	m_watchDog->getTimeAndRestart();
}

RobotStateTurnTo::~RobotStateTurnTo()
{
	delete m_followingState;
	m_followingState = 0;
	delete m_watchDog;
	m_watchDog = 0;
}

bool RobotStateTurnTo::reachedTarget() const
{
	return false;
}

bool RobotStateTurnTo::cantReachTarget() const
{
	return false;
}

RobotState *RobotStateTurnTo::nextState()
{
	Compare compare(0.1);
	Pose currentPose = getRobot().getPose();
	Angle targetOrientation = calculateTargetOrientation();
	RobotState *result = 0;

	if (compare.isFuzzyEqual(currentPose.getOrientation(), targetOrientation) || m_watchDog->getTime() > 2)
	{
		result = m_followingState;
		m_followingState = 0;
	}

	return result;
}

bool RobotStateTurnTo::isEquivalentToDriveTo(const Point &) const
{
	return false;
}

void RobotStateTurnTo::update()
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
