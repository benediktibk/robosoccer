#include "layer/autonomous/robotstatedriveto.h"
#include "layer/autonomous/robotstatereachedtarget.h"
#include "layer/abstraction/controllablerobot.h"
#include "common/geometry/compare.h"
#include "common/time/stopwatch.h"

using namespace std;
using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Time;

RobotStateDriveTo::RobotStateDriveTo(Abstraction::ControllableRobot &robot, Pose const &target, Watch const &watch) :
	RobotState(robot),
	m_precisionPosition(0.02),
	m_precisionOrientation(0.1),
	m_initialRotationReached(false),
	m_initialRotationStarted(false),
	m_positionReached(false),
	m_driveStarted(false),
	m_finalRotationReached(false),
	m_finalRotationStarted(false),
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

bool RobotStateDriveTo::isEquivalentToDriveTo(const Pose &target) const
{
	Compare compare(0.02);
	return compare.isFuzzyEqual(m_target, target);
}

void RobotStateDriveTo::update()
{
	Compare comparePosition(m_precisionPosition);
	Compare compareAngle(m_precisionOrientation);
	Pose pose = getRobot().getPose();

	if (!m_initialRotationReached)
	{
		Angle targetAngle(pose.getPosition(), m_target.getPosition());
		if (compareAngle.isFuzzyEqual(pose.getOrientation(), targetAngle) && !getRobot().isMoving())
			m_initialRotationReached = true;
		else
		{
			if (!m_initialRotationStarted)
				getRobot().turn(targetAngle);

			m_initialRotationStarted = true;
			return;
		}
	}

	if (!m_positionReached)
	{
		if (comparePosition.isFuzzyEqual(pose.getPosition(), m_target.getPosition()) && !getRobot().isMoving())
			m_positionReached = true;
		else
		{
			if (!m_driveStarted)
				getRobot().gotoPositionPrecise(m_target.getPosition());

			m_driveStarted = true;
			return;
		}
	}

	if (!m_finalRotationReached)
	{
		if (compareAngle.isFuzzyEqual(pose.getOrientation(), m_target.getOrientation()) && !getRobot().isMoving())
			m_finalRotationReached = true;
		else
		{
			if (!m_finalRotationStarted)
				getRobot().turn(m_target.getOrientation());

			m_finalRotationStarted = true;
			return;
		}
	}
}

string RobotStateDriveTo::getName() const
{
	return string("drive to");
}
