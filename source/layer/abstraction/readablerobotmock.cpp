#include "layer/abstraction/readablerobotmock.h"
#include "common/geometry/orientedposition.h"
#include "common/geometry/circle.h"

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;

OrientedPosition ReadableRobotMock::getPosition() const
{
	return OrientedPosition();
}

Circle ReadableRobotMock::createObstacle() const
{
	return Circle();
}

