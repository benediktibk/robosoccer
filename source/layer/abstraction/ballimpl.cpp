#include "layer/abstraction/ballimpl.h"
#include "common/geometry/circle.h"
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

void BallImpl::update()
{
	m_orientation = Geometry::Angle(m_ball->GetPhi().Rad());
	m_position = Geometry::Point(m_ball->GetX(),m_ball->GetY());
	m_velocity = m_ball->GetVelocity()*871.3072;
}

Geometry::Angle BallImpl::getRotation() const
{
	return m_orientation;
}

Geometry::Point BallImpl::getPosition() const
{
	return m_position;
}

Geometry::Circle BallImpl::getObstacle() const
{
	return Geometry::Circle(m_position, 0.045);
}

double BallImpl::getVelocity() const
{
	return m_velocity;
}
