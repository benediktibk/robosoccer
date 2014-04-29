#include "layer/autonomous/robotimpl.h"
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

void RobotImpl::goTo(const Point &/*position*/)
{

}

Pose RoboSoccer::Layer::Autonomous::RobotImpl::getCurrentPose() const
{
	return m_robot.getPose();
}

bool RobotImpl::targetReached() const
{
	return false;
}

void RobotImpl::stop()
{
	m_robot.stop();
}