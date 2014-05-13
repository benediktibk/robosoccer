#include "layer/autonomous/robotstatedrivetodirect.h"
#include "layer/autonomous/robotstatereachedtarget.h"
#include "layer/abstraction/controllablerobot.h"
#include "common/time/stopwatch.h"
#include "common/geometry/compare.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Time;
using namespace std;

RobotStateDriveToDirect::RobotStateDriveToDirect(ControllableRobot &robot, const Pose &target, const Watch &watch) :
	RobotState(robot),
	m_initialRotationReached(false),
	m_initialRotationStarted(false),
	m_positionReached(false),
	m_driveStarted(false),
	m_finalRotationReached(false),
	m_finalRotationStarted(false),
	m_target(target),
	m_watchDog(new StopWatch(watch))
{ }

RobotStateDriveToDirect::~RobotStateDriveToDirect()
{
	delete m_watchDog;
	m_watchDog = 0;
}

bool RobotStateDriveToDirect::reachedTarget() const
{
	return false;
}

bool RobotStateDriveToDirect::cantReachTarget() const
{
	return false;
}

RobotState* RobotStateDriveToDirect::nextState()
{
	Compare comparePosition(0.1);
	Compare compareAngle(0.2);
	Pose pose = getRobot().getPose();

	if (	comparePosition.isFuzzyEqual(pose.getPosition(), m_target.getPosition()) &&
			compareAngle.isFuzzyEqual(pose.getOrientation(), m_target.getOrientation()))
		return new RobotStateReachedTarget(getRobot());
	else if (m_watchDog->getTime() > 10)
		return new RobotStateReachedTarget(getRobot());
	else
		return 0;
}

void RobotStateDriveToDirect::update()
{
	Compare comparePosition(0.1);
	Compare compareAngle(0.2);
	Pose pose = getRobot().getPose();

	if (!m_initialRotationReached)
	{
		Angle targetAngle(pose.getPosition(), m_target.getPosition());
		if (compareAngle.isFuzzyEqual(pose.getOrientation(), targetAngle))
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
		if (comparePosition.isFuzzyEqual(pose.getPosition(), m_target.getPosition()))
			m_positionReached = true;
		else
		{
			if (!m_driveStarted)
				getRobot().gotoPositionImprecise(m_target.getPosition());

			m_driveStarted = true;
			return;
		}
	}

	if (!m_finalRotationReached)
	{
		if (compareAngle.isFuzzyEqual(pose.getOrientation(), m_target.getOrientation()))
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

string RobotStateDriveToDirect::getName() const
{
	return string("drive to direct");
}

bool RobotStateDriveToDirect::isEquivalentToDriveToDirect(const Pose &target) const
{
	Compare compare(0.02);

	return compare.isFuzzyEqual(m_target, target);
}
