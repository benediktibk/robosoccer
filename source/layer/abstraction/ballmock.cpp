#include "layer/abstraction/ballmock.h"
#include "common/geometry/point.h"
#include "common/geometry/circle.h"
#include "common/geometry/angle.h"
#include "common/geometry/orientedposition.h"

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;

Point BallMock::getPosition() const
{
	return m_position;
}

Angle BallMock::getRotation() const
{
	return Angle();
}

Circle BallMock::getObstacle() const
{
	return Circle();
}

double BallMock::getVelocity() const
{
	return 0;
}

void BallMock::setBallPosition(Point position)
{
	m_position = position;
}

