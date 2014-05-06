#include "layer/autonomous/enemyteamimpl.h"
#include "layer/abstraction/storage.h"
#include "layer/abstraction/readablerobot.h"
#include "layer/autonomous/intelligentball.h"
#include "common/geometry/circle.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;
using namespace std;

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

const vector<Circle> EnemyTeamImpl::getObstacles()
{
	vector<Circle> obstacles;
	obstacles.reserve(3);

	for(unsigned int i=0;i<3;i++)
		obstacles.push_back(m_robots[i]->createObstacle());

	return obstacles;
}

