#include "layer/autonomous/robotmock.h"
#include "common/geometry/pose.h"
#include "common/geometry/circle.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;

RobotMock::RobotMock() :
	m_callsToStop(0),
	m_callsToGoTo(0),
	m_callsToKick(0),
	m_targetReached(false)
{ }

RobotMock::~RobotMock()
{ }

void RobotMock::goTo(const Point &/*position*/)
{
	++m_callsToGoTo;
}

Pose RobotMock::getCurrentPose() const
{
	return Pose();
}

Circle RobotMock::getObstacle() const
{
	return Circle();
}

bool RobotMock::targetReached() const
{
	return m_targetReached;
}

bool RobotMock::cantReachTarget() const
{
	return false;
}

void RobotMock::kick(unsigned int /*force*/, IntelligentBall const &/*ball*/)
{
	++m_callsToKick;
}

void RobotMock::update()
{ }

unsigned int RobotMock::getCallsToStop() const
{
	return m_callsToStop;
}

unsigned int RobotMock::getCallsToGoTo() const
{
	return m_callsToGoTo;
}

unsigned int RobotMock::getCallsToKick() const
{
	return m_callsToKick;
}

void RobotMock::setTargetReached(bool value)
{
	m_targetReached = value;
}

void RobotMock::stop()
{
	++m_callsToStop;
}
