#include "layer/autonomous/robotstateturnto.h"
#include "layer/abstraction/controllablerobot.h"
#include "common/geometry/pose.h"
#include "common/geometry/compare.h"

using namespace std;
using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;

RobotStateTurnTo::RobotStateTurnTo(
		Abstraction::ControllableRobot &robot, Common::Geometry::Point const &target,
		RobotState *followingState) :
	RobotState(robot),
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

RobotState *RobotStateTurnTo::nextState()
{
	Compare compare(0.01);
	Pose currentPose = getRobot().getPose();
	Angle targetOrientation = calculateTargetOrientation();
	RobotState *result = 0;

	if (compare.isFuzzyEqual(currentPose.getOrientation(), targetOrientation))
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
