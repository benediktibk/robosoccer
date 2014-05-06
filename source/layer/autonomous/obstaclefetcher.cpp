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

ObstacleFetcher::ObstacleFetcher(Team &team, const EnemyTeam &enemyTeam, IntelligentBall &ball) :
	m_team(team),
	m_enemyTeam(enemyTeam),
	m_ball(ball)
{ }

const vector<Circle> ObstacleFetcher::getAllObstacles() const
{
	vector<Circle> obstacles;
	obstacles.reserve(7);

	obstacles.push_back(m_ball.getObstacle());
	for(unsigned int i=0;i<3;i++)
	{
		obstacles.push_back(m_team.getRobotByNumber(i).getObstacle());
		//!@todo Impl of EnemyTeam is missing
		//obstacles.push_back(m_enemyTeam.getRobotByNumer(i).createObstacle());
	}

	return obstacles;
}

