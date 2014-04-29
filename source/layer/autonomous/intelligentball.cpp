#include "layer/autonomous//intelligentball.h"
#include "layer/abstraction/ball.h"
#include "common/geometry/angle.h"
#include "common/geometry/circle.h"

using namespace RoboSoccer::Layer::Main;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common;

IntelligentBall::IntelligentBall()
{

}

Geometry::Angle IntelligentBall::getRotation() const
{
	return m_ball->getRotation();
}

Geometry::Circle IntelligentBall::getObstacle() const
{
	return m_ball->getObstacle();
}

double IntelligentBall::getVelocity() const
{
	return m_ball->getVelocity();
}

bool IntelligentBall::isMoving() const
{
	double velocity = m_ball->getVelocity();
	return(velocity > 0.1);
	//TODO: find appropriate Threshold
}

FieldSide IntelligentBall::getMovingDirection() const
{
	Geometry::Angle direction = m_ball->getRotation();
	double angle=direction.getValueBetweenMinusPiAndPi();
	if (angle > 0)
		return FieldSideRight;
	else
		return FieldSideLeft;
}
