#include "layer/autonomous/obstaclefetchertest.h"
#include "layer/autonomous/obstaclefetcher.h"
#include "layer/autonomous/enemyteammock.h"
#include "layer/autonomous/teammock.h"
#include "layer/autonomous/intelligentballmock.h"

using namespace RoboSoccer::Layer::Autonomous;
using namespace RoboSoccer::Common::Geometry;
using namespace std;

void ObstacleFetcherTest::setUp()
{
	m_team = new TeamMock();
	m_enemyTeam = new EnemyTeamMock();
	m_ball = new IntelligentBallMock();
	m_obstacleFetcher = new ObstacleFetcher(*m_team, *m_enemyTeam, *m_ball);
	RobotMock &ownRobot = m_team->getRobotMock();
	ownRobot.setObstacle(Circle(Point(3, 3), 3));
	vector<Circle> enemyObstacles;
	enemyObstacles.push_back(Circle(Point(4, 4), 4));
	enemyObstacles.push_back(Circle(Point(5, 5), 5));
	enemyObstacles.push_back(Circle(Point(6, 6), 6));
	m_enemyTeam->setObstacles(enemyObstacles);
	m_ball->setObstacle(Circle(Point(7, 7), 7));
}

void ObstacleFetcherTest::tearDown()
{
	delete m_obstacleFetcher;
	m_obstacleFetcher = 0;
	delete m_team;
	m_team = 0;
	delete m_enemyTeam;
	m_enemyTeam = 0;
	delete m_ball;
	m_ball = 0;
}

void ObstacleFetcherTest::getAllObstacles_empty_countIs7()
{
	vector<Circle> obstacles = m_obstacleFetcher->getAllObstacles();

	CPPUNIT_ASSERT_EQUAL((size_t)7, obstacles.size());
}
