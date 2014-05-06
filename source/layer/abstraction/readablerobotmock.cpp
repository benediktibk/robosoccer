#include "layer/abstraction/readablerobotmock.h"
#include "common/geometry/pose.h"
#include "common/geometry/circle.h"

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;

Pose ReadableRobotMock::getPose() const
{
	return Pose();
}

Circle ReadableRobotMock::getObstacle() const
{
	return Circle();
}

