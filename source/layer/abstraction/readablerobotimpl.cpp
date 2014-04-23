#include "layer/abstraction/readablerobotimpl.h"
#include "common/geometry/orientedposition.h"
#include "common/geometry/circle.h"

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;

ReadableRobotImpl::ReadableRobotImpl()
{ }

OrientedPosition ReadableRobotImpl::getPosition() const
{
	return OrientedPosition();
}

Circle ReadableRobotImpl::createObstacle() const
{
	return Circle();
}

