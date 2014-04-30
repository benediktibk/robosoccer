#include "layer/autonomous//intelligentball.h"
#include "layer/abstraction/ball.h"
#include "common/geometry/angle.h"
#include "common/geometry/circle.h"
#include "common/geometry/point.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;

IntelligentBall::IntelligentBall(Abstraction::Ball const &ball):
	m_ball(ball)
{
}

IntelligentBall::~IntelligentBall()
{ }

Angle IntelligentBall::getRotation() const
{
	return m_ball.getRotation();
}

Circle IntelligentBall::getObstacle() const
{
	return m_ball.getObstacle();
}

double IntelligentBall::getVelocity() const
{
	return m_ball.getVelocity();
}

bool IntelligentBall::isMoving() const
{
	double velocity = m_ball.getVelocity();
	return(velocity > 0.2);
}

FieldSide IntelligentBall::getMovingDirection() const
{
	Angle direction = m_ball.getRotation();
	double angle=direction.getValueBetweenMinusPiAndPi();
	if (angle > 0)
		return FieldSideRight;
	else
		return FieldSideLeft;
}

Point IntelligentBall::getPosition() const
{
	return m_ball.getPosition();
}
