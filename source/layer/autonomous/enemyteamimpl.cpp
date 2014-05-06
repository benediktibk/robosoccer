#include "layer/autonomous/enemyteamimpl.h"
#include "layer/abstraction/storage.h"
#include "layer/abstraction/readablerobot.h"
#include "layer/autonomous/intelligentball.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;

EnemyTeamImpl::EnemyTeamImpl(Abstraction::Storage &storage)
{
	m_robots.push_back(&storage.getEnemyRobot(0));
	m_robots.push_back(&storage.getEnemyRobot(1));
	m_robots.push_back(&storage.getEnemyRobot(2));
}

EnemyTeamImpl::~EnemyTeamImpl()
{
	m_robots.clear();
}

const ReadableRobot &EnemyTeamImpl::getGoalkeeper()
{
	return *m_robots.front();
}

const ReadableRobot &EnemyTeamImpl::getPlayerNextToBall(const IntelligentBall &ball)
{
	ball.isMoving();
	return *m_robots.front();
}

void EnemyTeamImpl::getObstacles()
{

}

