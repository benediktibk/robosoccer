#include "layer/abstraction/ballmock.h"
#include "common/geometry/point.h"
#include "common/geometry/circle.h"
#include "common/geometry/angle.h"
#include "common/geometry/orientedposition.h"

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;

OrientedPosition BallMock::getPosition() const
{
	return OrientedPosition();
}

Circle BallMock::getObstacle() const
{
	return Circle();
}

double BallMock::getVelocity() const
{
	return 0;
}
