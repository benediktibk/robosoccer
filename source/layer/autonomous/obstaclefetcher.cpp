#include "layer/autonomous/obstaclefetcher.h"
#include "layer/autonomous/enemyteam.h"
#include "layer/autonomous/team.h"
#include "layer/autonomous/intelligentball.h"
#include "common/geometry/circle.h"
#include "layer/autonomous/robot.h"
#include "layer/abstraction/readablerobot.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;
using namespace std;

ObstacleFetcher::ObstacleFetcher(vector<Circle> &obstaclesTeam, const vector<Circle> &obstaclesEnemyTeam, Circle &obstacleBall)
{
	m_obstacles.reserve(7);
	m_obstacles = obstaclesTeam;
	m_obstacles.insert(m_obstacles.end(), obstaclesEnemyTeam.begin(), obstaclesEnemyTeam.end());
	m_obstacles.push_back(obstacleBall);
}

const vector<Circle> ObstacleFetcher::getAllObstacles() const
{
	return m_obstacles;
}

