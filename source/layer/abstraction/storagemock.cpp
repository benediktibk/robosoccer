#include "layer/abstraction/storagemock.h"

using namespace RoboSoccer::Layer::Abstraction;

Ball const& StorageMock::getBall() const
{
	return m_ball;
}

ReadableRobot const& StorageMock::getEnemyRobot(unsigned int /*number*/) const
{
	return m_enemyRobot;
}

ControllableRobot &StorageMock::getOwnRobot(unsigned int /*number*/)
{
	return m_ownRobot;
}

RefereeBase &StorageMock::getReferee()
{
	return m_referee;
}

const ControllableRobotMock &StorageMock::getOwnRobotMock() const
{
	return m_ownRobot;
}
