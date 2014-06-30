#include "layer/abstraction/controllablerobotmock.h"
#include "common/geometry/pose.h"
#include "common/geometry/circle.h"
#include <assert.h>

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;

ControllableRobotMock::ControllableRobotMock() :
	m_callsToStop(0),
	m_callsToGoToPositionImprecise(0),
	m_callsToGoToPositionPrecise(0),
	m_callsToTurn(0),
	m_callsToKick(0),
	m_callsToUpdate(0),
	m_isMoving(false)
{ }

Pose ControllableRobotMock::getPose() const
{
	return m_pose;
}

Pose ControllableRobotMock::getPoseRaw() const
{
	return m_pose;
}

Circle ControllableRobotMock::getObstacle() const
{
	return Circle(m_pose.getPosition(),ReadableRobot::getWidth());
}

void ControllableRobotMock::gotoPositionImprecise(const Point &position)
{
	++m_callsToGoToPositionImprecise;
	m_lastPointToDriveTo = position;
}

void ControllableRobotMock::gotoPositionPrecise(const Point &position)
{
	++m_callsToGoToPositionPrecise;
	m_lastPointToDriveTo = position;
}

void ControllableRobotMock::kick(Point const &/*ballPosition*/)
{
	++m_callsToKick;
}

void ControllableRobotMock::turn(const Angle &absoluteAngle)
{
	m_lastAngleToTurnTo = absoluteAngle;
	++m_callsToTurn;
}

void ControllableRobotMock::stop()
{
	++m_callsToStop;
}

void ControllableRobotMock::updateSensors()
{
	++m_callsToUpdate;
}

bool ControllableRobotMock::isMoving() const
{
	return m_isMoving;
}

unsigned int ControllableRobotMock::getCallsToStop() const
{
	return m_callsToStop;
}

unsigned int ControllableRobotMock::getCallsToGoToPositionImprecise() const
{
	return m_callsToGoToPositionImprecise;
}

unsigned int ControllableRobotMock::getCallsToGoToPositionPrecise() const
{
	return m_callsToGoToPositionPrecise;
}

unsigned int ControllableRobotMock::getCallsToTurn() const
{
	return m_callsToTurn;
}

unsigned int ControllableRobotMock::getCallsToKick() const
{
	return m_callsToKick;
}

unsigned int ControllableRobotMock::getCallsToUpdate() const
{
	return m_callsToUpdate;
}

void ControllableRobotMock::setPose(const Pose &pose)
{
	m_pose = pose;
}

void ControllableRobotMock::setIsMoving(bool value)
{
	m_isMoving = value;
}

const Angle & ControllableRobotMock::getLastAngleToTurnTo() const
{
	assert(getCallsToTurn() > 0);
	return m_lastAngleToTurnTo;
}

const Point & ControllableRobotMock::getLastPointToDriveTo() const
{
	assert(getCallsToGoToPositionImprecise() + getCallsToGoToPositionPrecise() > 0);
	return m_lastPointToDriveTo;
}

unsigned int RoboSoccer::Layer::Abstraction::ControllableRobotMock::getCallsToGoToCombined() const
{
	return getCallsToGoToPositionImprecise() + getCallsToGoToPositionPrecise();
}
