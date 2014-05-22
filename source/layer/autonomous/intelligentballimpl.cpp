#include "layer/autonomous/intelligentballimpl.h"
#include "layer/abstraction/ball.h"
#include "common/geometry/angle.h"
#include "common/geometry/circle.h"
#include "common/geometry/point.h"
#include "layer/autonomous/obstaclefetcher.h"
#include <assert.h>
#include <math.h>

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace std;

IntelligentBallImpl::IntelligentBallImpl(const Ball &ball) :
	m_ball(ball)
{ }

Angle IntelligentBallImpl::getRotation() const
{
	return m_ball.getRotation();
}

vector<Circle> IntelligentBallImpl::getObstacles() const
{
	vector<Circle> result;
	result.push_back(getObstacle());
	return result;
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

	if (fabs(angle) < piHalf)
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

double IntelligentBallImpl::getShootingLineCoveragePercent(ObstacleFetcher &obstacles, Point &target) const
{
	vector<Circle> Obstacles = obstacles.getAllObstacles();
	Point Punkthaftigkeit = target;
	Circle erster = Obstacles.at(1);
	return Punkthaftigkeit.getX()+erster.getDiameter();
}
