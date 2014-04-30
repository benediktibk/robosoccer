#include "layer/autonomous/teammock.h"

using namespace RoboSoccer::Layer::Autonomous;

TeamMock::TeamMock()
{ }

TeamMock::~TeamMock()
{ }

Robot &TeamMock::getGoalie()
{
	return m_robot;
}

Robot &TeamMock::getPlayerCloserToBall(const IntelligentBall &/*ball*/)
{
	return m_robot;
}

Robot &TeamMock::getPlayerFartherAwayFromBall(const IntelligentBall &/*ball*/)
{
	return m_robot;
}

Robot &TeamMock::getFirstFieldPlayer()
{
	return m_robot;
}

Robot &TeamMock::getSecondFieldPlayer()
{
	return m_robot;
}

Robot &TeamMock::getRobotByNumber(unsigned int /*i*/)
{
	return m_robot;
}

