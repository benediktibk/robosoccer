#include "layer/abstraction/ballimpl.h"
#include "common/geometry/point.h"
#include "common/geometry/circle.h"
#include "common/geometry/angle.h"
#include "common/geometry/orientedposition.h"
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

Geometry::OrientedPosition BallImpl::getPosition() const
{
	Geometry::Point ballPosition;
	ballPosition.setX(m_ball->GetX());
	ballPosition.setY(m_ball->GetY());
	Angle angle = m_ball->GetPhi();
	Geometry::Angle ballAngle(angle.Rad());
	return Geometry::OrientedPosition(ballPosition,ballAngle);
}

Geometry::Circle BallImpl::getObstacle() const
{
	return Geometry::Circle(getPosition(), 0.045);
}

double BallImpl::getVelocity() const
{
	return m_ball->GetVelocity();
}
