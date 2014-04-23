#include "layer/abstraction/ballimpl.h"
#include "common/geometry/point.h"
#include "common/geometry/circle.h"
#include <kogmo_rtdb.hxx>
#include <raw_ball.h>

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;

BallImpl::BallImpl(KogniMobil::RTDBConn &dataBase) :
	m_ball(new RawBall(dataBase))
{ }

BallImpl::~BallImpl()
{
	delete m_ball;
	m_ball = 0;
}

Point BallImpl::getPosition() const
{
	return Point(m_ball->GetX(), m_ball->GetY());
}

Circle BallImpl::getObstacle() const
{
	//! @todo measure and fix diameter of ball
	return Circle(getPosition(), 0.05);
}