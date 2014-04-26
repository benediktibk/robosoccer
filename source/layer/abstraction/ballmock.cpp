#include "layer/abstraction/ballmock.h"
#include "common/geometry/point.h"
#include "common/geometry/circle.h"
#include "common/geometry/angle.h"

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;

Point BallMock::getPosition() const
{
	return Point();
}

Circle BallMock::getObstacle() const
{
	return Circle();
}

bool BallMock::isMoving() const
{
	return true;
}

Angle BallMock::getDirection() const
{
	return Angle();
}
