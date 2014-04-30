#include "layer/autonomous/intelligentballmock.h"
#include "common/geometry/angle.h"
#include "common/geometry/circle.h"
#include "common/geometry/point.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Layer::Abstraction;

IntelligentBallMock::IntelligentBallMock()
{ }

Angle IntelligentBallMock::getRotation() const
{
	return Angle();
}

Circle IntelligentBallMock::getObstacle() const
{
	return Circle();
}

Point IntelligentBallMock::getPosition() const
{
	return m_ball.getPosition();
}

double IntelligentBallMock::getVelocity() const
{
	return 0;
}

bool IntelligentBallMock::isMoving() const
{
	return false;
}

FieldSide IntelligentBallMock::getMovingDirection() const
{
	return FieldSideInvalid;
}

FieldSide IntelligentBallMock::getCurrentFieldSide() const
{
	return FieldSideInvalid;
}

void IntelligentBallMock::setPosition(Point position)
{
	m_ball.setPosition(position);
}
