#include "layer/abstraction/ballmock.h"
#include "common/geometry/point.h"
#include "common/geometry/circle.h"

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;

Point BallMock::getPosition() const
{
	return m_position;
}

Circle BallMock::getObstacle() const
{
	return Circle();
}

void BallMock::setBallPosition(Point position)
{
	m_position = position;
}

