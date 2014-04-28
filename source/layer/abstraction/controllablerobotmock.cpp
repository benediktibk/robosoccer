#include "layer/abstraction/controllablerobotmock.h"
#include "common/geometry/pose.h"
#include "common/geometry/circle.h"

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;

Pose ControllableRobotMock::getPose() const
{
	return Pose();
}

Circle ControllableRobotMock::createObstacle() const
{
	return Circle();
}

void ControllableRobotMock::gotoPositionImprecise(const Point &/*position*/)
{

}

void ControllableRobotMock::gotoPositionPrecise(const Point &/*position*/)
{

}

bool ControllableRobotMock::kick(unsigned int /*force*/, double /*distanceToBall*/)
{
	return false;
}

void ControllableRobotMock::turn(const Angle &/*absoluteAngle*/)
{

}

