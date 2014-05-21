#include "layer/abstraction/ballmock.h"
#include "common/geometry/point.h"
#include "common/geometry/circle.h"
#include "common/geometry/angle.h"
#include "common/geometry/pose.h"

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;

BallMock::BallMock() :
	m_velocity(0),
	m_rotation(0)
{ }

Point BallMock::getPosition() const
{
	return m_position;
}

Angle BallMock::getRotation() const
{
	return m_rotation;
}

Circle BallMock::getObstacle() const
{
	return m_obstacle;
}

double BallMock::getVelocity() const
{
	return m_velocity;
}

void BallMock::setPosition(Point position)
{
	m_position = position;
}

void BallMock::setVelocity(double value)
{
	m_velocity = value;
}

void BallMock::setObstacle(const Circle &obstacle)
{
	m_obstacle = obstacle;
}

void BallMock::setRotation(Angle value)
{
	m_rotation = value;
}

