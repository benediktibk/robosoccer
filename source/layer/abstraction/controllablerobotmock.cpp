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
	m_callsToUpdate(0)
{ }

Pose ControllableRobotMock::getPose() const
{
	return m_pose;
}

Circle ControllableRobotMock::getObstacle() const
{
	return Circle(m_pose.getPosition(),0.095);
}

void ControllableRobotMock::gotoPositionImprecise(const Point &/*position*/)
{
	++m_callsToGoToPositionImprecise;
}

void ControllableRobotMock::gotoPositionPrecise(const Point &/*position*/)
{
	++m_callsToGoToPositionPrecise;
}

bool ControllableRobotMock::kick(unsigned int /*force*/)
{
	++m_callsToKick;
	return false;
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

void ControllableRobotMock::update()
{
	++m_callsToUpdate;
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

const Angle & ControllableRobotMock::getLastAngleToTurnTo() const
{
	assert(getCallsToTurn() > 0);
	return m_lastAngleToTurnTo;
}
