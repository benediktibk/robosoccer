#include "layer/abstraction/ballimpl.h"
#include "common/geometry/point.h"
#include "common/geometry/circle.h"
#include "common/geometry/angle.h"
#include <kogmo_rtdb.hxx>
#include <raw_ball.h>

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common;

BallImpl::BallImpl(KogniMobil::RTDBConn &dataBase) :
	m_ball(new RawBall(dataBase))
{ }

BallImpl::~BallImpl()
{
	delete m_ball;
	m_ball = 0;
}

Geometry::Point BallImpl::getPosition() const
{
	return Geometry::Point(m_ball->GetX(), m_ball->GetY());
}

Geometry::Circle BallImpl::getObstacle() const
{
	return Geometry::Circle(getPosition(), 0.045);
}

bool BallImpl::isMoving() const
{
	return(m_ball->GetVelocity() > 0.1);
	//TODO: find appropriate Threshold
}

Geometry::Angle BallImpl::getDirection() const
{
	Angle angle = m_ball->GetPhi();
	Geometry::Angle direction(angle.Rad());
	return direction;
}
