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

void IntelligentBallMock::update()
{ }

Angle IntelligentBallMock::getRotation() const
{
	return m_ball.getRotation();
}

Circle IntelligentBallMock::getObstacle() const
{
	return m_obstacle;
}

vector<Circle> IntelligentBallMock::getObstacles() const
{
	vector<Circle> result;
	result.push_back(getObstacle());
	return result;
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

double IntelligentBallMock::getShootingLineCoveragePercent(ObstacleFetcher &/*obstacles*/, Point &/*target*/) const
{
	return 0;
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

void IntelligentBallMock::setObstacle(const Circle &obstacle)
{
	m_obstacle = obstacle;
}
