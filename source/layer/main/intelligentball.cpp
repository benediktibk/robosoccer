#include "layer/main/intelligentball.h"
#include "layer/abstraction/ball.h"
#include "common/geometry/orientedposition.h"
#include "common/geometry/circle.h"

using namespace RoboSoccer::Layer::Main;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common;

IntelligentBall::IntelligentBall()
{

}

Geometry::OrientedPosition IntelligentBall::getPosition() const
{
	return m_ball->getPosition();
}

Geometry::Circle IntelligentBall::getObstacle() const
{
	return m_ball->getObstacle();
}

double IntelligentBall::getVelocity() const
{
	return m_ball->getVelocity();
}

bool IntelligentBall::isMoving(double velocity) const
{
	return(velocity > 0.1);
	//TODO: find appropriate Threshold
}

FieldSide IntelligentBall::getMovingDirection(Geometry::OrientedPosition position) const
{
	Geometry::Angle direction = position.getOrientation();
	double angle=direction.getValueBetweenMinusPiAndPi();
	if (angle > 0)
		return FieldSideRight;
	else
		return FieldSideLeft;
}
