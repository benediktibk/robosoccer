#include "layer/autonomous/intelligentballimpl.h"
#include "layer/abstraction/ball.h"
#include "common/geometry/angle.h"
#include "common/geometry/circle.h"
#include "common/geometry/point.h"
#include <assert.h>

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
	return(m_ball.getVelocity() > 0.2);
}

FieldSide IntelligentBallImpl::getMovingDirection() const
{
	assert(isMoving());

	double angle = m_ball.getRotation().getValueBetweenMinusPiAndPi();
	double piHalf = Angle::getQuarterRotation().getValueBetweenMinusPiAndPi();

	if (angle >= -piHalf && angle < piHalf)
		return FieldSideRight;
	else
		return FieldSideLeft;
}

FieldSide IntelligentBallImpl::getCurrentFieldSide() const
{
	if (m_ball.getPosition().getX() > 0)
		return FieldSideRight;
	else
		return FieldSideLeft;
}

Point IntelligentBallImpl::getPosition() const
{
	return m_ball.getPosition();
}
