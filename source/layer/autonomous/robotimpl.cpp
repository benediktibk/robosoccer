#include "layer/autonomous/robotimpl.h"
#include "layer/autonomous/intelligentball.h"
#include "layer/abstraction/controllablerobot.h"
#include "common/geometry/pose.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;

RobotImpl::RobotImpl(ControllableRobot &robot) :
	m_robot(robot)
{ }

RobotImpl::~RobotImpl()
{ }

void RobotImpl::goTo(const Point &position)
{
	//! @todo should consider obstacles
	m_robot.gotoPositionPrecise(position);
}

Pose RobotImpl::getCurrentPose() const
{
	return m_robot.getPose();
}

bool RobotImpl::targetReached() const
{
	return false;
}

bool RobotImpl::kick(unsigned int force, IntelligentBall const &ball)
{
	Point ballPosition = ball.getPosition();
	Pose ownPose = getCurrentPose();
	Point const &ownPosition = ownPose.getPosition();
	double distanceToBall = ownPosition.distanceTo(ballPosition);

	//! there is a maximum distance to the ball specified in the documentation
	if (distanceToBall >= 0.25)
		return false;

	//! first turn towards the ball
	return m_robot.kick(force);
}

void RobotImpl::stop()
{
	m_robot.stop();
}