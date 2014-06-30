#include "layer/autonomous/enemyteamimpl.h"
#include "layer/abstraction/storage.h"
#include "layer/abstraction/readablerobot.h"
#include "layer/autonomous/intelligentball.h"
#include "common/geometry/pose.h"
#include "common/geometry/circle.h"
#include <algorithm>
#include <iostream>

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

const ReadableRobot &EnemyTeamImpl::getPlayerNextToBall(const IntelligentBall &ball)
{
	vector<double> distances;
	distances.reserve(m_robots.size());

	for(unsigned int i=0; i<3; i++)
		distances.push_back(m_robots[i]->getPose().getPosition().distanceTo(ball.getPosition()));

	unsigned int index =  min_element(distances.begin(), distances.end()) - distances.begin();

	return *m_robots[index];
}

std::vector<Circle> EnemyTeamImpl::getObstacles() const
{
	vector<Circle> obstacles;
	obstacles.reserve(3);

	for(unsigned int i=0; i<3; i++)
		obstacles.push_back(m_robots[i]->getObstacle());

	return obstacles;
}

void EnemyTeamImpl::update()
{
	m_robots[0]->updateSensors();
	m_robots[1]->updateSensors();
	m_robots[2]->updateSensors();
}

