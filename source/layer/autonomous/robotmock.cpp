#include "layer/autonomous/robotmock.h"
#include "common/geometry/pose.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;

RobotMock::RobotMock() :
	m_callsToStop(0),
	m_callsToGoTo(0),
	m_callsToKick(0)
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

bool RobotMock::targetReached() const
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

void RobotMock::stop()
{
	++m_callsToStop;
}
