#include "layer/autonomous/enemyteamimpl.h"
#include "layer/abstraction/storage.h"
#include "layer/abstraction/readablerobot.h"
#include "layer/autonomous/intelligentball.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;

EnemyTeamImpl::EnemyTeamImpl(Abstraction::Storage &storage) :
	m_robot(storage.getEnemyRobot(0))
{ }

EnemyTeamImpl::~EnemyTeamImpl()
{ }

const ReadableRobot &EnemyTeamImpl::getGoalkeeper()
{
	return m_robot;
}

const ReadableRobot &EnemyTeamImpl::getPlayerNextToBall(const IntelligentBall &ball)
{
	ball.isMoving();
	return m_robot;
}

void EnemyTeamImpl::getObstacles()
{

}

