#include "layer/abstraction/storagemock.h"

using namespace RoboSoccer::Layer::Abstraction;

Ball &StorageMock::getBall()
{
	return m_ball;
}

ReadableRobot &StorageMock::getEnemyRobot(unsigned int /*number*/)
{
	return m_enemyRobot;
}

ControllableRobot &StorageMock::getOwnRobot(unsigned int /*number*/)
{
	return m_ownRobot;
}

Referee &StorageMock::getReferee()
{
	return m_referee;
}
