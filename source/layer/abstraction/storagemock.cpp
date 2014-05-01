#include "layer/abstraction/storagemock.h"

using namespace RoboSoccer::Layer::Abstraction;

Ball const& StorageMock::getBall() const
{
	return m_ball;
}

ReadableRobot const& StorageMock::getEnemyRobot(unsigned int number) const
{
	return m_enemyRobot[number];
}

ControllableRobot &StorageMock::getOwnRobot(unsigned int number)
{
	return m_ownRobot[number];
}

RefereeBase &StorageMock::getReferee()
{
	return m_referee;
}

void StorageMock::addControllableRobot(ControllableRobotMock ownRobot)
{
	m_ownRobot.push_back(ownRobot);
}
