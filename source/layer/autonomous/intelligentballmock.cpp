#include "layer/autonomous/intelligentballmock.h"
#include "common/geometry/angle.h"
#include "common/geometry/circle.h"
#include "common/geometry/point.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Layer::Abstraction;
using namespace std;

IntelligentBallMock::IntelligentBallMock() :
	m_isMoving(false),
	m_currentFieldSide(FieldSideInvalid),
	m_movingDirection(FieldSideInvalid)
{ }

Angle IntelligentBallMock::getRotation() const
{
	return m_ball.getRotation();
}

Circle IntelligentBallMock::getObstacle() const
{
	return Circle();
}

vector<Circle> IntelligentBallMock::getObstacles() const
{
	return vector<Circle>();
}

Point IntelligentBallMock::getPosition() const
{
	return m_ball.getPosition();
}

double IntelligentBallMock::getVelocity() const
{
	return 0;
}

bool IntelligentBallMock::isMoving() const
{
	return m_isMoving;
}

FieldSide IntelligentBallMock::getMovingDirection() const
{
	return m_movingDirection;
}

FieldSide IntelligentBallMock::getCurrentFieldSide() const
{
	return m_currentFieldSide;
}

void IntelligentBallMock::setPosition(Point position)
{
	m_ball.setPosition(position);
}

void IntelligentBallMock::setRotation(Angle angle)
{
	m_ball.setRotation(angle);
}

void IntelligentBallMock::setIsMoving(bool value)
{
	m_isMoving = value;
}

void IntelligentBallMock::setCurrentFieldSide(FieldSide fieldSide)
{
	m_currentFieldSide = fieldSide;
}

void IntelligentBallMock::setMovingDirection(FieldSide fieldSide)
{
	m_movingDirection = fieldSide;
}
