#include "layer/autonomous/obstaclesourcemock.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;
using namespace std;

vector<Circle> ObstacleSourceMock::getObstacles() const
{
	return m_obstacles;
}

void ObstacleSourceMock::setObstacles(const vector<Circle> &obstacles)
{
	m_obstacles = obstacles;
}
