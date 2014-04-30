#include "layer/autonomous/robotmock.h"
#include "common/geometry/pose.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;

RobotMock::RobotMock()
{ }

void RobotMock::goTo(const Point &/*position*/)
{ }

Pose RobotMock::getCurrentPose() const
{
	return Pose();
}

bool RobotMock::targetReached() const
{
	return false;
}

void RobotMock::kick(unsigned int /*force*/, IntelligentBall const &/*ball*/)
{ }

void RobotMock::update()
{ }

void RobotMock::stop()
{ }