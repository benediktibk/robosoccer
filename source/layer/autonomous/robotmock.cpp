#include "layer/autonomous/robotmock.h"
#include "common/geometry/pose.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;

RobotMock::RobotMock()
{ }

void RobotMock::goTo(const RoboSoccer::Common::Geometry::Point &/*position*/)
{

}

Pose RoboSoccer::Layer::Autonomous::RobotMock::getCurrentPose() const
{
	return Pose();
}

bool RobotMock::targetReached() const
{
	return false;
}

bool RobotMock::kick(unsigned int /*force*/)
{
	return false;
}

void RobotMock::stop()
{ }