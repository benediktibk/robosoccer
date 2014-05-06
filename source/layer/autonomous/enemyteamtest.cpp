#include "layer/autonomous/enemyteamtest.h"
#include "layer/autonomous/enemyteamimpl.h"
#include "layer/abstraction/readablerobotmock.h"
#include "layer/abstraction/storagemock.h"

using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Layer::Autonomous;
using namespace std;

void EnemyTeamTest::setUp()
{
	m_storageMock = new StorageMock;
	m_readableRobotMockPlayer1 = &(m_storageMock->getEnemyRobotMock(0));
	m_readableRobotMockPlayer2 = &(m_storageMock->getEnemyRobotMock(1));
	m_readableRobotMockPlayer3 = &(m_storageMock->getEnemyRobotMock(2));
	m_enemyTeam = new EnemyTeamImpl(*m_storageMock);
}

void EnemyTeamTest::tearDown()
{
	delete m_enemyTeam;
	m_enemyTeam = 0;
	delete m_storageMock;
	m_storageMock = 0;
	m_readableRobotMockPlayer1 = 0;
	m_readableRobotMockPlayer2 = 0;
	m_readableRobotMockPlayer3 = 0;
}
