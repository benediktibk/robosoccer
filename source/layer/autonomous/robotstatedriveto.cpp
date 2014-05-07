#include "layer/autonomous/robotstatedriveto.h"
#include "layer/autonomous/robotstatereachedtarget.h"
#include "layer/abstraction/controllablerobot.h"
#include "common/geometry/compare.h"
#include "common/geometry/pose.h"
#include "common/time/stopwatch.h"

using namespace std;
using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Time;

RobotStateDriveTo::RobotStateDriveTo(Abstraction::ControllableRobot &robot, Point const &target, Watch const &watch) :
	RobotState(robot),
	m_currentTargetValid(false),
	m_target(target),
	m_watchDog(new StopWatch(watch))
{
	m_watchDog->getTimeAndRestart();
}

RobotStateDriveTo::~RobotStateDriveTo()
{
	delete m_watchDog;
	m_watchDog = 0;
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
	Compare compare(0.1);
	Pose currentPose = getRobot().getPose();

	if (compare.isFuzzyEqual(currentPose.getPosition(), m_target) || m_watchDog->getTime() > 5)
		return new RobotStateReachedTarget(getRobot());

	return 0;
}

bool RobotStateDriveTo::isEquivalentToDriveTo(const Point &target) const
{
	Compare compare(0.02);
	return compare.isFuzzyEqual(m_target, target);
}

void RobotStateDriveTo::update()
{
	if (!m_currentTargetValid)
	{
		getRobot().gotoPositionPrecise(m_target);
		m_currentTargetValid = true;
	}
}

string RobotStateDriveTo::getName() const
{
	return string("drive to");
}
