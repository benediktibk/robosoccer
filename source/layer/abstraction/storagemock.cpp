#include "layer/abstraction/storagemock.h"

using namespace std;
using namespace RoboSoccer::Layer::Abstraction;

StorageMock::StorageMock()
{
	m_ownRobot.push_back(new ControllableRobotMock());
	m_ownRobot.push_back(new ControllableRobotMock());
	m_ownRobot.push_back(new ControllableRobotMock());
	m_enemyRobot.push_back(new ReadableRobotMock());
	m_enemyRobot.push_back(new ReadableRobotMock());
	m_enemyRobot.push_back(new ReadableRobotMock());
}

StorageMock::~StorageMock()
{
	for (vector<ControllableRobotMock*>::iterator i = m_ownRobot.begin(); i != m_ownRobot.end(); ++i)
		delete *i;
	m_ownRobot.clear();

	for (vector<ReadableRobotMock*>::iterator i = m_enemyRobot.begin(); i != m_enemyRobot.end(); ++i)
		delete *i;
	m_enemyRobot.clear();
}

Ball const& StorageMock::getBall() const
{
	return m_ball;
}

ReadableRobot const& StorageMock::getEnemyRobot(unsigned int number) const
{
	return *m_enemyRobot[number];
}

ControllableRobot &StorageMock::getOwnRobot(unsigned int number)
{
	return *m_ownRobot[number];
}

RefereeBase &StorageMock::getReferee()
{
	return m_referee;
}

ControllableRobotMock &StorageMock::getOwnRobotMock(unsigned int number)
{
	return *m_ownRobot[number];
}

ReadableRobotMock &StorageMock::getEnemyRobotMock(unsigned int number)
{
	return *m_enemyRobot[number];
}
