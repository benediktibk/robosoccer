#include "layer/abstraction/readablerobotmock.h"
#include "common/geometry/pose.h"
#include "common/geometry/circle.h"

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;

Pose ReadableRobotMock::getPosition() const
{
	return Pose();
}

Circle ReadableRobotMock::createObstacle() const
{
	return Circle();
}

