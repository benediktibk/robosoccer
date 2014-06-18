#include "layer/autonomous/robotmock.h"
#include "common/geometry/pose.h"
#include "common/geometry/circle.h"
#include "common/routing/route.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;
using namespace RoboSoccer::Common::Routing;
using namespace std;

RobotMock::RobotMock() :
	m_callsToStop(0),
	m_callsToGoTo(0),
	m_callsToGoToDirect(0),
	m_callsToKick(0),
	m_targetReached(false)
{ }

RobotMock::~RobotMock()
{ }

void RobotMock::goTo(const vector<Pose> &, DriveMode)
{
	++m_callsToGoTo;
}

Pose RobotMock::getCurrentPose() const
{
	return m_pose;
}

Circle RobotMock::getObstacle() const
{
	return m_obstacle;
}

vector<Circle> RobotMock::getObstacles() const
{
	vector<Circle> result;
	result.push_back(getObstacle());
	return result;
}

bool RobotMock::reachedTarget() const
{
	return m_targetReached;
}

void RobotMock::kick(IntelligentBall const &)
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

void RobotMock::setObstacle(const Circle &obstacle)
{
	m_obstacle = obstacle;
}

void RobotMock::stop()
{
	++m_callsToStop;
}

void RobotMock::goToDirect(const Pose &)
{
	++m_callsToGoToDirect;
}

unsigned int RobotMock::getCallsToGoToDirect() const
{
	return m_callsToGoToDirect;
}

unsigned int RobotMock::getCallsToGoToCombined() const
{
	return m_callsToGoTo + m_callsToGoToDirect;
}

void RobotMock::setCurrentPose(const Pose &pose)
{
	m_pose = pose;
}

Route RobotMock::getCurrentRoute() const
{
	return Route();
}
