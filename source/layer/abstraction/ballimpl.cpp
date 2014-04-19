#include "layer/abstraction/ballimpl.h"
#include "common/geometry/point.h"
#include "common/geometry/circle.h"

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;

BallImpl::BallImpl()
{ }

Point BallImpl::getPosition()
{
	return Point();
}

Circle BallImpl::getObstacle()
{
	return Circle();
}