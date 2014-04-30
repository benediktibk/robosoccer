#include "layer/autonomous/robotmock.h"
#include "common/geometry/pose.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;

RobotMock::RobotMock()
{ }

RobotMock::~RobotMock()
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

bool RobotMock::kick(unsigned int /*force*/, IntelligentBall const &/*ball*/)
{
	return false;
}

void RobotMock::update()
{ }

void RobotMock::stop()
{ }
