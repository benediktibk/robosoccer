#include "layer/autonomous/intelligentballimpl.h"
#include "layer/abstraction/ball.h"
#include "common/geometry/angle.h"
#include "common/geometry/circle.h"
#include "common/geometry/point.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;

IntelligentBallImpl::IntelligentBallImpl(const Ball &ball) :
	m_ball(ball)
{ }

Angle IntelligentBallImpl::getRotation() const
{
	return m_ball.getRotation();
}

Circle IntelligentBallImpl::getObstacle() const
{
	return m_ball.getObstacle();
}

double IntelligentBallImpl::getVelocity() const
{
	return m_ball.getVelocity();
}

bool IntelligentBallImpl::isMoving() const
{
	double velocity = m_ball.getVelocity();
	return(velocity > 0.2);
}

FieldSide IntelligentBallImpl::getMovingDirection() const
{
	Angle direction = m_ball.getRotation();
	double angle=direction.getValueBetweenMinusPiAndPi();
	if (angle > 0)
		return FieldSideRight;
	else
		return FieldSideLeft;
}

Point IntelligentBallImpl::getPosition() const
{
	return m_ball.getPosition();
}