#include "layer/autonomous/obstaclefetcher.h"
#include "layer/autonomous/enemyteam.h"
#include "layer/autonomous/team.h"
#include "layer/autonomous/intelligentball.h"
#include "common/geometry/circle.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;
using namespace std;

ObstacleFetcher::ObstacleFetcher(Team &team, const EnemyTeam &enemyTeam, IntelligentBall &ball) :
	m_team(team),
	m_enemyTeam(enemyTeam),
	m_ball(ball)
{ }

