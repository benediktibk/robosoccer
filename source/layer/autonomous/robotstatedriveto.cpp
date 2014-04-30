#include "layer/autonomous/robotstatedriveto.h"
#include "layer/abstraction/controllablerobot.h"
#include "common/geometry/compare.h"
#include "common/geometry/pose.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;

RobotStateDriveTo::RobotStateDriveTo(
		Abstraction::ControllableRobot &robot, Common::Geometry::Point const &target,
		RobotState *followingState, bool precise) :
	RobotState(robot),
	m_target(target),
	m_followingState(followingState),
	m_precise(precise)
{ }

RobotStateDriveTo::~RobotStateDriveTo()
{
	delete m_followingState;
	m_followingState = 0;
}

bool RobotStateDriveTo::reachedTarget() const
{
	return false;
}

bool RobotStateDriveTo::cantReachTarget() const
{
	return false;
}

RobotState *RobotStateDriveTo::nextState()
{
	Compare compare(0.01);
	Pose currentPose = getRobot().getPose();
	RobotState *result = 0;

	if (compare.isFuzzyEqual(currentPose.getPosition(), m_target))
	{
		result = m_followingState;
		m_followingState = 0;
	}

	return result;
}

void RobotStateDriveTo::update()
{
	if (m_precise)
		getRobot().gotoPositionPrecise(m_target);
	else
		getRobot().gotoPositionImprecise(m_target);
}