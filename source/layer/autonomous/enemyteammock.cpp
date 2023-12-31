#include "layer/autonomous/enemyteammock.h"
#include "layer/abstraction/readablerobotmock.h"
#include "common/geometry/circle.h"

using namespace std;
using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Layer::Abstraction;
using namespace RoboSoccer::Common::Geometry;

EnemyTeamMock::EnemyTeamMock()
{
	m_robots.reserve(3);
	m_robots.push_back(new ReadableRobotMock());
	m_robots.push_back(new ReadableRobotMock());
	m_robots.push_back(new ReadableRobotMock());
}

EnemyTeamMock::~EnemyTeamMock()
{
	while(m_robots.size() > (size_t) 0)
	{
		delete m_robots.back();
		m_robots.pop_back();
	}

	m_robots.clear();
}

vector<Circle> EnemyTeamMock::getObstacles() const
{
	return m_obstacles;
}

void EnemyTeamMock::updateSensors()
{}

void EnemyTeamMock::setObstacles(const vector<Circle> &obstacles)
{
	m_obstacles = obstacles;
}

const ReadableRobot &EnemyTeamMock::getPlayerNextToBall(const IntelligentBall &)
{
	return *m_robots.front();
}
