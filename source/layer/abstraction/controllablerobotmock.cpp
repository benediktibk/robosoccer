#include "layer/abstraction/controllablerobotmock.h"
#include "common/geometry/pose.h"
#include "common/geometry/circle.h"

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;

ControllableRobotMock::ControllableRobotMock() :
	m_callsToStop(0)
{ }

Pose ControllableRobotMock::getPose() const
{
	return Pose();
}

Circle ControllableRobotMock::createObstacle() const
{
	return Circle();
}

void ControllableRobotMock::gotoPositionImprecise(const Point &/*position*/)
{

}

void ControllableRobotMock::gotoPositionPrecise(const Point &/*position*/)
{

}

bool ControllableRobotMock::kick(unsigned int /*force*/)
{
	return false;
}

void ControllableRobotMock::turn(const Angle &/*absoluteAngle*/)
{

}

void ControllableRobotMock::stop()
{
	++m_callsToStop;
}

unsigned int ControllableRobotMock::getCallsToStop() const
{
	return m_callsToStop;
}